This example is based on the Chatter and MessageBoard from the 
DCPS Tutorial. It contains SQL versions of these two applications that
communicate with any ODBC-enabled database system. This example will show that
these applications can communicate with their DDS equivalents by using the 
DBMSConnect service.

The example requires the following to be available on your system:
- An ODBC library with driver
- An ODBC-enabled database system
- A configured Data Source Name  

The example is delivered with two special OpenSplice configuration file:

$OSPL_HOME/examples/dbmsconnect/dbmsconnect.xml for use in shared memory deployment and
$OSPL_HOME/examples/dbmsconnect/sp_dbmsconnet.xml for use in single process deployment.

This file also holds the configuration of the OpenSplice DBMSConnect service
for this example. It assumes a dsn (Data Source Name) to be available with
the following properties: 
- name      : 'my_dsn'
- user name : 'SYSTEM'
- password  : 'SYSTEM'

Please setup a DSN with these properties on your system or change the settings
in the dbmsconnect.xml configuration file to match a DSN to your liking.

The SQL Chatter and MessageBoard executables require some command-line 
parameters. The parameters and their meaning are specified below:

Chatter [dsn] [dsnuser] [dsnpwd] [userid] [username]
  dsn:      a Data Source Name that identifies the ODBC connection with the 
            database. Make sure this dsn is configured on your system before
            running the example.
  dsnuser:  the username to use for connecting to the dsn. Make sure the 
            username is configured for the dsn before running the example.
  dsnpwd:   the password to use for connection to the dsn. Make sure the 
            password is configured for the dsnuser before running the example.
  userid:   an integer number that uniquely identifies the sender of a message
            (Transmit a message with userid = -1 to terminate the MessageBoard.)
  username: the user-name other chatters will see when they receive one of your
            chat messages.
            
MessageBoard [dsn] [dsnuser] [dsnpwd]
  dsn:      a data source name that identifies the ODBC connection with the 
            database. Make sure this dsn is configured on your system before
            running the example.
  dsnuser:  the username to use for connecting to the dsn. Make sure the 
            username is configured for the dsn before running the example.
  dsnpwd:   the password to use for connection to the dsn. Make sure the 
            password is configured for the dsnuser before running the example.

Before running the example you should set OSPL_URI to point to the configuration file
required for the deployment method which you are using

The RUN/RUN.bat file is only an example of how the DBMSConnect example could be run and will not work
unless you have configured your environment identically.

e.g 
export OSPL_URI=file://$OSPL_HOME/examples/services/dbmsconnect/sp_dbmsconnect.xml

If you are running in a shared memory deployment it is necessary to start the OpenSplice infrastructure before running the example

Enter ospl start on the command line

On completion of running the example stop the OpenSplice infrastructure

Enter ospl stop on the command line.

See the OpenSplice Deployment Guide for a discussion of the different deployment architectures



