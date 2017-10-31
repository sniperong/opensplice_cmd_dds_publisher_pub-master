#include <iostream>
#include <map>
#include <vector>

#include "ddsrmi.h"

#include "ClientServer_Interface.h"
#include "ClientServer_InterfaceProxy.h"


#include <stdlib.h>
#include <stdio.h>

#include "example_main.h"

using namespace org::opensplice::DDS_RMI;

/**
* @brief A DDS RMI Client Example
*/

int OSPL_MAIN (int argc, const char * argv[]) {

  std::string sServerName ("MyCPPServer");
  int iProxyInstanceID = 1;

  // Getting a DDS Runtime instance
  std::cout << "=== getDefaultRuntime" << std::endl;
  CRuntime_ref runtime = CRuntime::getDefaultRuntime();
  if (runtime.get() == NULL)
  {
     std::cout << "*** Client main: Failed to get the default Runtime " << std::endl;
  }

  // Starting the DDS runtime
  std::cout << "=== Runtime start" << std::endl;
  bool result = runtime->start(argc, argv);
  if (result !=true)
  {
     std::cout << "*** Client main: Failed to start the Runtime " << std::endl;
  }

  std::cout << "=== Getting the server proxy ..." << std::endl;
  shared_ptr< ::DDS_RMI::ClientServer::myServerInterfaceProxy> cproxy;
  try
  {
      bool ret = DDS_Service::getServerProxy< ::DDS_RMI::ClientServer::myServerInterfaceProxy>
                      (sServerName, iProxyInstanceID, cproxy);
      if(!ret)
      {
              std::cout << " *** Failed to get the server proxy !" << std::endl;
              runtime->stop();
              return 1;
      } else
      {
              std::cout << "=== Succeeded in getting the server proxy named " << sServerName << " : " << std::endl;
      }

  }
  catch(SERVICE_NOT_FOUND &)
  {
      std::cout << " *** Failed to find the service !" << std::endl;
      runtime->stop();
      return 1;
  }

 ::ClientServer::string_seq string_seq1 ;
 ::ClientServer::long_seq long_seq1 ;
 ::ClientServer::TestStruct_seq struct_seq1 ;


    try {
    std::cout << "=== set_temperature" << std::endl;
    cproxy->set_temperature(21.5F);
    std::cout << "=== set_temperature done" << std::endl;
  } catch (TIMEOUT&) {
    std::cout << "*** set_temperature timed out" << std::endl;
  }

  try {
    std::cout << "=== set_humidity" << std::endl;
    cproxy->set_humidity(90.5F);
    std::cout << "=== set_humidity done" << std::endl;
  } catch (TIMEOUT&) {
    std::cout << "*** set_humidity timed out" << std::endl;
  }

  try {
    std::cout << "=== set_fan_level" << std::endl;
    cproxy->set_fan_level(10);
    std::cout << "=== set_fan_level done" << std::endl;
  } catch (TIMEOUT&) {
    std::cout << "*** set_fan_level timed out" << std::endl;
  }

  try {
    std::cout << "=== test_sequence_string (string sequence in " << '"'
        << "inout" << '"' << " mode)" << std::endl;
    const DDS::Char* infos = "first message";
    string_seq1.length(3);
    string_seq1[0] = DDS::string_dup(infos);
    infos = "second message";
    string_seq1[1] = DDS::string_dup(infos);
    infos = "third message";
    string_seq1[2] = DDS::string_dup(infos);
    std::cout << "=== test_sequence_string request :" << std::endl
        << "   [0]=" << string_seq1[0] << std::endl << "   [1]="
        << string_seq1[1] << std::endl << "   [2]=" << string_seq1[2]
        << std::endl;

    cproxy->test_sequence_string(string_seq1);
    std::cout << "=== test_sequence_string reply : " << std::endl
        << "   [0]=" << string_seq1[0] << std::endl << "   [1]="
        << string_seq1[1] << std::endl << "   [2]=" << string_seq1[2]
        << std::endl;
  } catch (TIMEOUT&) {
    std::cout << "*** test_sequence_string out" << std::endl;
  }

  try {
    std::cout << "=== test_sequence_long" << std::endl;
    long_seq1.length(3);
    long_seq1[0] = 1;
    long_seq1[1] = 2;
    long_seq1[2] = 3;

    cproxy->test_sequence_long(long_seq1);
    std::cout << "=== test_sequence_long done : " << std::endl << "[0]="
        << long_seq1[0] << " / [1]=" << long_seq1[1] << " / [2]="
        << long_seq1[2] << std::endl;
  } catch (TIMEOUT&) {
    std::cout << "*** test_sequence_long timed out" << std::endl;
  }

  try {
    std::cout << "=== test_sequence_TestStruct" << std::endl;
    const DDS::Char* infos = "first message";
    struct_seq1.length(3);
    struct_seq1[0].struct_member1 = DDS::string_dup(infos);
    struct_seq1[0].struct_member2 = 'a';
    struct_seq1[0].struct_member3 = 1;

    infos = "second message";
    struct_seq1[1].struct_member1 = DDS::string_dup(infos);
    struct_seq1[1].struct_member2 = 'b';
    struct_seq1[1].struct_member3 = 2;

    infos = "third message";
    struct_seq1[2].struct_member1 = DDS::string_dup(infos);
    struct_seq1[2].struct_member2 = 'c';
    struct_seq1[2].struct_member3 = 3;

    cproxy->test_sequence_TestStruct(struct_seq1);
    std::cout << "=== test_sequence_TestStruct done : " << std::endl
        << "[0] " << "member1=" << struct_seq1[0].struct_member1
        << "/member2=" << struct_seq1[0].struct_member2 << "/member3="
        << struct_seq1[0].struct_member3 << std::endl << "[1] "
        << "member1=" << struct_seq1[1].struct_member1 << "/member2="
        << struct_seq1[1].struct_member2 << "/member3="
        << struct_seq1[1].struct_member3 << std::endl << "[2] "
        << "member1=" << struct_seq1[2].struct_member1 << "/member2="
        << struct_seq1[2].struct_member2 << "/member3="
        << struct_seq1[2].struct_member3 << std::endl;
  } catch (TIMEOUT&) {
    std::cout << "*** test_sequence_TestStruct out" << std::endl;
  }

  try {
    std::cout << "=== stop" << std::endl;
    cproxy->stop();
    std::cout << "=== stop done" << std::endl;
  } catch (TIMEOUT&) {
    std::cout << "*** stop timed out" << std::endl;
  }

  // Stopping the Runtime
  std::cout << "=== Runtime stop" << std::endl;
  runtime->stop();
  return 0;
}
