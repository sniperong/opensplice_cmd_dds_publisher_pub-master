#ifdef _WIN32

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#pragma warning (disable : 4786)
#include <windows.h>

#else

#ifdef USE_NANOSLEEP
#include <time.h>
#else
#include <unistd.h>
#endif

#endif

void millisleep (int millis)
{
#ifdef USE_NANOSLEEP
  struct timespec t, r;
  t.tv_sec = millis / 1000;
  t.tv_nsec = 1000*1000*(millis % 1000);
  nanosleep (&t, &r);
#elif defined _WIN32
  Sleep (millis);
#else
  usleep (millis * 1000);
#endif
}


#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>
#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <time.h>

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
  long nRows=10;
  SQLLEN len;
  SQLRETURN retcode;
  SQLLEN row_count;
  char _time[100],_userId[100],_content[100], _userName[100];
  string s;
  int stop;

  if (argc !=4) {
        printf("USAGE: %s  <dsn> <user> <pwd>\n",argv[0]);

        return 0;
    }

  string m_dsn(argv[1]);
  string m_user(argv[2]);
  string m_pwd(argv[3]);

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
  checkError (retcode, SQL_HANDLE_STMT, m_hstmt1, "SQLAllocHandle statement handle(1)");

  const char triggerRemove[] = "DROP TRIGGER STATUS_CHANGED_TRIGGER";
  retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)triggerRemove,SQL_NTS);
  //checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "drop trigger update");

  const char triggerInsertRemove[] = "DROP TRIGGER STATUS_CHANGED_TRIGGER_INSERT";
  retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)triggerInsertRemove,SQL_NTS);
  //checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "drop trigger insert");

  retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)"DROP TABLE EVENT_WARNINGS",SQL_NTS);
  //checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "drop table");

  retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)"CREATE TABLE EVENT_WARNINGS (DESCRIPTION varchar(100), TS TIMESTAMP, USERID INTEGER, CONTENT VARCHAR(6000))",SQL_NTS);
  checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "create table");

  const char triggerInsert[]= "CREATE TRIGGER STATUS_CHANGED_TRIGGER_INSERT "      \
               "AFTER INSERT "                  \
               "ON \"Chat_ChatMessage\" "                \
               "FOR EACH ROW  "                  \
               "BEGIN  "                      \
               "INSERT INTO EVENT_WARNINGS  VALUES "        \
               "('insert', CURRENT_TIMESTAMP, "  \
               "NEW.\"userID\", NEW.\"content\"); "        \
               "END";

  retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)triggerInsert,SQL_NTS);
  //checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "create trigger insert");

  const char trigger[]=   "CREATE TRIGGER STATUS_CHANGED_TRIGGER "      \
               "AFTER UPDATE "                  \
               "ON \"Chat_ChatMessage\" "                \
               "FOR EACH ROW  "                  \
               "BEGIN  "                      \
               "INSERT INTO EVENT_WARNINGS  VALUES "        \
               "('update', CURRENT_TIMESTAMP, "  \
               "NEW.\"userID\", NEW.\"content\"); "        \
               "END";

  retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)trigger,SQL_NTS);
  //checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "create trigger update");

  retcode=SQLSetStmtAttr(m_hstmt0,SQL_ATTR_MAX_ROWS,(SQLPOINTER)nRows,SQL_IS_INTEGER);
  checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "SQLSetStmtAttr");

  retcode=SQLSetStmtAttr(m_hstmt1,SQL_ATTR_MAX_ROWS,(SQLPOINTER)nRows,SQL_IS_INTEGER);
  checkError (retcode, SQL_HANDLE_STMT, m_hstmt1, "SQLSetStmtAttr(1)");

  string saved_timestamp=string(" '2000-01-01' "); //start with an old value

  /*******************************************************************************/

  printf("SQL-MessageBoard has opened: Send a ChatMessage with userID = -1 to close it...\n\n");
  stop = 0;

  while(stop != -1){
    s="SELECT * FROM EVENT_WARNINGS WHERE TS >= "+saved_timestamp+ " ORDER BY TS";
    retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)s.c_str(),SQL_NTS);
    checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "SQLExecDirect: SELECT");

    retcode=SQLRowCount(m_hstmt0,&row_count);
    checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "SQLRowCount");

    if(row_count > 0){
      retcode = SQLFetch(m_hstmt0);

      while((retcode != SQL_NO_DATA) && (stop != -1)){
        SQLGetData(m_hstmt0,2,SQL_C_CHAR,_time,100,&len);
        SQLGetData(m_hstmt0,3,SQL_C_CHAR,_userId,100,&len);
        SQLGetData(m_hstmt0,4,SQL_C_CHAR,_content,100,&len);
        stop = atoi(_userId);

        if(stop != -1){
          s="SELECT \"name\" FROM \"Chat_NameService\" WHERE \"userID\" = " + string(_userId);
          retcode = SQLExecDirect(m_hstmt1,(SQLCHAR*)s.c_str(),SQL_NTS);
          checkError (retcode, SQL_HANDLE_STMT, m_hstmt1, "select");

          retcode=SQLRowCount(m_hstmt1,&row_count);
          checkError (retcode, SQL_HANDLE_STMT, m_hstmt1, "row count");

          SQLFetch(m_hstmt1);
          SQLGetData(m_hstmt1,1,SQL_C_CHAR,_userName,100,&len);
          SQLCloseCursor(m_hstmt1);

          if(row_count != 0){
            printf("%s: %s\n", _userName, _content);
            s="DELETE FROM EVENT_WARNINGS WHERE USERID='" + string(_userId) + "' AND " \
              "TS='" + string(_time) + "' AND CONTENT='" + string(_content) + "'";

            retcode = SQLExecDirect(m_hstmt1,(SQLCHAR*)s.c_str(),SQL_NTS);
            checkError (retcode, SQL_HANDLE_STMT, m_hstmt1, "delete");

            saved_timestamp=string("'")+ string(_time)+ string("'");
            millisleep (100);
          }
        }
        retcode = SQLFetch(m_hstmt0);
        checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "SQLFetch");
      }
      SQLCloseCursor(m_hstmt0);
    } else {
        millisleep (200);
    }
  }
  /*******************************************************************************/
  printf("Termination message received: exiting...\n");
  retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)"DELETE FROM \"SqlChat_ChatMessage\" WHERE \"userID\" = '-1'",SQL_NTS);
  checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "delete termination message");

  retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)"DROP TRIGGER STATUS_CHANGED_TRIGGER",SQL_NTS);
  checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "drop trigger");

  retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)"DROP TRIGGER STATUS_CHANGED_TRIGGER_INSERT",SQL_NTS);
  checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "drop trigger");

  retcode = SQLExecDirect(m_hstmt0,(SQLCHAR*)"DROP TABLE EVENT_WARNINGS",SQL_NTS);
  checkError (retcode, SQL_HANDLE_STMT, m_hstmt0, "drop table");

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
        millisleep(5000);
        exit(-1);
      }
    }
  }
  else
  {

#ifdef _DEBUG
//      printf("SUCCESS: %s\n",msg);
#endif
    /* No errors to report. */

  }
}
