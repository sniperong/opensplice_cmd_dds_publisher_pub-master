package dds.rmi.example.printer;

import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

import org.opensplice.DDS_RMI.DDS_Service;
import org.opensplice.DDS_RMI.SERVICE_NOT_FOUND;
import org.opensplice.DDS_RMI.TIMEOUT;
import org.opensplice.DDS_RMI.Sync_Print;

import printer.JobStatus;
import printer.NamesListHolder;
import printer.PrinterInfos;

import DDS_RMI.printer.PrinterInterfaceProxy.printDoc_Reply_Handler;
import DDS_RMI.printer.PrinterInterfaceProxy;
import DDS_RMI.printer.PrinterManagerInterfaceProxy;
import DDS_RMI.printer.PrinterManagerInterfaceProxy.stop_Reply_Handler;

public class client {

    static final ReentrantLock lock = new ReentrantLock();
    static final Condition exitCond = lock.newCondition();
    static boolean stopped = false;
    static String reportMessages = "";

    /**
     * @param args
     */
    public static void main(String[] args) {
        client exampleClient = new client();

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

        // Getting a PrinterManager proxy
        PrinterManagerInterfaceProxy printer_mger = null;
        for (int i=0; i<3 && printer_mger == null; i++){
            try {
                printer_mger = DDS_Service.getServerProxy("PrinterManagerService",
                        1, PrinterManagerInterfaceProxy.class);
            } catch (SERVICE_NOT_FOUND e) {
                org.opensplice.DDS_RMI.Sync_Print
                        .stdOutFormat("*** Failed to get the PrinterManager service proxy ... Trying again\n");
            }
        }

        if (printer_mger == null) {
            org.opensplice.DDS_RMI.Sync_Print
                    .stdOutFormat("*** Failed to get the PrinterManager service proxy\n");
            System.exit(1);
        }

        // getting all the available printers (synchronously)
        NamesListHolder names = new NamesListHolder();
        printer_mger.getAllPrintersNames(names);
        System.out.println("Available printers : ");
        for (int i = 0; i < names.value.length; i++) {
            System.out.println("\t" + names.value[i]);
        }

        // getting the closest printer (synchronously)
        String p1 = printer_mger.getClosestPrinter("R100");
        System.out.println("The closest printer to R100 is " + p1);
        String p2 = printer_mger.getClosestPrinter("R410");
        System.out.println("The closest printer to R410 is " + p2);
        String p3 = printer_mger.getClosestPrinter("R120");
        System.out.println("The closest printer to R120 is " + p3);

        try {
            //getting the Printers services
            PrinterInterfaceProxy[] printersProxies = new PrinterInterfaceProxy[3];
            printersProxies[0] = DDS_Service.getServerProxy(p1, 1,
                    PrinterInterfaceProxy.class);
            printersProxies[1] = DDS_Service.getServerProxy(p2, 1,
                    PrinterInterfaceProxy.class);
            printersProxies[2] = DDS_Service.getServerProxy(p3, 1,
                    PrinterInterfaceProxy.class);

            for (int i = 0; i < 4; i++) {
                String doc = "Document" + i;
                //requesting the printer infos synchronously
                PrinterInfos infos = printersProxies[i % 3].getPrinterInfos();
                Sync_Print
                        .stdOutFormat(
                                "Submitting document %s to printer %s located at %s \n",
                                doc, infos.name, infos.location);

                // Instantiating a reply handler
                client.PrintDocReplyHandler handler = exampleClient.new PrintDocReplyHandler();

                // submitting documents to printing asynchronously
                printersProxies[i % 3].async_printDoc(doc, true, handler);
            }

        } catch (SERVICE_NOT_FOUND e) {
            Sync_Print.stdOutFormat("*** Printer Service Not Found !");
        } catch (TIMEOUT e) {
            Sync_Print.stdOutFormat("*** Request timeout !");
            e.printStackTrace();
        } catch (Exception e) {
            e.printStackTrace();
        }

        try {
            Thread.sleep(5000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        // stopping the PrinterManager asynchronously
        StopReplyHandler handler = exampleClient.new StopReplyHandler();
        printer_mger.async_stop(handler);

        //displaying the printing report
        Sync_Print.stdOutFormat("----------------------------------\n" +
                                "-- PRINTERS REPORTS --------------\n" +
                                "----------------------------------\n");
        Sync_Print.stdOutFormat(client.reportMessages);
        Sync_Print.stdOutFormat("\n----------------------------------\n");

        // waiting for the PrinterManager to stop
        lock.lock();
        try {
            while(!stopped)
                exitCond.await();

        } catch (InterruptedException e) {
            e.printStackTrace();
        } finally {
            lock.unlock();
        }

        //stopping the runtime
        runtime.stop();

    }

    /**
     * Reply Handler of the 'printDoc' operation
     *
     */
    class PrintDocReplyHandler extends printDoc_Reply_Handler {

        synchronized void addReport(String msg){
            reportMessages += msg;
        }

        @Override
        public void printDoc_Reply(printer.JobReport report,
                int jobId) {
            String str = "\n\tPrinter: " + report.printer_name +
                      "\n\tjobId : " + jobId +
                      "\n\t document : " +  report.doc_name +
                      "\n\t pages : " + report.nbPrintedPages +
                      "\n\t status : " + toString(report.printer_result) +
                      "\n\t message : " + report.message;
            System.out.println("Printer report ==> " + str);

            addReport(str);
        }

        private String toString(JobStatus result) {
            switch (result.value()) {
            case JobStatus._ERR:
                return "P_ERR";
            case JobStatus._NO_COLOR:
                return "NO_COLOR";
            case JobStatus._PRINTER_OK:
                return "OK";
            case JobStatus._TOO_BIG:
                return "DOC_TOO_BIG";
            case JobStatus._UNAVAILABLE:
                return "UNAVAILABLE";
            default:
                return "UNKOWN_STATUS";
            }
        }
    }

    /**
     * Reply Handler of the 'stop' operation
     *
     */
    class StopReplyHandler extends stop_Reply_Handler {
        @Override
        public void stop_Reply() {
            lock.lock();
            try {
                stopped = true;
                exitCond.signal();
            } finally {
                lock.unlock();
            }
        }
    }

}
