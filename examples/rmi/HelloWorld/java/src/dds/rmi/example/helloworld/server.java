package dds.rmi.example.helloworld;

import java.io.*;
import org.opensplice.DDS_RMI.*;
import DDS_RMI.HelloWorld.*;

public class server {

    public static void main(String[] args) throws InterruptedException {

        String sServerName = "HelloWorldServer";
        int iInstanceID = 1;

        org.opensplice.DDS_RMI.Sync_Print
                .stdOutFormat("=== Getting a DDS Runtime instance\n");
        org.opensplice.DDS_RMI.CRuntime runtime = org.opensplice.DDS_RMI.CRuntime
                .getDefaultRuntime();
        if (null == runtime) {
            org.opensplice.DDS_RMI.Sync_Print
                    .stdOutFormat("*** Failed to get the DDS Runtime\n");
            System.exit(1);
        }

        org.opensplice.DDS_RMI.Sync_Print
                .stdOutFormat("=== Starting the DDS Runtime\n");
        boolean result = runtime.start(args);
        if (!result) {
            org.opensplice.DDS_RMI.Sync_Print
                    .stdOutFormat("*** Failed to start the DDS Runtime\n");
            System.exit(1);
        }

        org.opensplice.DDS_RMI.Sync_Print
                .stdOutFormat("=== Creating a server\n");
        org.opensplice.DDS_RMI.Sync_Print.stdOutFormat(
                "=== Server Name=%s , Instance ID=%d\n", sServerName,
                iInstanceID);

        HelloServiceImpl HelloService = new HelloServiceImpl(runtime);

        if (!org.opensplice.DDS_RMI.DDS_Service.register_interface(
                HelloService, sServerName, iInstanceID,
                DDS_RMI.HelloWorld.HelloServiceInterface.class)) {
            org.opensplice.DDS_RMI.Sync_Print
                    .stdOutFormat("*** Failed to create the Server\n");
            System.exit(1);
        }
        ;

        // Waiting for requests
        org.opensplice.DDS_RMI.Sync_Print.stdOutFormat("=== Ready ...\n");
        runtime.run();

        // sleeping a little bit to make sure the shutdown is complete, as shutdown(false) has been used
        Thread.sleep(2000);

        org.opensplice.DDS_RMI.Sync_Print
                .stdOutFormat("=== Stopping the DDS Runtime\n");
        result = runtime.stop();
        if (!result) {
            org.opensplice.DDS_RMI.Sync_Print
                    .stdOutFormat("*** Failed to stop the DDS Runtime\n");
            System.exit(1);
        }

    }
}


class HelloServiceImpl extends HelloServiceInterface {
    org.opensplice.DDS_RMI.CRuntime runtime;

    public HelloServiceImpl(org.opensplice.DDS_RMI.CRuntime _runtime) {
        runtime = _runtime;
    }

    public String greet() {
        return "Hello World !";
    }

    public void stop() {
        // Stopping the Runtime
        System.out.println("=== service shutdown");
        runtime.shutdown(false);
    }

    /**
     * callback methods
     */

    @Override
    public void suspend() {
        System.out.println("HelloService stopped.");
    }

    @Override
    public void resume() {
        System.out.println("HelloService activated.");
    }
}
