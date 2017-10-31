#include <iostream>
#include <map>
#include <vector>

#include "ddsrmi.h"
#include "ClientServer_Interface.h"
#include "ClientServer_InterfaceProxy.h"

#include "example_main.h"

using namespace org::opensplice::DDS_RMI;


bool done = false;
/**
*  Implementation of the Idl interfaces
*/
class myServerImpl : public virtual ::DDS_RMI::ClientServer::myServerInterface {
  private:
  CRuntime_ref runtime;

  public:
    myServerImpl (CRuntime_ref runtime) : ::DDS_RMI::ClientServer::myServerInterface(),
      runtime(runtime)
    {}

    virtual void set_temperature(float temp)
    {
        std::cout << "=== Server : method >>set_temperature called" << std::endl;
    }

    virtual void set_humidity(float hum)
    {
        std::cout << "=== Server : method >>set_humidity called" << std::endl;
    }

    virtual void set_fan_level(short level)
    {
        std::cout << "=== Server : method >>set_fan_level called" << std::endl;
    }

    void test_sequence_string(::ClientServer::string_seq test)
    {
        std::cout << "=== Server : method >>test_sequence_string called" << std::endl;
        std::cout << "[0]=" << test[0] << " / [1]=" << test[1] << " / [2]=" << test[2] << std::endl ;
    }

    void test_sequence_string(::ClientServer::string_seq& test)
    {
        std::cout << "=== Server : method >>test_sequence_string called" << std::endl;
        std::cout << "[0]=" << test[0] << " / [1]=" << test[1] << " / [2]=" << test[2] << std::endl ;
        std::string reply("reply_to_");
        std::string infos = reply + std::string(test[0]);
        std::cout << "infos=" << infos << std::endl;
        test [0] = DDS::string_dup(infos.c_str());
        infos = reply + std::string(test[1]);
        test [1] = DDS::string_dup(infos.c_str());
        infos = reply + std::string(test[2]);
         test [2] = DDS::string_dup(infos.c_str());
    }

    void test_inout_string (
              DDS::String in_string,
              DDS::String& inout_string,
              DDS::String& out_string )
    {
        std::cout << "=== Server : method >>test_inout_string called" << std::endl;
        std::cout << "in_string=" << in_string << " / inout_string=" << inout_string << std::endl ;
        std::string reply("reply_to_");
        std::string infos = reply + std::string(inout_string);
        std::cout << "reply to " << inout_string << "=" << infos << std::endl;
        inout_string = DDS::string_dup(infos.c_str());
        infos = " " + std::string("out_string value");
        out_string = DDS::string_dup(infos.c_str());
    };

    void test_sequence_long(::ClientServer::long_seq test)
    {
        std::cout << "=== Server : method test_sequence_long called" << std::endl;
    }

    void test_sequence_TestStruct(::ClientServer::TestStruct_seq test)
    {
        std::cout << "=== Server : method >>test_sequence_TestStruct called" << std::endl;
    }

    virtual void get_details(DDS::Char*& infos)
    {
       std::cout << "=== Server : method >>get_details called" << std::endl;
       infos = DDS::string_dup("Server Details");
    }

    virtual void setTopicQoS(DDS::TopicQos& qos, int opIndex, int mode) {}

    virtual DDS::Short start ()
    {
        return 0 ;
    }

    virtual DDS::Short stop ()
    {
      // Stopping the Runtime
      std::cout << "=== Service shutdown" << std::endl;
      runtime->shutdown(false);
      return 0;
    }

    virtual DDS::Boolean raise_temp_to(DDS::Float temp, DDS::Long& hum, DDS::Short& level)
    {
      hum = 70 ;
      level = 7 ;
      return true ;
    }
};

/**
* @brief A DDS RMI Server Example
*/

int OSPL_MAIN (int argc, const char * argv[]) {

    std::string sServerName ("MyCPPServer");
    int iServerInstanceID = 1;

  // Getting a DDS Runtime instance
  std::cout << "=== getDefaultRuntime" << std::endl;
  CRuntime_ref runtime = CRuntime::getDefaultRuntime();
  if (runtime.get() == NULL)
  {
     std::cout << "*** Server main: Failed to get default Runtime " << std::endl;
  }

  // Starting a DDS runtime
  std::cout << "=== Runtime start" << std::endl;
  bool result = runtime->start(argc, argv);
  if (result !=true)
  {
     std::cout << "*** Server main: Failed to start the runtime " << std::endl;
  }

  std::cout << "=== Registering the server ..." << std::endl;
  shared_ptr<myServerImpl> impl(new myServerImpl(runtime));
  bool ret = DDS_Service::register_interface< ::DDS_RMI::ClientServer::myServerInterface, myServerImpl>
                          (impl, sServerName, iServerInstanceID);
  if(!ret)
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

