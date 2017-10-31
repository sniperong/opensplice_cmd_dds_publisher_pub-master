

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Flood.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef Flood_277517566_h
#define Flood_277517566_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

extern "C" {

    extern const char *FloodTYPENAME;

}

struct FloodSeq;
#ifndef NDDS_STANDALONE_TYPE
class FloodTypeSupport;
class FloodDataWriter;
class FloodDataReader;
#endif

class Flood 
{
  public:
    typedef struct FloodSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef FloodTypeSupport TypeSupport;
    typedef FloodDataWriter DataWriter;
    typedef FloodDataReader DataReader;
    #endif

    DDS_Char *   id ;
    DDS_Char *   type ;
    DDS_Float   value ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* Flood_get_typecode(void); /* Type code */

DDS_SEQUENCE(FloodSeq, Flood);                                        

NDDSUSERDllExport
RTIBool Flood_initialize(
    Flood* self);

NDDSUSERDllExport
RTIBool Flood_initialize_ex(
    Flood* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool Flood_initialize_w_params(
    Flood* self,
    const struct DDS_TypeAllocationParams_t * allocParams);        

NDDSUSERDllExport
void Flood_finalize(
    Flood* self);

NDDSUSERDllExport
void Flood_finalize_ex(
    Flood* self,RTIBool deletePointers);

NDDSUSERDllExport
void Flood_finalize_w_params(
    Flood* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void Flood_finalize_optional_members(
    Flood* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool Flood_copy(
    Flood* dst,
    const Flood* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* Flood */

