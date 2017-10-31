/*
 * Implementation class of the PrinterManager service interface
 */

#ifndef PRINTERMANAGERIMPL_H_
#define PRINTERMANAGERIMPL_H_

#include "Printer_Interface.h"
#include "PrinterImpl.h"
#include "ddsrmi.h"

using namespace DDS_RMI::printer;
using namespace printer;

class PrinterManagerImpl : public virtual DDS_RMI::printer::PrinterManagerInterface
{
public:
  PrinterManagerImpl(CRuntime_ref runtime, std::string name);
  virtual
  ~PrinterManagerImpl();

  /*
   * Business methods
   */

  virtual DDS::String
  getClosestPrinter(DDS::String room);

  virtual void
  getAllPrintersNames(::printer::NamesList& names);

  virtual void
  stop();

  /**
   * RMI callback methods
   */

  virtual void
  suspend();

  virtual void
  resume();

private:
  typedef shared_ptr<PrinterImpl>  PrinterImpl_ref;
  CRuntime_ref runtime; // RMI runtime
  std::string s_name; //service name
  std::vector<PrinterInfos> printersInfo;
  std::vector<PrinterImpl_ref> printersServicesImpl;
};

#endif /* PRINTERMANAGERIMPL_H_ */
