

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from Velocities.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef VelocitiesPlugin_2013134840_h
#define VelocitiesPlugin_2013134840_h

#include "Velocities.h"

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

    #define VelocitiesPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 
    #define VelocitiesPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define VelocitiesPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer 

    #define VelocitiesPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define VelocitiesPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern Velocities*
    VelocitiesPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern Velocities*
    VelocitiesPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern Velocities*
    VelocitiesPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    VelocitiesPluginSupport_copy_data(
        Velocities *out,
        const Velocities *in);

    NDDSUSERDllExport extern void 
    VelocitiesPluginSupport_destroy_data_w_params(
        Velocities *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    VelocitiesPluginSupport_destroy_data_ex(
        Velocities *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    VelocitiesPluginSupport_destroy_data(
        Velocities *sample);

    NDDSUSERDllExport extern void 
    VelocitiesPluginSupport_print_data(
        const Velocities *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    VelocitiesPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    VelocitiesPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    VelocitiesPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    VelocitiesPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    VelocitiesPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        Velocities *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    VelocitiesPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        Velocities *out,
        const Velocities *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool 
    VelocitiesPlugin_serialize(
        PRESTypePluginEndpointData endpoint_data,
        const Velocities *sample,
        struct RTICdrStream *stream, 
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    VelocitiesPlugin_deserialize_sample(
        PRESTypePluginEndpointData endpoint_data,
        Velocities *sample, 
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    VelocitiesPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const Velocities *sample); 

    NDDSUSERDllExport extern RTIBool 
    VelocitiesPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        Velocities **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    VelocitiesPlugin_deserialize_from_cdr_buffer(
        Velocities *sample,
        const char * buffer,
        unsigned int length);    

    NDDSUSERDllExport extern RTIBool
    VelocitiesPlugin_skip(
        PRESTypePluginEndpointData endpoint_data,
        struct RTICdrStream *stream, 
        RTIBool skip_encapsulation,  
        RTIBool skip_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern unsigned int 
    VelocitiesPlugin_get_serialized_sample_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);    

    NDDSUSERDllExport extern unsigned int 
    VelocitiesPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    VelocitiesPlugin_get_serialized_sample_min_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int
    VelocitiesPlugin_get_serialized_sample_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment,
        const Velocities * sample);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    VelocitiesPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    VelocitiesPlugin_get_serialized_key_max_size_ex(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool * overflow,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    VelocitiesPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    VelocitiesPlugin_serialize_key(
        PRESTypePluginEndpointData endpoint_data,
        const Velocities *sample,
        struct RTICdrStream *stream,
        RTIBool serialize_encapsulation,
        RTIEncapsulationId encapsulation_id,
        RTIBool serialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    VelocitiesPlugin_deserialize_key_sample(
        PRESTypePluginEndpointData endpoint_data,
        Velocities * sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool 
    VelocitiesPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        Velocities ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    VelocitiesPlugin_serialized_sample_to_key(
        PRESTypePluginEndpointData endpoint_data,
        Velocities *sample,
        struct RTICdrStream *stream, 
        RTIBool deserialize_encapsulation,  
        RTIBool deserialize_key, 
        void *endpoint_plugin_qos);

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    VelocitiesPlugin_new(void);

    NDDSUSERDllExport extern void
    VelocitiesPlugin_delete(struct PRESTypePlugin *);

}

#if (defined(RTI_WIN32) || defined (RTI_WINCE)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* VelocitiesPlugin_2013134840_h */

