//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: WaitSetData.h
//  Source: ../../idl/WaitSetData.idl
//  Generated: Mon Oct 23 17:10:19 2017
//  OpenSplice 6.8.2
//  
//******************************************************************
#ifndef _WAITSETDATA_H_
#define _WAITSETDATA_H_

#include "sacpp_mapping.h"


namespace WaitSetData
{
   struct Msg;

   struct Msg
   {
         DDS::Long userID;
         DDS::String_mgr message;
   };

   typedef DDS_DCPSStruct_var < Msg> Msg_var;
   typedef DDS_DCPSStruct_out < Msg> Msg_out;
}




#endif