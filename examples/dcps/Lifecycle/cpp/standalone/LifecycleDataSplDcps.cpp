#include "LifecycleDataSplDcps.h"
#include "ccpp_LifecycleData.h"

#include <v_copyIn.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__LifecycleData_writerState_t__copyIn(
    c_base base,
    const ::LifecycleData::writerState_t *from,
    _LifecycleData_writerState_t *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    int i1;

    for (i1 = 0; (i1 < 10) && V_COPYIN_RESULT_IS_OK(result); i1++) {
#ifdef OSPL_BOUNDS_CHECK
        if((*from)[i1]){
            (*to)[i1] = c_stringNew_s(base, (*from)[i1]);
            if((*to)[i1] == NULL) {
                result = V_COPYIN_RESULT_OUT_OF_MEMORY;
            }
        } else {
            OS_REPORT (OS_ERROR, "copyIn", 0,"Element of 'LifecycleData.*from' of type 'c_string' is NULL.");
            result = V_COPYIN_RESULT_INVALID;
        }
#else
        (*to)[i1] = c_stringNew_s(base, (*from)[i1]);
        if((*to)[i1] == NULL) {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
#endif
    }
    return result;
}

v_copyin_result
__LifecycleData_Msg__copyIn(
    c_base base,
    const struct ::LifecycleData::Msg *from,
    struct _LifecycleData_Msg *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

    to->userID = (c_long)from->userID;
#ifdef OSPL_BOUNDS_CHECK
    if(from->message){
        to->message = c_stringNew_s(base, from->message);
        if(to->message == NULL) {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'LifecycleData::Msg.message' of type 'c_string' is NULL.");
        result = V_COPYIN_RESULT_INVALID;
    }
#else
    to->message = c_stringNew_s(base, from->message);
    if(to->message == NULL) {
        result = V_COPYIN_RESULT_OUT_OF_MEMORY;
    }
#endif
#ifdef OSPL_BOUNDS_CHECK
    if(from->writerStates){
        to->writerStates = c_stringNew_s(base, from->writerStates);
        if(to->writerStates == NULL) {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'LifecycleData::Msg.writerStates' of type 'c_string' is NULL.");
        result = V_COPYIN_RESULT_INVALID;
    }
#else
    to->writerStates = c_stringNew_s(base, from->writerStates);
    if(to->writerStates == NULL) {
        result = V_COPYIN_RESULT_OUT_OF_MEMORY;
    }
#endif
    return result;
}

void
__LifecycleData_writerState_t__copyOut(
    const void *_from,
    void *_to)
{
    const _LifecycleData_writerState_t *from = (const _LifecycleData_writerState_t *)_from;
    ::LifecycleData::writerState_t *to = (::LifecycleData::writerState_t *)_to;
    int i1;

    for (i1 = 0; (i1 < 10); i1++) {
        (*to)[i1] = DDS::string_dup(((*from)[i1]) ? ((*from)[i1]) : "");
    }
}

void
__LifecycleData_Msg__copyOut(
    const void *_from,
    void *_to)
{
    const struct _LifecycleData_Msg *from = (const struct _LifecycleData_Msg *)_from;
    struct ::LifecycleData::Msg *to = (struct ::LifecycleData::Msg *)_to;
    to->userID = (::DDS::Long)from->userID;
    to->message = DDS::string_dup(from->message ? from->message : "");
    to->writerStates = DDS::string_dup(from->writerStates ? from->writerStates : "");
}

