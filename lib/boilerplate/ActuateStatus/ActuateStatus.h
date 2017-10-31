

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ActuateStatus.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef ActuateStatus_935639761_h
#define ActuateStatus_935639761_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

extern "C" {

    extern const char *ActuateStatusTYPENAME;

}

struct ActuateStatusSeq;
#ifndef NDDS_STANDALONE_TYPE
class ActuateStatusTypeSupport;
class ActuateStatusDataWriter;
class ActuateStatusDataReader;
#endif

class ActuateStatus 
{
  public:
    typedef struct ActuateStatusSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef ActuateStatusTypeSupport TypeSupport;
    typedef ActuateStatusDataWriter DataWriter;
    typedef ActuateStatusDataReader DataReader;
    #endif

    DDS_Char *   id ;
    DDS_Char *   type ;
    DDS_Double   status ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* ActuateStatus_get_typecode(void); /* Type code */

DDS_SEQUENCE(ActuateStatusSeq, ActuateStatus);                                        

NDDSUSERDllExport
RTIBool ActuateStatus_initialize(
    ActuateStatus* self);

NDDSUSERDllExport
RTIBool ActuateStatus_initialize_ex(
    ActuateStatus* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool ActuateStatus_initialize_w_params(
    ActuateStatus* self,
    const struct DDS_TypeAllocationParams_t * allocParams);        

NDDSUSERDllExport
void ActuateStatus_finalize(
    ActuateStatus* self);

NDDSUSERDllExport
void ActuateStatus_finalize_ex(
    ActuateStatus* self,RTIBool deletePointers);

NDDSUSERDllExport
void ActuateStatus_finalize_w_params(
    ActuateStatus* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void ActuateStatus_finalize_optional_members(
    ActuateStatus* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool ActuateStatus_copy(
    ActuateStatus* dst,
    const ActuateStatus* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* ActuateStatus */

