#include <sstream>
#include <map>
#include <vector>

#include "ddsrmi.h"
#include "Printer_Interface.h"
#include "Printer_InterfaceProxy.h"
#include "ReplyHandlers.cpp"

#include "example_main.h"

using namespace org::opensplice::DDS_RMI;
using namespace printer;
using namespace DDS_RMI::printer;


std::string PrintDocReplyHandler::reportMessages;
Mutex PrintDocReplyHandler::mutex;

int
OSPL_MAIN(int argc, const char * argv[])
{

  // Getting a DDS Runtime instance
  std::cout << "=== Getting the default RMI runtime ..." << std::endl;
  CRuntime_ref runtime = CRuntime::getDefaultRuntime();
  if (runtime.get() == NULL)
    {
      std::cout << "*** Server main: Failed to get default Runtime "
          << std::endl;
      return 1;
    }

  // Starting a DDS runtime
  std::cout << "=== Starting the RMI Runtime ..." << std::endl;
  bool result = runtime->start(argc, argv);
  if (result != true)
    {
      std::cout << "*** Server main: Failed to start the runtime " << std::endl;
      return 1;
    }

  // Getting a PrinterManager proxy
  std::cout << "=== Getting the PrinterManager proxy ..." << std::endl;
  std::string sServerName("PrinterManagerService");
  shared_ptr< ::DDS_RMI::printer::PrinterManagerInterfaceProxy> printer_mger;
  for(int i=0; i<3 && printer_mger.get() == NULL; i++)
    {
      try
         {
           result = DDS_Service::getServerProxy<
               ::DDS_RMI::printer::PrinterManagerInterfaceProxy>(sServerName, 1,
               printer_mger);

           if (!result)
             std::cout << " *** Failed to get the PrinterManager proxy !"
                 << std::endl;
           else
             std::cout << "=== Succeeded in getting the PrinterManager proxy named "
                 << std::endl;
         }
       catch (SERVICE_NOT_FOUND &)
         {
           std::cout << "*** The PrinterManagerService is not found ! ... Trying again" << std::endl;
           //runtime->stop();
           //return 1;
         }
    }

  // getting all the available printers (synchronously)
  NamesList names;
  printer_mger->getAllPrintersNames(names);
  std::cout << "Available printers : " << std::endl;
  for(unsigned int i=0; i<names.length(); i++)
    std::cout << "\t" << names[i] << std::endl;

  // getting the closest printer (synchronously)
  DDS::String p1 = printer_mger->getClosestPrinter(DDS::string_dup("R100"));
  std::cout << "The closest printer to R100 is " << p1 << std::endl;
  DDS::String p2 = printer_mger->getClosestPrinter(DDS::string_dup("R410"));
  std::cout << "The closest printer to R410 is " << p2 << std::endl;
  DDS::String p3 = printer_mger->getClosestPrinter(DDS::string_dup("R220"));
  std::cout << "The closest printer to R120 is " << p3 << std::endl;


  try{
      //getting the Printers services
      shared_ptr<PrinterInterfaceProxy> printersProxies[3];
      DDS_Service::getServerProxy<PrinterInterfaceProxy>(p1, 1, printersProxies[0]);
      DDS_Service::getServerProxy<PrinterInterfaceProxy>(p2, 1, printersProxies[1]);
      DDS_Service::getServerProxy<PrinterInterfaceProxy>(p3, 1, printersProxies[2]);

      for (int i = 0; i < 4; i++) {
           std::stringstream doc;
           doc << "Document_" << i;
           //requesting the printer infos synchronously
           PrinterInfos infos = printersProxies[i % 3]->getPrinterInfos();
           Sync_Print::stdOutFormat(
                           "Submitting document %s to printer %s located at %s \n",
                           doc.str().c_str(), infos.name.in(), infos.location.in());

           // Instantiating a reply handler
           shared_ptr<PrintDocReplyHandler> handler(new PrintDocReplyHandler());

           // submitting documents to printing asynchronously
           printersProxies[i % 3]->async_printDoc(DDS::string_dup(doc.str().c_str()), true, handler.get());
       }


  }
  catch (SERVICE_NOT_FOUND &) {
      std::cout <<"*** Printer Service Not Found !" <<std::endl;
  }
  catch (TIMEOUT &) {
      std::cout << "*** Request timeout !" << std::endl;
  }
  os_time delay_5s = { 5, 0 };
  os_nanoSleep(delay_5s);

  // stopping the PrinterManager asynchronously
  Sync_Print::stdOutFormat("Requesting the PrinterManager to stop ...\n");
  shared_ptr<StopReplyHandler> stopHandler(new StopReplyHandler());
  printer_mger->async_stop(stopHandler.get());

  //displaying the printing report
  Sync_Print::stdOutFormat("----------------------------------\n");
  Sync_Print::stdOutFormat("-- PRINTERS REPORTS --------------\n");
  Sync_Print::stdOutFormat("----------------------------------\n");
  Sync_Print::stdOutFormat(PrintDocReplyHandler::getReports().c_str());
  Sync_Print::stdOutFormat("\n----------------------------------\n");

  // waiting for the PrinterManager to stop
  os_time delay_2s = { 2, 0 };
  while(!stopHandler->is_stopped())
    os_nanoSleep(delay_2s);

  // Stopping the Runtime
  std::cout << "=== Runtime stop" << std::endl;
  runtime->stop();
  return 0;
}
