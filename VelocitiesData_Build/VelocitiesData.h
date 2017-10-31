//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: VelocitiesData.h
//  Source: idl/VelocitiesData.idl
//  Generated: Tue Oct 31 12:03:13 2017
//  OpenSplice 6.8.2
//  
//******************************************************************
#ifndef _VELOCITIESDATA_H_
#define _VELOCITIESDATA_H_

#include "sacpp_mapping.h"


namespace VelocitiesData
{
   struct Velocities;

   struct Velocities
   {
         DDS::Long robot_id;
         DDS::Double linear_velocity_x;
         DDS::Double linear_velocity_y;
         DDS::Double angular_velocity_z;
   };

   typedef DDS_DCPSStruct_var < Velocities> Velocities_var;
   typedef Velocities&Velocities_out;
}




#endif
