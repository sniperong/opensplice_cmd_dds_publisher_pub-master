//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: HelloWorldData.h
//  Source: ../../idl/HelloWorldData.idl
//  Generated: Mon Oct 23 17:10:01 2017
//  OpenSplice 6.8.2
//  
//******************************************************************
#ifndef _HELLOWORLDDATA_H_
#define _HELLOWORLDDATA_H_

#include "sacpp_mapping.h"


namespace HelloWorldData
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