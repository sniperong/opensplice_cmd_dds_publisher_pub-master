

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from ActuateStatus.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_cpp_h
#include "ndds/ndds_cpp.h"
#endif
#ifndef dds_c_log_impl_h              
#include "dds_c/dds_c_log_impl.h"                                
#endif        

#ifndef cdr_type_h
#include "cdr/cdr_type.h"
#endif    

#ifndef osapi_heap_h
#include "osapi/osapi_heap.h" 
#endif
#else
#include "ndds_standalone_type.h"
#endif

#include "ActuateStatus.h"

/* ========================================================================= */
const char *ActuateStatusTYPENAME = "ActuateStatus";

DDS_TypeCode* ActuateStatus_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode ActuateStatus_g_tc_id_string = DDS_INITIALIZE_STRING_TYPECODE((50));
    static DDS_TypeCode ActuateStatus_g_tc_type_string = DDS_INITIALIZE_STRING_TYPECODE((50));
    static DDS_TypeCode_Member ActuateStatus_g_tc_members[3]=
    {

        {
            (char *)"id",/* Member name */
            {
                0,/* Representation ID */          
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL/* Ignored */
        }, 
        {
            (char *)"type",/* Member name */
            {
                1,/* Representation ID */          
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL/* Ignored */
        }, 
        {
            (char *)"status",/* Member name */
            {
                2,/* Representation ID */          
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL/* Ignored */
        }
    };

    static DDS_TypeCode ActuateStatus_g_tc =
    {{
            DDS_TK_STRUCT,/* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"ActuateStatus", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            3, /* Number of members */
            ActuateStatus_g_tc_members, /* Members */
            DDS_VM_NONE  /* Ignored */         
        }}; /* Type code for ActuateStatus*/

    if (is_initialized) {
        return &ActuateStatus_g_tc;
    }

    ActuateStatus_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&ActuateStatus_g_tc_id_string;

    ActuateStatus_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&ActuateStatus_g_tc_type_string;

    ActuateStatus_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_double;

    is_initialized = RTI_TRUE;

    return &ActuateStatus_g_tc;
}

RTIBool ActuateStatus_initialize(
    ActuateStatus* sample) {
    return ActuateStatus_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool ActuateStatus_initialize_ex(
    ActuateStatus* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return ActuateStatus_initialize_w_params(
        sample,&allocParams);

}

RTIBool ActuateStatus_initialize_w_params(
    ActuateStatus* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (allocParams) {} /* To avoid warnings */

    if (allocParams->allocate_memory){
        sample->id= DDS_String_alloc ((50));
        if (sample->id == NULL) {
            return RTI_FALSE;
        }

    } else {
        if (sample->id!= NULL) { 
            sample->id[0] = '\0';
        }
    }

    if (allocParams->allocate_memory){
        sample->type= DDS_String_alloc ((50));
        if (sample->type == NULL) {
            return RTI_FALSE;
        }

    } else {
        if (sample->type!= NULL) { 
            sample->type[0] = '\0';
        }
    }

    if (!RTICdrType_initDouble(&sample->status)) {
        return RTI_FALSE;
    }     

    return RTI_TRUE;
}

void ActuateStatus_finalize(
    ActuateStatus* sample)
{

    ActuateStatus_finalize_ex(sample,RTI_TRUE);
}

void ActuateStatus_finalize_ex(
    ActuateStatus* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    ActuateStatus_finalize_w_params(
        sample,&deallocParams);
}

void ActuateStatus_finalize_w_params(
    ActuateStatus* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }
    if (deallocParams) {} /* To avoid warnings */

    if (sample->id != NULL) {
        DDS_String_free(sample->id);
        sample->id=NULL;

    }
    if (sample->type != NULL) {
        DDS_String_free(sample->type);
        sample->type=NULL;

    }

}

void ActuateStatus_finalize_optional_members(
    ActuateStatus* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool ActuateStatus_copy(
    ActuateStatus* dst,
    const ActuateStatus* src)
{

    if (!RTICdrType_copyStringEx (
        &dst->id, src->id, 
        (50) + 1, RTI_FALSE)){
        return RTI_FALSE;
    }
    if (!RTICdrType_copyStringEx (
        &dst->type, src->type, 
        (50) + 1, RTI_FALSE)){
        return RTI_FALSE;
    }
    if (!RTICdrType_copyDouble (
        &dst->status, &src->status)) { 
        return RTI_FALSE;
    }

    return RTI_TRUE;
}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'ActuateStatus' sequence class.
*/
#define T ActuateStatus
#define TSeq ActuateStatusSeq
#define T_initialize_w_params ActuateStatus_initialize_w_params
#define T_finalize_w_params   ActuateStatus_finalize_w_params
#define T_copy       ActuateStatus_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#include "dds_cpp/generic/dds_cpp_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#include "dds_cpp_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params
#undef T_initialize_w_params
#undef TSeq
#undef T

