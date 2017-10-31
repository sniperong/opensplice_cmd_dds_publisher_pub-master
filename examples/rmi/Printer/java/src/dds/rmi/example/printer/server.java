package dds.rmi.example.printer;

import org.opensplice.DDS_RMI.DDS_Service;

import DDS_RMI.printer.PrinterManagerInterface;

public class server {

    /**
     * @param args
     */
    public static void main(String[] args) {
        org.opensplice.DDS_RMI.Sync_Print.stdOutFormat("=== Getting the default RMI runtime ...\n") ;
        org.opensplice.DDS_RMI.CRuntime runtime = org.opensplice.DDS_RMI.CRuntime.getDefaultRuntime();
        if(null == runtime)
        {
            org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ( "*** Failed to get the default Runtime ...\n") ;
            System.exit(1);
        }

        org.opensplice.DDS_RMI.Sync_Print.stdOutFormat("=== Starting the RMI Runtime\n") ;
        boolean result = runtime.start(args);
        if(!result)
        {
            org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ( "*** Failed to start the DDS Runtime ...\n") ;
            System.exit(1);
        }

        org.opensplice.DDS_RMI.Sync_Print.stdOutFormat("=== Creating a PrinterManager service ...\n") ;
        String s_name = "PrinterManagerService";
        PrinterManagerImpl print_mger = new PrinterManagerImpl(runtime, s_name);
        try {
          //just waiting for the printers activation by the PrinterManager to have clean display !
            Thread.sleep(3000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        result = DDS_Service.register_interface(print_mger, s_name, 1, PrinterManagerInterface.class);
        if(!result)
        {
            org.opensplice.DDS_RMI.Sync_Print.stdOutFormat ( "*** Failed to create the PrinterManager service\n") ;
            System.exit(1);
        }

        //Waiting for requests
        org.opensplice.DDS_RMI.Sync_Print.stdOutFormat("=== Ready ...");
        runtime.run();

        //stopping the runtime
        runtime.stop();
    }

}
