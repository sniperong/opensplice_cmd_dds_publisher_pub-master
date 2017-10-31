package dds.rmi.example;

import java.io.*;

public class client {

    /**
     * @param args
     */
    public static void main(String[] args) {
        // Parsing the arguments
        if (args.length < 2) {
            org.opensplice.DDS_RMI.Sync_Print
                    .stdOutFormat("*** Usage : dds.rmi.example.server <server_name> <proxy_instance_number>\n");
            System.exit(1);
        }
        String sServerName = args[0];
        int iProxyInstanceID = Integer.decode(args[1]);

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

        DDS_RMI.ClientServer.myServerInterfaceProxy l_Proxy = null;
        try{
            l_Proxy = org.opensplice.DDS_RMI.DDS_Service
                            .getServerProxy(sServerName, iProxyInstanceID,
                    DDS_RMI.ClientServer.myServerInterfaceProxy.class);
        } catch(org.opensplice.DDS_RMI.SERVICE_NOT_FOUND e){
            org.opensplice.DDS_RMI.Sync_Print
                .stdOutFormat("*** Failed to find the service '%s'\n", sServerName);
            System.exit(1);
        }

        if (null != l_Proxy) {
            org.opensplice.DDS_RMI.Sync_Print
                    .stdOutFormat("=== Calling the interface services (methods)\n");
            try {
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   === set_temperature\n");
                l_Proxy.set_temperature(21.5F);
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   === set_temperature done\n");
            } catch (org.opensplice.DDS_RMI.TIMEOUT e) {
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   *** set_temperature timed out\n");
                System.exit(1);
            }

            try {
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   === get_details\n");
                DDS.StringHolder Infos = new DDS.StringHolder();
                Infos.value = "Client details";
                l_Proxy.get_details(Infos);
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   === get_details done\n");
            } catch (org.opensplice.DDS_RMI.TIMEOUT e) {
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   *** get_details timed out\n");
                System.exit(1);
            }

            try {
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   === set_humidity\n");
                l_Proxy.set_humidity(90.5F);
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   === set_humidity done\n");
            } catch (org.opensplice.DDS_RMI.TIMEOUT e) {
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   *** set_humidity timed out\n");
                System.exit(1);
            }

            try {
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   === set_fan_level\n");
                l_Proxy.set_fan_level((short) 10);
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   === set_fan_level done\n");
            } catch (org.opensplice.DDS_RMI.TIMEOUT e) {
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   *** set_fan_level timed out\n");
                System.exit(1);
            }

            try {
                org.opensplice.DDS_RMI.Sync_Print.stdOutFormat("   === stop\n");
                l_Proxy.stop();
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   === stop done\n");
            } catch (org.opensplice.DDS_RMI.TIMEOUT e) {
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("   *** stop timed out\n");
                System.exit(1);
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
}
