// For Windows build
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#include "WindowsBuild.h"
#else
#define DDS_SERVICE_API
#endif

#include "ddsrmi.h"
#include "HelloWorld_InterfaceProxy.h"

#include "example_main.h"

using namespace org::opensplice::DDS_RMI;

/**
 * @brief A DDS RMI Client Example using asynchronous invocations
 */

bool done;

/**
 * Reply Handler of the 'greet' operation
 *
 */
class MyGreetReplyHandler : public virtual DDS_RMI::HelloWorld::HelloService_greet_Reply_Handler
{
  void
  greet_Reply(DDS::String ret)
  {
    std::cout << "async_greet returns: " << ret << std::endl;
    done = true;
  }
};

int
OSPL_MAIN(int argc, const char * argv[])
{

  std::string sServerName("HelloWorldServer");
  int iProxyInstanceID = 1;
  done = false;

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
    }

  try
    {
      shared_ptr<MyGreetReplyHandler> handler(new MyGreetReplyHandler());
      std::cout << "=== async_greet" << std::endl;
      cproxy->async_greet(handler.get());
    }
  catch (BAD_PARAM)
    {
      std::cout << "*** Operation TIMEOUT" << std::endl;
    }

  os_time delay_2s = { 2, 0 };
  while(!done){
      os_nanoSleep(delay_2s);
  }

  try
    {
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
