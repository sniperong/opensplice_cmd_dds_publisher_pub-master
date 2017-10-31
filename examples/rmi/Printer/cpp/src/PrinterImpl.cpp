/*
 * PrinterImpl.cpp
 *
 *  Created on: 7 juin 2012
 *      Author: nawel
 */

#include "PrinterImpl.h"
#include "vortex_os.h"


int PrinterImpl::id;

PrinterImpl::PrinterImpl(std::string name, std::string location, bool color)
{
  infos.name = name.c_str();
  infos.location = location.c_str();
  infos.s = P_IDLE;
  infos.color = color;
  activeJobId = -1;
}

PrinterImpl::~PrinterImpl()
{
}

printer::PrinterInfos
PrinterImpl::getPrinterInfos()
{
  return infos; // may be explicit copy is needed ...
}

printer::JobReport
PrinterImpl::printDoc(DDS::String doc_name, DDS::Boolean color,
    DDS::Long & jobId)
{
  JobReport report;
  report.printer_name = DDS::string_dup(infos.name);
  report.doc_name = DDS::string_dup(doc_name);
  report.nbPrintedPages = 0;
  report.printer_result = PRINTER_OK;
  report.message = DDS::string_dup("Succeeded in printing the document !");
  jobId = 0;

  if (infos.s != P_IDLE)
    {
      report.printer_result = UNAVAILABLE;
      report.message = DDS::string_dup("The printer is still busy !");
      return report;
    }
  else if (color && !infos.color)
    {
      report.printer_result = NO_COLOR;
      report.message = DDS::string_dup("The printer is black & white !");
      return report;
    }

  if (strlen(doc_name) > 20)
    {
      report.printer_result = TOO_BIG;
      report.message = DDS::string_dup("The document is too big !");
      return report;
    }

  setPrinterStatus(P_BUSY);
  jobId = getJobId();
  if (jobId % 7 == 0)
    {
      setPrinterStatus(P_IDLE);
      report.printer_result = ERR;
      report.message = DDS::string_dup("Printer Error occured !");
    }

  std::cout << "Printing document " << doc_name << " ... " << std::endl;
  setActiveJob(jobId);
  os_time delay =
    { jobId, 0 };
  os_nanoSleep(delay);
  setPrinterStatus(P_IDLE);
  report.nbPrintedPages = strlen(doc_name);
  setActiveJob(-1);
  return report;
}

void
PrinterImpl::setPrinterStatus(Status s)
{
  Locker lock(mutex);
  infos.s = s;
}

Status
PrinterImpl::getPrinterStatus()
{
  Locker lock(mutex);
  return infos.s;
}

void
PrinterImpl::resume()
{
  std::cout << "Printer " << infos.name << " activated." << std::endl;
}

void
PrinterImpl::suspend()
{
  os_time delay_2s = { 2, 0 };
  while (getPrinterStatus() != P_IDLE)
    {
      std::cout << "Waiting for the current job to complete ..." << std::endl;
      os_nanoSleep(delay_2s);
    }
  std::cout << "Printer " << infos.name << " stopped." << std::endl;
}

DDS::Long
PrinterImpl::getActiveJob()
{
  Locker lock(mutex);
  return activeJobId;
}

void
PrinterImpl::setActiveJob(DDS::Long id)
{
  Locker lock(mutex);
  activeJobId = id;
}

int
PrinterImpl::getJobId()
{
  return PrinterImpl::id++;
}
