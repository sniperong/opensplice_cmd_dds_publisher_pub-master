package dds.rmi.example.printer;

import org.opensplice.DDS_RMI.IntHolder;

import printer.JobReport;
import printer.JobStatus;
import printer.PrinterInfos;
import printer.Status;
import DDS_RMI.printer.PrinterInterface;

public class PrinterImpl extends PrinterInterface{

    public static int id = 0;
    private PrinterInfos infos;
    private int activeJobId;

    public PrinterImpl(String name, String location, boolean color){
        infos = new PrinterInfos();
        infos.name = name;
        infos.location = location;
        infos.s = Status.P_IDLE;
        infos.color = color;
        activeJobId = -1;
    }

    synchronized static int getJobId(){
        return id++;
    }

    @Override
    public void suspend() {
        while(getPrinterStatus() != Status.P_IDLE){
            try {
                System.out.println("Waiting for the current job to complete ...");
                Thread.sleep(2000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("Printer " + infos.name + " stopped.");
    }

    @Override
    public void resume() {
        System.out.println("Printer " + infos.name + " activated.");
    }

    @Override
    public JobReport printDoc(String doc_name, boolean color, IntHolder jobId) {
        if(infos.s != Status.P_IDLE){
            return new JobReport(doc_name, infos.name, JobStatus.UNAVAILABLE, (short)0, "The printer is still busy !");
        }
        else
            if(color && !infos.color){
                return new JobReport(doc_name, infos.name, JobStatus.NO_COLOR, (short)0, "The printer is black & white !");
            }

        if(doc_name.length() > 20)
            return new JobReport(doc_name, infos.name, JobStatus.TOO_BIG, (short)0, "The document is too big !");

        setPrinterStatus(Status.P_BUSY);
        jobId.value = getJobId();
        if(jobId.value % 7 == 0){
            setPrinterStatus(Status.P_IDLE);
            return new JobReport(doc_name, infos.name, JobStatus.ERR, (short)0, "Printer error occured !");
        }

        System.out.println("Printing document " + doc_name + " ... ");
        setActiveJob(jobId.value);
        try {
            Thread.sleep(jobId.value * 1000);
        } catch (InterruptedException e) {
            setPrinterStatus(Status.P_IDLE);
            return new JobReport(doc_name, infos.name, JobStatus.ERR, (short)0, "InterruptedException raised !");
        }

        setPrinterStatus (Status.P_IDLE);
        setActiveJob(-1);
        return new JobReport(doc_name, infos.name, JobStatus.PRINTER_OK, (short)doc_name.length(), "Succeeded in printing the document !");
    }

    @Override
    synchronized public int getActiveJob() {
        return activeJobId;
    }

    synchronized private void setActiveJob(int id){
        activeJobId = id;
    }

    synchronized private void setPrinterStatus(Status s){
        infos.s = s;
    }

    synchronized private Status getPrinterStatus(){
        return infos.s;
    }

    @Override
    public PrinterInfos getPrinterInfos() {
        return this.infos;
    }

}
