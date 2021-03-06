//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: LifecycleData.h
//  Source: ../../idl/LifecycleData.idl
//  Generated: Mon Oct 23 17:12:13 2017
//  OpenSplice 6.8.2
//  
//******************************************************************
#ifndef _LIFECYCLEDATA_H_
#define _LIFECYCLEDATA_H_

#include "sacpp_mapping.h"


namespace LifecycleData
{
   struct Msg;
   typedef DDS::String_mgr writerState_t_slice;
   typedef DDS::String_mgr writerState_t[10];
   extern writerState_t_slice * writerState_t_alloc ();
   extern void writerState_t_free (writerState_t_slice *);
   extern void writerState_t_copy (writerState_t_slice* to, const writerState_t_slice* from);
   extern writerState_t_slice *writerState_t_dup (const writerState_t_slice* from);

   struct writerState_t_uniq_ {};
   typedef DDS_DCPS_VArray_var< writerState_t, writerState_t_slice, struct writerState_t_uniq_> writerState_t_var;
   typedef DDS_DCPS_Array_forany< writerState_t, writerState_t_slice, struct writerState_t_uniq_> writerState_t_forany;
   typedef DDS_DCPS_VLArray_out< writerState_t, writerState_t_slice, writerState_t_var, writerState_t_uniq_> writerState_t_out;

   struct Msg
   {
         DDS::Long userID;
         DDS::String_mgr message;
         DDS::String_mgr writerStates;
   };

   typedef DDS_DCPSStruct_var < Msg> Msg_var;
   typedef DDS_DCPSStruct_out < Msg> Msg_out;
}
template <>
LifecycleData::writerState_t_slice* DDS_DCPS_ArrayHelper < LifecycleData::writerState_t, LifecycleData::writerState_t_slice, LifecycleData::writerState_t_uniq_>::alloc ();
template <>
void DDS_DCPS_ArrayHelper < LifecycleData::writerState_t, LifecycleData::writerState_t_slice, LifecycleData::writerState_t_uniq_>::copy (LifecycleData::writerState_t_slice *to, const LifecycleData::writerState_t_slice* from);
template <>
void DDS_DCPS_ArrayHelper < LifecycleData::writerState_t, LifecycleData::writerState_t_slice, LifecycleData::writerState_t_uniq_>::free (LifecycleData::writerState_t_slice *ptr);




#endif
