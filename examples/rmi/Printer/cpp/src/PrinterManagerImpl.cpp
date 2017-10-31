/*
 * PrinterManagerImpl.cpp
 */

#include "PrinterManagerImpl.h"

#include <sstream>
#include <iostream>
#include <cmath>

PrinterManagerImpl::PrinterManagerImpl(CRuntime_ref runtime, std::string name) :
  runtime(runtime), s_name(name)
{
  PrinterInfos i1 = { "HPLaserJetColor", P_IDLE, "R324", true };
  printersInfo.push_back(i1);
  printersServicesImpl.push_back(PrinterImpl_ref(new PrinterImpl(printersInfo[0].name.in(),
      printersInfo[0].location.in(), printersInfo[0].color!=0 )));

  PrinterInfos i2 = { "BrotherHL-5280", P_IDLE, "R115", true };
  printersInfo.push_back(i2);
  printersServicesImpl.push_back(PrinterImpl_ref(new PrinterImpl(printersInfo[1].name.in(),
      printersInfo[1].location.in(), printersInfo[1].color!=0 )));

  PrinterInfos i3 = { "EPSON-EPL-7500", P_IDLE, "R245", false };
  printersInfo.push_back(i3);
  printersServicesImpl.push_back(PrinterImpl_ref(new PrinterImpl(printersInfo[2].name.in(),
      printersInfo[2].location.in(), printersInfo[2].color!=0 )));

  for (unsigned int i = 0; i < printersInfo.size(); i++)
    {
      //registering the Printers services
      bool ret =
          DDS_Service::register_interface<PrinterInterface, PrinterImpl>(
              printersServicesImpl[i], std::string(printersInfo[i].name.in()), 1);
      if (!ret)
        {
          std::cout << "Failed to register Printer service: "
              << printersInfo[i].name << std::endl;
          return;
        }

    }

}

PrinterManagerImpl::~PrinterManagerImpl()
{
}

void
PrinterManagerImpl::suspend()
{
  std::cout << "PrinterManager service stopped." << std::endl;
}

void
PrinterManagerImpl::resume()
{
  std::cout << "PrinterManager service activated." << std::endl;
}

DDS::String
PrinterManagerImpl::getClosestPrinter(DDS::String room)
{
  int nearestRoomIdx = 0;
  std::stringstream room_str(room);
  room_str.ignore(1);
  int room_int;
  room_str >> room_int;
  int min = 1000; //just a big value

  //finding the nearest room
  for (unsigned int i = 0; i < printersInfo.size(); i++)
    {
      std::stringstream room_str(std::string(printersInfo[i].location.in()).substr(1));
      int r;
      room_str >> r;

      int m = abs(room_int - r);
      if (m <= min)
        {
          min = m;
          nearestRoomIdx = i;
        }
    }
  return DDS::string_dup(printersInfo[nearestRoomIdx].name);
}

void
PrinterManagerImpl::getAllPrintersNames(::printer::NamesList& names)
{
  names.length((DDS::ULong)printersInfo.size());
  for (unsigned int i = 0; i < printersInfo.size(); i++)
    {
      names[i] = DDS::string_dup(printersInfo[i].name);
    }

}

void
PrinterManagerImpl::stop()
{
  std::cout
      << "The PrinterManager service will stop all the printers services ..."
      << std::endl;
  std::cout << "The PrinterManager service will stop ..." << std::endl;
  runtime->shutdown(false);
}
