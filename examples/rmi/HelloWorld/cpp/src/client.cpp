#include "ddsrmi.h"
#include "HelloWorld_InterfaceProxy.h"

#include "example_main.h"

using namespace org::opensplice::DDS_RMI;

/**
 * @brief A DDS RMI Client Example
 */

int
OSPL_MAIN(int argc, const char * argv[])
{

  std::string sServerName("HelloWorldServer");
  int iProxyInstanceID = 1;

  // Getting a DDS Runtime instance
  std::cout << "=== getDefaultRuntime" << std::endl;
  CRuntime_ref runtime = CRuntime::getDefaultRuntime();
  if (runtime.get() == NULL)
    {
      std::cout << "*** Client main: Failed to get the default Runtime "
          << std::endl;
    }

  // Starting the DDS runtime
  std::cout << "=== Runtime start" << std::endl;
  bool result = runtime->start(argc, argv);
  if (result != true)
    {
      std::cout << "*** Client main: Failed to start the Runtime " << std::endl;
    }

  std::cout << "=== Getting the server proxy ..." << std::endl;
  shared_ptr< ::DDS_RMI::HelloWorld::HelloServiceInterfaceProxy> cproxy;
  try
    {
      bool ret = DDS_Service::getServerProxy<
          ::DDS_RMI::HelloWorld::HelloServiceInterfaceProxy>(sServerName,
          iProxyInstanceID, cproxy);
      if (!ret)
        {
          std::cout << " *** Failed to get the server proxy !" << std::endl;
        }
      else
        {
          std::cout << "=== Succeeded in getting the server proxy named "
              << sServerName << " : " << std::endl;
        }
    }
  catch (SERVICE_NOT_FOUND&)
    {
      std::cout << " *** Unable to find the service !" << std::endl;
      runtime->stop();
      return 0;
    }

  try
    {
      std::cout << "=== greet" << std::endl;
      std::cout << "=== greet returns : " << cproxy->greet() << std::endl;

      std::cout << "=== stop" << std::endl;
      cproxy->stop();
      std::cout << "=== stop done" << std::endl;
    }
  catch (TIMEOUT&)
    {
      std::cout << "*** Operation TIMEOUT" << std::endl;
    }

  // Stopping the Runtime
  std::cout << "=== Runtime stop" << std::endl;
  runtime->stop();
  return 0;
}
