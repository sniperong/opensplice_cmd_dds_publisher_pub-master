#ifdef _WIN32
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning (disable : 4786)
#include <windows.h>
void sleep(int secs)
{
    Sleep(secs * 1000);
}
#else
#include <unistd.h>
#endif

#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <stdio.h>

#include <string.h>
#include <stdlib.h>

#include <string>
#include <vector>

#include "example_main.h"

#define NO_ATTRIBUTES 10
using namespace std;

void checkError (
    SQLRETURN       rc,
    SQLSMALLINT     handleType,
    SQLHANDLE       handle,
    const char      *msg);

int OSPL_MAIN (int argc, char* argv[])
{
    SQLHENV  m_henv;
    SQLHDBC  m_hdbc;
    SQLHSTMT m_hstmt0, m_hstmt1;
    SQLPOINTER nRows=(SQLPOINTER)10;
    SQLRETURN retcode;
    char message[128];
    int NUM_MSG = 10;

    if (argc !=6) {
        printf("USAGE: %s  <dsn> <user> <pwd> <userID> <userName>\n", argv[0]);
        printf ("Exiting in 5 seconds...\n");
        sleep(5);

        return 0;
    }

    string m_dsn(argv[1]);
    string m_user(argv[2]);
    string m_pwd(argv[3]);
    char* userID = argv[4];
    char* userName = argv[5];
    retcode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv);
    checkError (retcode, SQL_HANDLE_ENV, m_henv, "SQLAllocHandle environment handle");

    retcode = SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION,(SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER);
    checkError (retcode, SQL_HANDLE_ENV, m_henv, "SQLSetEnvAttr:SQL_ATTR_ODBC_VERSION");

    retcode = SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc);
    checkError (retcode, SQL_HANDLE_ENV, m_henv, "SQLAllocHandle database handle");

    SQLSetConnectAttr(m_hdbc, SQL_ATTR_AUTOCOMMIT,(SQLPOINTER)SQL_AUTOCOMMIT_ON, SQL_IS_UINTEGER);
    checkError (retcode, SQL_HANDLE_ENV, m_henv, "SQLSetConnectAttr:SQL_AUTOCOMMIT_ON");

    SQLSetConnectAttr(m_hdbc, SQL_ATTR_CONNECTION_TIMEOUT, (SQLPOINTER)100,  SQL_IS_INTEGER);
    checkError (retcode, SQL_HANDLE_ENV, m_henv, "SQLSetConnectAttr:SQL_LOGIN_TIMEOUT,");

    SQLSetConnectAttr(m_hdbc, SQL_ATTR_LOGIN_TIMEOUT, (SQLPOINTER)0,  SQL_IS_INTEGER);
    checkError (retcode, SQL_HANDLE_ENV, m_henv, "SQLSetConnectAttr:SQL_LOGIN_TIMEOUT,");

    retcode = SQLConnect(m_hdbc, (SQLCHAR*)m_dsn.c_str(), SQL_NTS,(SQLCHAR*)m_user.c_str(), SQL_NTS,(SQLCHAR*)m_pwd.c_str(), SQL_NTS);
    checkError (retcode, SQL_HANDLE_DBC, m_hdbc, "SQLConnect to database");

    retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt0);
    checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "SQLAllocHandle statement handle");

    retcode = SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &m_hstmt1);
    checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "SQLAllocHandle statement handle(1)");

    retcode=SQLSetStmtAttr(m_hstmt0,SQL_ATTR_MAX_ROWS,(SQLPOINTER)nRows,SQL_IS_INTEGER);
    checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "SQLSetStmtAttr");

    retcode=SQLSetStmtAttr(m_hstmt1,SQL_ATTR_MAX_ROWS,(SQLPOINTER)nRows,SQL_IS_INTEGER);
    checkError (retcode, SQL_HANDLE_STMT, m_hstmt1, "SQLSetStmtAttr(1)");

    SQLExecDirect(m_hstmt0,(SQLCHAR*)"CREATE TABLE \"SqlChat_NameService\" (\"userID\" INTEGER NOT NULL, \"name\" VARCHAR(6000) NOT NULL, PRIMARY KEY(\"userID\"))",SQL_NTS);
    retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)"DELETE FROM \"SqlChat_NameService\"",SQL_NTS);
    checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "SQLExecDirect: DELETE");

    SQLExecDirect(m_hstmt0,(SQLCHAR*)"CREATE TABLE \"SqlChat_ChatMessage\" (\"userID\" INTEGER NOT NULL, \"index\" INTEGER NOT NULL, \"content\" VARCHAR(6000) NOT NULL, PRIMARY KEY(\"userID\"))",SQL_NTS);
    retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)"DELETE FROM \"SqlChat_ChatMessage\"",SQL_NTS);
    checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "SQLExecDirect: DELETE");

    sleep(1); //sleep 1 sec

    sprintf(message, "INSERT INTO \"SqlChat_NameService\" " \
                     "(\"userID\", \"name\") VALUES(" \
                     "'%s', '%s')", userID, userName);
    retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)message,SQL_NTS);
    checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "SQLExecDirect: INSERT");
    sleep(1); //sleep 1 sec

    if(strcmp(argv[4], "-1") == 0){
        printf("Writing terminate message.\"\n");
        sprintf(message, "INSERT INTO \"SqlChat_ChatMessage\" " \
                         "(\"userID\", \"index\", \"content\") VALUES(" \
                         "'-1', '0', 'Termination message.')");
        retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)message,SQL_NTS);
        checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "SQLExecDirect: INSERT");
    } else {
        printf("Writing message: \"Hi there, I will send you %d messages.\"\n", NUM_MSG);
        sprintf(message, "INSERT INTO \"SqlChat_ChatMessage\" " \
                         "(\"userID\", \"index\", \"content\") VALUES(" \
                         "'%s', '0', 'Hi there, I will send you %d messages.')", userID, NUM_MSG);

        retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)message,SQL_NTS);
        checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "SQLExecDirect: INSERT");
        /*******************************************************************************/

        sleep(1); //sleep 1 sec

        for(int i=1; i<=NUM_MSG; i++){
            sprintf(message, "UPDATE \"SqlChat_ChatMessage\" SET \"userID\"='%s', \"index\"='%d', \"content\"='Message no. %d' WHERE \"userID\"='%s'", userID, i, i, userID);
            printf("Writing message: \"Message no %d\"\n", i);

            retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)message,SQL_NTS);
            checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "SQLExecDirect: INSERT");

            sleep(1); //sleep 1 sec
        }
        /*******************************************************************************/

        //SQLExecDirect(m_hstmt0,(SQLCHAR*)"DROP TABLE CHAT_CHATMESSAGE2",SQL_NTS);
        //checkError (retcode, SQL_HANDLE_STMT, m_hstmt1, "Drop table");
    }
    retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt1);
    checkError (retcode, SQL_HANDLE_STMT, m_hstmt1, "free statement handle(1)");

    retcode = SQLFreeHandle(SQL_HANDLE_STMT, m_hstmt0);
    checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "free statement handle");

    retcode = SQLDisconnect(m_hdbc);
    checkError (retcode, SQL_HANDLE_DBC, m_hdbc, "SQLDisconnect");

    retcode = SQLFreeHandle(SQL_HANDLE_DBC,m_hdbc);
    checkError (retcode, SQL_HANDLE_DBC, m_hdbc, "SQLFreeHandle hdbc");

    retcode = SQLFreeHandle(SQL_HANDLE_ENV,m_henv);
    checkError (retcode, SQL_HANDLE_ENV, m_henv, "SQLFreeHandle henv");
}

