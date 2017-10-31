package dds.rmi.example.helloworld;

import java.io.*;
import DDS_RMI.HelloWorld.HelloServiceInterfaceProxy.*;

public class async_client {
    boolean done = false;

    synchronized void done() {
        done = true;
    }

    synchronized boolean isDone() {
        return done;
    }

    public static void main(String[] args) throws InterruptedException {

        String sServerName = "HelloWorldServer";
        int iProxyInstanceID = 1;
        async_client clientApp = new async_client();

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

        // Interface resolution and proxy creation
        org.opensplice.DDS_RMI.Sync_Print.stdOutFormat(
                "=== Server Name=%s proxyInstanceID=%d\n", sServerName,
                iProxyInstanceID);

        DDS_RMI.HelloWorld.HelloServiceInterfaceProxy l_Proxy = null;
        try {
            l_Proxy = org.opensplice.DDS_RMI.DDS_Service.getServerProxy(
                    sServerName, iProxyInstanceID,
                    DDS_RMI.HelloWorld.HelloServiceInterfaceProxy.class);
        } catch (org.opensplice.DDS_RMI.SERVICE_NOT_FOUND e) {
            org.opensplice.DDS_RMI.Sync_Print.stdOutFormat(
                    "*** Failed to find the service '%s'\n", sServerName);
            System.exit(1);
        }

        if (null != l_Proxy) {

            try {
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   === async_greet\n");

                async_client.MyGreetReplyHandler handler = clientApp.new MyGreetReplyHandler();
                l_Proxy.async_greet(handler);

                while (!clientApp.isDone()) {
                    Thread.sleep(2000);
                }

                org.opensplice.DDS_RMI.Sync_Print.stdOutFormat("   === stop\n");
                l_Proxy.stop();
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   === stop done\n");
            } catch (org.opensplice.DDS_RMI.TIMEOUT e) {
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   *** stop timed out\n");
            } catch (org.opensplice.DDS_RMI.BAD_PARAM e) {
                org.opensplice.DDS_RMI.Sync_Print
                .stdOutFormat("   *** Reply handler already active !\n");
            }

        } else {
            org.opensplice.DDS_RMI.Sync_Print
                    .stdOutFormat("*** Failed to create the proxy\n");
            System.exit(1);
        }

        org.opensplice.DDS_RMI.Sync_Print
                .stdOutFormat("=== Stopping the DDS Runtime\n");
        result = runtime.stop();
        if (!result) {
            org.opensplice.DDS_RMI.Sync_Print
                    .stdOutFormat("*** Failed to stop the DDS Runtime\n");
            System.exit(1);
        }
    }

    /**
     * Reply Handler of the 'greet' operation
     *
     */
    class MyGreetReplyHandler extends greet_Reply_Handler {
        public void greet_Reply(String ret) {
            System.out.println("async_greet returns: " + ret);
            done();
        }
    };
}
