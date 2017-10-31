

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ActuateControl.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef ActuateControl_280332832_h
#define ActuateControl_280332832_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

extern "C" {

    extern const char *ActuateControlTYPENAME;

}

struct ActuateControlSeq;
#ifndef NDDS_STANDALONE_TYPE
class ActuateControlTypeSupport;
class ActuateControlDataWriter;
class ActuateControlDataReader;
#endif

class ActuateControl 
{
  public:
    typedef struct ActuateControlSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef ActuateControlTypeSupport TypeSupport;
    typedef ActuateControlDataWriter DataWriter;
    typedef ActuateControlDataReader DataReader;
    #endif

    DDS_Char *   id ;
    DDS_Char *   type ;
    DDS_Char *   target_id ;
    DDS_Double   state ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* ActuateControl_get_typecode(void); /* Type code */

DDS_SEQUENCE(ActuateControlSeq, ActuateControl);                                        

NDDSUSERDllExport
RTIBool ActuateControl_initialize(
    ActuateControl* self);

NDDSUSERDllExport
RTIBool ActuateControl_initialize_ex(
    ActuateControl* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool ActuateControl_initialize_w_params(
    ActuateControl* self,
    const struct DDS_TypeAllocationParams_t * allocParams);        

NDDSUSERDllExport
void ActuateControl_finalize(
    ActuateControl* self);

NDDSUSERDllExport
void ActuateControl_finalize_ex(
    ActuateControl* self,RTIBool deletePointers);

NDDSUSERDllExport
void ActuateControl_finalize_w_params(
    ActuateControl* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void ActuateControl_finalize_optional_members(
    ActuateControl* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool ActuateControl_copy(
    ActuateControl* dst,
    const ActuateControl* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* ActuateControl */

