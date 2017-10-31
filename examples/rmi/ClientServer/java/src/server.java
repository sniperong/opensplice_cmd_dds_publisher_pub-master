package dds.rmi.example;

import java.io.*;
import org.opensplice.DDS_RMI.*;

public class server
{
  /**
   * @param args
   */
  public static void main(String[] args) throws InterruptedException
  {
	// Parsing the arguments
 	if (args.length < 2)
	{
		org.opensplice.DDS_RMI.Sync_Print.stdOutFormat("*** Usage : dds.rmi.example.server <server_name> <proxy_instance_number>\n") ;
		System.exit(1);
	}
    String sServerName =args[0];
 	int iInstanceID = Integer.decode( args[1]);

    org.opensplice.DDS_RMI.Sync_Print.stdOutFormat("=== Getting a DDS Runtime instance\n") ;
    org.opensplice.DDS_RMI.CRuntime runtime = org.opensplice.DDS_RMI.CRuntime.getDefaultRuntime();
    if(null == runtime)
	{
    	org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ( "*** Failed to get the DDS Runtime\n") ;
		System.exit(1);
 	}

    org.opensplice.DDS_RMI.Sync_Print.stdOutFormat("=== Starting the DDS Runtime\n") ;
    boolean result = runtime.start(args);
    if(!result)
	{
    	org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ( "*** Failed to start the DDS Runtime\n") ;
		System.exit(1);
 	}

    org.opensplice.DDS_RMI.Sync_Print.stdOutFormat("=== Creating a server\n") ;
	org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ( "=== Server Name=%s , Instance ID=%d\n", sServerName, iInstanceID) ;

	myServerImpl myServer = new myServerImpl(runtime) ;

    if(!org.opensplice.DDS_RMI.DDS_Service.register_interface
    		(myServer, sServerName, iInstanceID, DDS_RMI.ClientServer.myServerInterface.class))
	{
		    org.opensplice.DDS_RMI.Sync_Print.stdOutFormat("*** Failed to create the Server\n") ;
			System.exit(1);
	};

    //Waiting for requests
    org.opensplice.DDS_RMI.Sync_Print.stdOutFormat("=== Ready ...\n");
    runtime.run();

    runtime.stop();
    System.exit(0);
  }
}
