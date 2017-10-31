#ifndef LIFECYCLEDATASPLTYPES_H
#define LIFECYCLEDATASPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ccpp_LifecycleData.h"


extern c_metaObject __LifecycleData_LifecycleData__load (c_base base);

extern c_metaObject __LifecycleData_writerState_t__load (c_base base);
typedef c_string _LifecycleData_writerState_t[10];

extern const char *LifecycleData_Msg_metaDescriptor[];
extern const int LifecycleData_Msg_metaDescriptorArrLength;
extern const int LifecycleData_Msg_metaDescriptorLength;
extern c_metaObject __LifecycleData_Msg__load (c_base base);
struct _LifecycleData_Msg ;
extern  v_copyin_result __LifecycleData_Msg__copyIn(c_base base, const struct LifecycleData::Msg *from, struct _LifecycleData_Msg *to);
extern  void __LifecycleData_Msg__copyOut(const void *_from, void *_to);
struct _LifecycleData_Msg {
    c_long userID;
    c_string message;
    c_string writerStates;
};

#undef OS_API
#endif
