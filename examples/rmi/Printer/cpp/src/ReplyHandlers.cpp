
#include "ddsrmi.h"
#include "Printer_Interface.h"
#include "Printer_InterfaceProxy.h"

#include <sstream>


using namespace org::opensplice::DDS_RMI;
using namespace printer;
using namespace DDS_RMI::printer;

/**
 * Reply Handler of the 'printDoc' operation
 *
 */
class PrintDocReplyHandler : public virtual Printer_printDoc_Reply_Handler
{
private:
  static std::string reportMessages;
  static Mutex mutex;

public:

  static void
  addReport(std::string msg)
  {
    Locker lock(mutex);
    reportMessages = reportMessages.append(msg);
  }

  static std::string
  getReports()
  {
    return PrintDocReplyHandler::reportMessages;
  }

  void
  printDoc_Reply(JobReport report, DDS::Long jobId)
  {
    std::stringstream ss;
    ss << "\n\tPrinter: " << report.printer_name << "\n\tjobId : " << jobId
        << "\n\t document : " << report.doc_name << "\n\t pages : "
        + report.nbPrintedPages << "\n\t status : " << toString(report.printer_result)
        << "\n\t message : " << report.message;

    std::cout << "Printer report ==> " << ss.str().c_str() << std::endl;
    PrintDocReplyHandler::addReport(ss.str());
  }

  const char *
  toString(JobStatus result)
  {
    switch (result)
      {
    case ERR:
      return "P_ERR";
    case NO_COLOR:
      return "NO_COLOR";
    case PRINTER_OK:
      return "OK";
    case TOO_BIG:
      return "DOC_TOO_BIG";
    case UNAVAILABLE:
      return "UNAVAILABLE";
    default:
      return "UNKOWN_STATUS";
      }
  }
};

/**
 * Reply Handler of the 'stop' operation
 *
 */
class StopReplyHandler : public virtual PrinterManager_stop_Reply_Handler
{
private:
  Mutex mutex;

public:
  bool stopped;

  StopReplyHandler() :
    PrinterManager_stop_Reply_Handler(), mutex(), stopped(
        false)
  {
  }

  void
  stop_Reply()
  {
    Locker lock(mutex);
    stopped = true;
  }

  bool
  is_stopped()
  {
    Locker lock(mutex);
    return stopped;
  }

};
