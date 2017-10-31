#ifndef DDS_RMISPLTYPES_H
#define DDS_RMISPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ccpp_dds_rmi.h"


extern c_metaObject __dds_rmi_DDS_RMI__load (c_base base);

extern const char *DDS_RMI_Identification_metaDescriptor[];
extern const int DDS_RMI_Identification_metaDescriptorArrLength;
extern const int DDS_RMI_Identification_metaDescriptorLength;
extern c_metaObject __DDS_RMI_Identification__load (c_base base);
struct _DDS_RMI_Identification ;
extern  v_copyin_result __DDS_RMI_Identification__copyIn(c_base base, const struct DDS_RMI::Identification *from, struct _DDS_RMI_Identification *to);
extern  void __DDS_RMI_Identification__copyOut(const void *_from, void *_to);
struct _DDS_RMI_Identification {
    c_string server_class;
    c_string server_impl;
    c_long server_instance;
};

extern c_metaObject __DDS_RMI_method_list__load (c_base base);
typedef c_sequence _DDS_RMI_method_list;

extern const char *DDS_RMI_Definition_metaDescriptor[];
extern const int DDS_RMI_Definition_metaDescriptorArrLength;
extern const int DDS_RMI_Definition_metaDescriptorLength;
extern c_metaObject __DDS_RMI_Definition__load (c_base base);
struct _DDS_RMI_Definition ;
extern  v_copyin_result __DDS_RMI_Definition__copyIn(c_base base, const struct DDS_RMI::Definition *from, struct _DDS_RMI_Definition *to);
extern  void __DDS_RMI_Definition__copyOut(const void *_from, void *_to);
struct _DDS_RMI_Definition {
    c_string server_class;
    _DDS_RMI_method_list server_api;
};

extern const char *DDS_RMI_Client_Identification_metaDescriptor[];
extern const int DDS_RMI_Client_Identification_metaDescriptorArrLength;
extern const int DDS_RMI_Client_Identification_metaDescriptorLength;
extern c_metaObject __DDS_RMI_Client_Identification__load (c_base base);
struct _DDS_RMI_Client_Identification ;
extern  v_copyin_result __DDS_RMI_Client_Identification__copyIn(c_base base, const struct DDS_RMI::Client_Identification *from, struct _DDS_RMI_Client_Identification *to);
extern  void __DDS_RMI_Client_Identification__copyOut(const void *_from, void *_to);
struct _DDS_RMI_Client_Identification {
    c_string client_impl;
    c_long client_instance;
    c_ulong request_id;
};

extern const char *DDS_RMI_Request_Header_metaDescriptor[];
extern const int DDS_RMI_Request_Header_metaDescriptorArrLength;
extern const int DDS_RMI_Request_Header_metaDescriptorLength;
extern c_metaObject __DDS_RMI_Request_Header__load (c_base base);
struct _DDS_RMI_Request_Header ;
extern  v_copyin_result __DDS_RMI_Request_Header__copyIn(c_base base, const struct DDS_RMI::Request_Header *from, struct _DDS_RMI_Request_Header *to);
extern  void __DDS_RMI_Request_Header__copyOut(const void *_from, void *_to);
struct _DDS_RMI_Request_Header {
    struct _DDS_RMI_Identification service_id;
    struct _DDS_RMI_Client_Identification client_id;
};

#undef OS_API
#endif
