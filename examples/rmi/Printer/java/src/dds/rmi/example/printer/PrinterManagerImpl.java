package dds.rmi.example.printer;

import java.util.Arrays;

import org.opensplice.DDS_RMI.CInterfaceManager;
import org.opensplice.DDS_RMI.CRuntime;
import org.opensplice.DDS_RMI.DDS_Service;

import printer.NamesListHolder;
import printer.PrinterInfos;
import printer.Status;
import DDS_RMI.printer.PrinterInterface;
import DDS_RMI.printer.PrinterManagerInterface;

public class PrinterManagerImpl extends PrinterManagerInterface{

    PrinterInfos[] printersInfo;
    PrinterImpl[] printersServicesImpl;
    CRuntime runtime;
    String serviceName;

    public PrinterManagerImpl(CRuntime runtime, String name){
        printersInfo = new PrinterInfos[3];
        printersServicesImpl = new PrinterImpl[3];
        printersInfo[0] = new PrinterInfos("HPLaserJetColor", Status.P_IDLE, "R324", true);
        printersServicesImpl[0] = new PrinterImpl(printersInfo[0].name, printersInfo[0].location, printersInfo[0].color);
        printersInfo[1] = new PrinterInfos("BrotherHL-5280", Status.P_IDLE, "R115", true);
        printersServicesImpl[1] = new PrinterImpl(printersInfo[1].name, printersInfo[1].location, printersInfo[1].color);
        printersInfo[2] = new PrinterInfos("EPSON-EPL-7500", Status.P_IDLE, "R245", false);
        printersServicesImpl[2] = new PrinterImpl(printersInfo[2].name, printersInfo[2].location, printersInfo[2].color);
        //registering the different Printers services
        for(int i=0; i<printersInfo.length; i++){
            boolean ret = DDS_Service.register_interface(printersServicesImpl[i], printersInfo[i].name, 1, PrinterInterface.class);
            if(!ret) {
                System.out.println("Failed to register Printer service: " + printersInfo[i].name);
                return;
            }
        }

        this.runtime = runtime;
        this.serviceName = name;

    }

    @Override
    public void suspend() {
        System.out.println("PrinterManager service stopped.");
    }

    @Override
    public void resume() {
        System.out.println("PrinterManager service activated.");

    }

    @Override
    public String getClosestPrinter(String room) {
        int nearestRoomIdx = 0;
        int roomR = Integer.valueOf(room.substring(1));
        int min = Integer.MAX_VALUE;
        //finding the nearest room
        for(int i=0; i<printersInfo.length; i++){
            int r = Integer.valueOf(printersInfo[i].location.substring(1));
            int m = Math.abs(roomR - r);
            if(m <= min){
                min = m;
                nearestRoomIdx = i;
            }
        }
        return printersInfo[nearestRoomIdx].name;
    }

    @Override
    public void getAllPrintersNames(NamesListHolder names) {
        String[] printers = new String[printersInfo.length];
        for(int i=0; i<printersInfo.length; i++){
            printers[i] = printersInfo[i].name;
        }
       names.value = Arrays.copyOf(printers, printers.length);
    }

    public void stop(){
        System.out.println("The PrinterManager service will stop all the printers services ...");
        System.out.println("The PrinterManager service will stop ...");
        runtime.shutdown(false);
    }

}
