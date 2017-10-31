/*
 * Implementation class of the Printer service interface
 */

#ifndef PRINTERIMPL_H_
#define PRINTERIMPL_H_

#include "ddsrmi.h"
#include "Printer_Interface.h"

using namespace DDS_RMI::printer;
using namespace printer;

class PrinterImpl : public virtual PrinterInterface
{
public:
  PrinterImpl(std::string name, std::string location, bool color);
  virtual
  ~PrinterImpl();

  /*
   * Business methods
   */

  virtual ::printer::JobReport
  printDoc(DDS::String doc_name, DDS::Boolean color, DDS::Long& jobId);

  virtual DDS::Long
  getActiveJob();

  virtual ::printer::PrinterInfos
  getPrinterInfos();

  /**
   * RMI callback methods
   */

  virtual void
  suspend();

  virtual void
  resume();

private:

  PrinterInfos infos;
  int activeJobId;
  Mutex mutex;

  void
  setPrinterStatus(Status s);

  Status
  getPrinterStatus();

  void
  setActiveJob(DDS::Long id);

  static int id;

  static int
  getJobId();

};

#endif /* PRINTERIMPL_H_ */
