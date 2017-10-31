#include "ddsrmi.h"
#include "HelloWorld_Interface.h"

#include "example_main.h"

using namespace org::opensplice::DDS_RMI;

/**
 *  Implementation of the HelloService IDL interface
 */
class HelloService_impl : public virtual ::DDS_RMI::HelloWorld::HelloServiceInterface
{
private:
  CRuntime_ref runtime;

public:
  HelloService_impl(CRuntime_ref runtime) :
    runtime(runtime)
  {
  }

  virtual DDS::String
  greet()
  {
    return DDS::string_dup("Hello World !");
  }

  virtual void
  stop()
  {
    // Stopping the Runtime
    std::cout << "=== service shutdown" << std::endl;
    runtime->shutdown(false);

  }

  /**
   * callback methods
   */

  void
  suspend()
  {
    std::cout << "HelloService stopped." << std::endl;
  }

  void
  resume()
  {
    std::cout << "HelloService activated." << std::endl;
  }

};

/**
 * @brief A DDS RMI Server Example
 */

int
OSPL_MAIN(int argc, const char * argv[])
{

  std::string sServerName("HelloWorldServer");
  int iServerInstanceID = 1;

  // Getting a DDS Runtime instance
  std::cout << "=== getDefaultRuntime" << std::endl;
  CRuntime_ref runtime = CRuntime::getDefaultRuntime();
  if (runtime.get() == NULL)
    {
      std::cout << "*** Server main: Failed to get default Runtime "
          << std::endl;
    }

  // Starting a DDS runtime
  std::cout << "=== Runtime start" << std::endl;
  bool result = runtime->start(argc, argv);
  if (result != true)
    {
      std::cout << "*** Server main: Failed to start the runtime " << std::endl;
      return 1;
    }

  std::cout << "=== Registering the server ..." << std::endl;
  shared_ptr<HelloService_impl> impl(new HelloService_impl(runtime));
  bool ret = DDS_Service::register_interface<
      ::DDS_RMI::HelloWorld::HelloServiceInterface, HelloService_impl>(impl,
      sServerName, iServerInstanceID);
  if (!ret)
    {
      std::cout << "*** Failed to register the server interface !" << std::endl;
      runtime->stop();
      return 1;
    }

  //Waiting for requests
  std::cout << "=== Ready ..." << std::endl;
  runtime->run();

  runtime->stop();
  return 0;
}
