

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Environmental.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef EnvironmentalPlugin_152884852_h
#define EnvironmentalPlugin_152884852_h

#include "Environmental.h"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

extern "C" {

    #define EnvironmentalPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define EnvironmentalPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define EnvironmentalPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define EnvironmentalPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define EnvironmentalPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern Environmental*
    EnvironmentalPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern Environmental*
    EnvironmentalPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern Environmental*
    EnvironmentalPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    EnvironmentalPluginSupport_copy_data(
        Environmental *out,
        const Environmental *in);

    NDDSUSERDllExport extern void 
    EnvironmentalPluginSupport_destroy_data_w_params(
        Environmental *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    EnvironmentalPluginSupport_destroy_data_ex(
        Environmental *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    EnvironmentalPluginSupport_destroy_data(
        Environmental *sample);

    NDDSUSERDllExport extern void 
    EnvironmentalPluginSupport_print_data(
        const Environmental *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    EnvironmentalPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    EnvironmentalPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    EnvironmentalPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    EnvironmentalPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    EnvironmentalPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        Environmental *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    EnvironmentalPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        Environmental *out,
        const Environmental *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    EnvironmentalPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const Environmental *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EnvironmentalPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        Environmental *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EnvironmentalPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const Environmental *sample); 

    NDDSUSERDllExport extern RTIBool 
    EnvironmentalPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        Environmental **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EnvironmentalPlugin_deserialize_from_cdr_buffer(
        Environmental *sample,
        const char * buffer,
        unsigned int length);    

    NDDSUSERDllExport extern RTIBool
    EnvironmentalPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    EnvironmentalPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    EnvironmentalPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    EnvironmentalPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    EnvironmentalPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const Environmental * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    EnvironmentalPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    EnvironmentalPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    EnvironmentalPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    EnvironmentalPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const Environmental *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EnvironmentalPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        Environmental * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    EnvironmentalPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        Environmental ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    EnvironmentalPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        Environmental *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    EnvironmentalPlugin_new(void);

    NDDSUSERDllExport extern void
    EnvironmentalPlugin_delete(struct PRESTypePlugin *);

}

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* EnvironmentalPlugin_152884852_h */

