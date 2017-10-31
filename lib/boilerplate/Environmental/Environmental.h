

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Environmental.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef Environmental_152884852_h
#define Environmental_152884852_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

extern "C" {

    extern const char *EnvironmentalTYPENAME;

}

struct EnvironmentalSeq;
#ifndef NDDS_STANDALONE_TYPE
class EnvironmentalTypeSupport;
class EnvironmentalDataWriter;
class EnvironmentalDataReader;
#endif

class Environmental 
{
  public:
    typedef struct EnvironmentalSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef EnvironmentalTypeSupport TypeSupport;
    typedef EnvironmentalDataWriter DataWriter;
    typedef EnvironmentalDataReader DataReader;
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

NDDSUSERDllExport DDS_TypeCode* Environmental_get_typecode(void); /* Type code */

DDS_SEQUENCE(EnvironmentalSeq, Environmental);                                        

NDDSUSERDllExport
RTIBool Environmental_initialize(
    Environmental* self);

NDDSUSERDllExport
RTIBool Environmental_initialize_ex(
    Environmental* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool Environmental_initialize_w_params(
    Environmental* self,
    const struct DDS_TypeAllocationParams_t * allocParams);        

NDDSUSERDllExport
void Environmental_finalize(
    Environmental* self);

NDDSUSERDllExport
void Environmental_finalize_ex(
    Environmental* self,RTIBool deletePointers);

NDDSUSERDllExport
void Environmental_finalize_w_params(
    Environmental* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void Environmental_finalize_optional_members(
    Environmental* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool Environmental_copy(
    Environmental* dst,
    const Environmental* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* Environmental */

