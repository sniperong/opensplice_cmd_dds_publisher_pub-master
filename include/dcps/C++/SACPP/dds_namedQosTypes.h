//******************************************************************
// 
//  Generated by IDL to C++ Translator
//  
//  File name: dds_namedQosTypes.h
//  Source: /home/dds/OvernightTests/overnight/ospli/tags/OSPL_V6_8_2-RC2/ubuntu1204-64/x86_64.linux-release-notest-inner/build/etc/idl/dds_namedQosTypes.idl
//  Generated: Thu Jul 27 00:46:05 2017
//  OpenSplice 6.8.2
//  
//******************************************************************
#ifndef _DDS_NAMEDQOSTYPES_H_
#define _DDS_NAMEDQOSTYPES_H_

#include "sacpp_mapping.h"
#include "dds_dcps_builtintopics.h"


namespace DDS
{
   struct NamedDomainParticipantQos;
   struct NamedPublisherQos;
   struct NamedSubscriberQos;
   struct NamedTopicQos;
   struct NamedDataWriterQos;
   struct NamedDataReaderQos;

   struct NamedDomainParticipantQos
   {
         String_mgr name;
         DomainParticipantQos domainparticipant_qos;
   };

   typedef DDS_DCPSStruct_var < NamedDomainParticipantQos> NamedDomainParticipantQos_var;
   typedef DDS_DCPSStruct_out < NamedDomainParticipantQos> NamedDomainParticipantQos_out;

   struct NamedPublisherQos
   {
         String_mgr name;
         PublisherQos publisher_qos;
   };

   typedef DDS_DCPSStruct_var < NamedPublisherQos> NamedPublisherQos_var;
   typedef DDS_DCPSStruct_out < NamedPublisherQos> NamedPublisherQos_out;

   struct NamedSubscriberQos
   {
         String_mgr name;
         SubscriberQos subscriber_qos;
   };

   typedef DDS_DCPSStruct_var < NamedSubscriberQos> NamedSubscriberQos_var;
   typedef DDS_DCPSStruct_out < NamedSubscriberQos> NamedSubscriberQos_out;

   struct NamedTopicQos
   {
         String_mgr name;
         TopicQos topic_qos;
   };

   typedef DDS_DCPSStruct_var < NamedTopicQos> NamedTopicQos_var;
   typedef DDS_DCPSStruct_out < NamedTopicQos> NamedTopicQos_out;

   struct NamedDataWriterQos
   {
         String_mgr name;
         DataWriterQos datawriter_qos;
   };

   typedef DDS_DCPSStruct_var < NamedDataWriterQos> NamedDataWriterQos_var;
   typedef DDS_DCPSStruct_out < NamedDataWriterQos> NamedDataWriterQos_out;

   struct NamedDataReaderQos
   {
         String_mgr name;
         DataReaderQos datareader_qos;
   };

   typedef DDS_DCPSStruct_var < NamedDataReaderQos> NamedDataReaderQos_var;
   typedef DDS_DCPSStruct_out < NamedDataReaderQos> NamedDataReaderQos_out;
}




#endif
