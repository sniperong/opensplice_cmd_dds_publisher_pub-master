#ifndef WAITSETDATASPLTYPES_H
#define WAITSETDATASPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ccpp_WaitSetData.h"


extern c_metaObject __WaitSetData_WaitSetData__load (c_base base);

extern const char *WaitSetData_Msg_metaDescriptor[];
extern const int WaitSetData_Msg_metaDescriptorArrLength;
extern const int WaitSetData_Msg_metaDescriptorLength;
extern c_metaObject __WaitSetData_Msg__load (c_base base);
struct _WaitSetData_Msg ;
extern  v_copyin_result __WaitSetData_Msg__copyIn(c_base base, const struct WaitSetData::Msg *from, struct _WaitSetData_Msg *to);
extern  void __WaitSetData_Msg__copyOut(const void *_from, void *_to);
struct _WaitSetData_Msg {
    c_long userID;
    c_string message;
};

#undef OS_API
#endif