void checkError (
    SQLRETURN       rc,
    SQLSMALLINT     handleType,
    SQLHANDLE       handle,
    const char      *msg)
{
    SQLRETURN       retcode=SQL_SUCCESS;

    SQLSMALLINT     errNum = 1;
    SQLCHAR         sqlState[6];
    SQLINTEGER      nativeError;
    SQLCHAR         errMsg[2000];
    SQLSMALLINT     textLengthPtr;
    SQLSMALLINT     buffer=1000;

    if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO) && (rc!=SQL_NO_DATA) )
    {
        while (retcode != SQL_NO_DATA)
        {

            retcode = SQLGetDiagRec (handleType, handle, errNum, sqlState, &nativeError, errMsg, buffer, &textLengthPtr);

            if (retcode == SQL_INVALID_HANDLE)
            {
                printf("checkError function was called with an invalid handle!!\n");
                exit(-1);
            }

            if ((retcode == SQL_SUCCESS) || (retcode == SQL_SUCCESS_WITH_INFO))
            {

                printf("---------------------------------------\n");
                printf("SQLSTATE: %s\n",sqlState);
                printf("native error: %d\n",nativeError);
                printf("diagnostics: %s\n",errMsg);
                printf("---------------------------------------\n");
                printf ("Fatal error : %s. Exiting in 5 seconds...\n", msg);
                sleep(5);
                exit(-1);
            }
        }
    }
    else
    {

#ifdef _DEBUG
//          printf("SUCCESS: %s\n",msg);
#endif
        /* No errors to report. */

    }
}
