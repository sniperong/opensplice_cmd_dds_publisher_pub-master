

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Velocities.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef Velocities_2013134840_h
#define Velocities_2013134840_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

extern "C" {

    extern const char *VelocitiesTYPENAME;

}

struct VelocitiesSeq;
#ifndef NDDS_STANDALONE_TYPE
class VelocitiesTypeSupport;
class VelocitiesDataWriter;
class VelocitiesDataReader;
#endif

class Velocities 
{
  public:
    typedef struct VelocitiesSeq Seq;
    #ifndef NDDS_STANDALONE_TYPE
    typedef VelocitiesTypeSupport TypeSupport;
    typedef VelocitiesDataWriter DataWriter;
    typedef VelocitiesDataReader DataReader;
    #endif

    DDS_Long   robot_id ;
    DDS_Double   linear_velocity_x ;
    DDS_Double   linear_velocity_y ;
    DDS_Double   angular_velocity_z ;

};
#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

NDDSUSERDllExport DDS_TypeCode* Velocities_get_typecode(void); /* Type code */

DDS_SEQUENCE(VelocitiesSeq, Velocities);                                        

NDDSUSERDllExport
RTIBool Velocities_initialize(
    Velocities* self);

NDDSUSERDllExport
RTIBool Velocities_initialize_ex(
    Velocities* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool Velocities_initialize_w_params(
    Velocities* self,
    const struct DDS_TypeAllocationParams_t * allocParams);        

NDDSUSERDllExport
void Velocities_finalize(
    Velocities* self);

NDDSUSERDllExport
void Velocities_finalize_ex(
    Velocities* self,RTIBool deletePointers);

NDDSUSERDllExport
void Velocities_finalize_w_params(
    Velocities* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void Velocities_finalize_optional_members(
    Velocities* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool Velocities_copy(
    Velocities* dst,
    const Velocities* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* Velocities */