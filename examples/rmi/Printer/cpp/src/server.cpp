#include <iostream>
#include <map>
#include <vector>

#include "ddsrmi.h"
#include "Printer_Interface.h"
#include "Printer_InterfaceProxy.h"
#include "PrinterManagerImpl.h"

#include "example_main.h"


using namespace org::opensplice::DDS_RMI;

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

  std::cout << "=== Creating a PrinterManager service ..." << std::endl;
  std::string sServerName("PrinterManagerService");
  shared_ptr<PrinterManagerImpl> impl(new PrinterManagerImpl(runtime, sServerName));

  //just waiting for the printers activation by the PrinterManager to have clean display !
  os_time delay_3s = { 3, 0 };
  os_nanoSleep(delay_3s);

  bool ret = DDS_Service::register_interface<
      ::DDS_RMI::printer::PrinterManagerInterface, PrinterManagerImpl>(impl,
      sServerName, 1);
  if (!ret)
    {
      std::cout << "*** Failed to register the PrinterManager interface"
          << std::endl;
      runtime->stop();
      return 1;
    }

  std::cout << "=== Ready ..." << std::endl;
  runtime->run();

  //stopping the runtime
  runtime->stop();
  return 0;
}
