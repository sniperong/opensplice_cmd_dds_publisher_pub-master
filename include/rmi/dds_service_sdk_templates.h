/*
 *                         OpenSplice DDS
 *
 *   This software and documentation are Copyright 2006 to 2017 PrismTech
 *   Limited, its affiliated companies and licensors. All rights reserved.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */

/**
 * @file
 *
 * @brief Templates definition
 *
 * @author Bernard MAUDRY
 *
 * Module   : RMI
 * Class   : many classes
 *
 */

#include <iostream>
#include "ccpp_dds_dcps.h"
#include "dds_service_sdk.h"
#include "sdk_sync_print.h"
#include "sdk_cinterfaceregistryimpl.h"

namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {
      /* Iterators to go through all the discovered interfaces */
      template<typename OutIterator>
        int
        CInterfaceRegistry::list(OutIterator begin, int max_interfaces)
        {
          CInterfaceRegistryImpl * registry = (CInterfaceRegistryImpl *) this;
          ::DDS_RMI::IdentificationSeq Idents = registry->listMax(
              max_interfaces);
          for (int Each = 0; Each < Idents.length(); Each++)
            {
              (*begin++) = Idents[Each];
            }
          return Idents.length();
        }

      /**
       * Resolves a set of interface instance matching the search criteria and creates proxy for them.
       */
      template<typename OutIterator>
        int
        CInterfaceRegistry::resolve(TInterfaceProperty& property,
            OutIterator begin, int max_interfaces)
        {
          CInterfaceRegistryImpl * registry = (CInterfaceRegistryImpl *) this;
          //    CInterfaceProxies proxies = registry->find(property, max_interfaces) ;
          CInterfaceProxies proxies;
          proxies.reserve(max_interfaces);
          registry->find(property, max_interfaces, proxies);
          for (unsigned int Each = 0; (Each < proxies.size()) && (Each
              < (unsigned int) max_interfaces); Each++)
            {
              (*begin++) = proxies[Each];
            }
          return proxies.size();
        }

      /**
       * Creates a writer for a specific topic (see template) and with a set of QoS. By default,
       * the writer is created on a publisher associated with the default partition.
       * Different from the DDS API, the Partition QoS can be passed at the time of creation for the writer,
       * and the SDK will take care of creating the proper Publisher if it does not exist yet.
       * Finally, the writer QoS are the DDS defaults;
       */
      template<class TopicInfo>
        CWriter<TopicInfo>::CWriter(CRuntime_ref runtime,
            const TopicInfo& info, const CWriterQoSTemplate qos)
        {
          DDS::DomainParticipant_var Participant =
              runtime->get_dds_domain_participant();

          // Create request Publisher
          DDS::PublisherQos publisherQoS;
          Participant->get_default_publisher_qos(publisherQoS);
          publisherQoS.partition = qos.partition;
          DDS::Publisher_var pub = Participant->create_publisher(publisherQoS,
              NULL, 0);
          if (NULL == pub.in())
            {
              BAD_PARAM
                  B(
                      "*** CWriter<TopicInfo>::CWriter: FAILED creation DDS::Publisher");
              Sync_Print::stdOutFormat(
                  "%s / in dds_service_sdk_templates.cpp (1)\n",
                  B.m_Msg.c_str());
              throw B;
            }

          DDS::Topic_var Topic;

          // Create topic
          typename TopicInfo::TypeTS typeSupport;
          char* typeName = typeSupport.get_type_name();
          DDS::ReturnCode_t status = typeSupport.register_type(
              Participant.in(), typeName);
          if (DDS::RETCODE_OK != status)
            {
              BAD_PARAM
                  B(
                      "*** CWriter<TopicInfo>::CWriter: FAILED register_type pour ");
              B.m_Msg += typeName;
              Sync_Print::stdOutFormat(
                  "%s / in dds_service_sdk_templates.cpp (2)\n",
                  B.m_Msg.c_str());
              throw B;
            }
          Topic = Participant->create_topic(info.TopicName.c_str(), typeName,
              info.TopicQos, NULL, 0);
          if (NULL == Topic.in())
            {
              BAD_PARAM B(
                  "*** CWriter<TopicInfo>::CWriter: FAILED creation du topic ");
              B.m_Msg += info.TopicName;
              Sync_Print::stdOutFormat(
                  "%s / in dds_service_sdk_templates.cpp (3)\n",
                  B.m_Msg.c_str());
              throw B;
            }

          // Create writer
          DDS::DataWriterQos writerQoS;
          pub->get_default_datawriter_qos(writerQoS);
          writerQoS.writer_data_lifecycle.autodispose_unregistered_instances
              = false;
          pub->copy_from_topic_qos(writerQoS, info.TopicQos);
          writerQoS.deadline = qos.deadline;
          writerQoS.destination_order = qos.destinationOrder;
          writerQoS.durability = qos.durability;
          writerQoS.latency_budget = qos.latency;
          writerQoS.lifespan = qos.lifespan;
          writerQoS.ownership = qos.ownership;
          writerQoS.ownership_strength = qos.ownershipStrength;
          writerQoS.reliability = qos.reliability;
          writerQoS.transport_priority = qos.transportPriority;
          m_ddsWriter = pub->create_datawriter(Topic.in(), writerQoS, NULL, 0);
          m_typedWriter = TopicInfo::TypedWriter::_narrow(m_ddsWriter.in());
          if (NULL == m_typedWriter.in())
            {
              BAD_PARAM
                  B(
                      "CWriter<TopicInfo>::CWriter: FAILED creation writer pour le topic ");
              B.m_Msg += info.TopicName;
              Sync_Print::stdOutFormat(
                  "%s / in dds_service_sdk_templates.cpp (4)\n",
                  B.m_Msg.c_str());
              throw B;
            }
        }

      template<class TopicInfo>
        void
        CWriter<TopicInfo>::register_instance(
            typename TopicInfo::Type& instance)
        {
          m_typedWriter->register_instance(instance);
        }

      template<class TopicInfo>
        void
        CWriter<TopicInfo>::unregister_instance(
            typename TopicInfo::Type& instance)
        {
          m_typedWriter->unregister_instance(instance, DDS::HANDLE_NIL);
        }

      template<class TopicInfo>
        void
        CWriter<TopicInfo>::write(typename TopicInfo::Type& instance)
        {
          m_typedWriter->write(instance, DDS::HANDLE_NIL);
        }

      /**
       * @brief Destroy an instance
       */
      template<class TopicInfo>
        void
        CWriter<TopicInfo>::dispose(typename TopicInfo::Type& instance)
        {
          m_typedWriter->dispose(instance, DDS::HANDLE_NIL);
        }

      template<class TopicInfo>
        CDDSWriter_ref
        CWriter<TopicInfo>::get_dds_writer()
        {
          return m_ddsWriter;
        }

      /**
       * Creates a reader for a specific topic (see template) and with a set of QoS. By default,
       * the reader is created on a subscriber associated with the default partition.
       * Different from the DDS API, the Partition QoS can be passed at the time of creation for the reader,
       * and the SDK will take care of creating the proper Subscriber if it does not exist yet.
       * Finally, the writer QoS are the DDS defaults;
       */
      template<class TopicInfo>
        CReader<TopicInfo>::CReader(CRuntime_ref runtime,
            const TopicInfo& info, const CReaderQoSTemplate qos, long millis)
        {
          DDS::DomainParticipant_var Participant =
              runtime->get_dds_domain_participant();

          // Create Subscriber
          DDS::SubscriberQos subscriberQoS;
          Participant->get_default_subscriber_qos(subscriberQoS);
          subscriberQoS.partition = qos.partition;
          DDS::Subscriber_var sub = Participant->create_subscriber(
              subscriberQoS, NULL, 0);
          if (NULL == sub.in())
            {
              BAD_PARAM
                  B(
                      "*** CReader<TopicInfo>::CReader: FAILED creation DDS::Subscriber ");
              Sync_Print::stdOutFormat(
                  "%s / in dds_service_sdk_templates.cpp (5)\n",
                  B.m_Msg.c_str());
              throw B;
            }

          DDS::Topic_var Topic;
          // Create topic
          typename TopicInfo::TypeTS typeSupport;
          char* typeName = typeSupport.get_type_name();
          DDS::ReturnCode_t status = typeSupport.register_type(
              Participant.in(), typeName);
          if (DDS::RETCODE_OK != status)
            {
              BAD_PARAM
                  B(
                      "*** CReader<TopicInfo>::CWriter: FAILED register_type pour ");
              B.m_Msg += typeName;
              Sync_Print::stdOutFormat(
                  "%s / in dds_service_sdk_templates.cpp (6)\n",
                  B.m_Msg.c_str());
              throw B;
            }
          Topic = Participant->create_topic(info.TopicName.c_str(), typeName,
              info.TopicQos, NULL, 0);
          if (NULL == Topic.in())
            {
              BAD_PARAM B(
                  "*** CReader<TopicInfo>::CReader: FAILED creation du topic ");
              B.m_Msg += info.TopicName;
              Sync_Print::stdOutFormat(
                  "%s / in dds_service_sdk_templates.cpp (7)\n",
                  B.m_Msg.c_str());
              throw B;
            }

          // Create reader
          DDS::DataReaderQos readerQoS;
          sub->get_default_datareader_qos(readerQoS);
          sub->copy_from_topic_qos(readerQoS, info.TopicQos);
          readerQoS.destination_order = qos.destinationOrder;
          readerQoS.durability = qos.durability;
          readerQoS.reliability = qos.reliability;
          m_ddsReader = sub->create_datareader(Topic.in(), readerQoS, NULL, 0);
          m_typedReader = TopicInfo::TypedReader::_narrow(m_ddsReader);
          if (NULL == m_typedReader.in())
            {
              BAD_PARAM
                  B(
                      "*** CReader<TopicInfo>::CReader: FAILED creation lecteur DDS pour le topic ");
              B.m_Msg += info.TopicName;
              Sync_Print::stdOutFormat(
                  "%s / in dds_service_sdk_templates.cpp (8)\n",
                  B.m_Msg.c_str());
              throw B;
            }
          // >>> Ticket 1781
          else if (readerQoS.durability.kind != DDS::VOLATILE_DURABILITY_QOS)
            {
              DDS::Duration_t a_timeout;
              a_timeout.sec = millis / 1000;
              millis -= a_timeout.sec * 1000;
              a_timeout.nanosec = millis * 1000000;
              status = m_typedReader->wait_for_historical_data(a_timeout);
              if (DDS::RETCODE_OK != status)
                {
                  Sync_Print::stdOutFormat(
                      "*** CReader<TopicInfo>::CReader: FAILED wait_for_historical_data in dds_service_sdk_templates.cpp (9)\n");
                }
            }
          m_condition = m_typedReader->create_readcondition(
              DDS::ANY_SAMPLE_STATE,
              DDS::ANY_VIEW_STATE,
              DDS::ALIVE_INSTANCE_STATE
                  | DDS::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE);
          status = m_waiter.attach_condition(m_condition) ;
          if (DDS::RETCODE_OK != status)
            {
              Sync_Print::stdOutFormat(
                  "*** CReader<TopicInfo>::CReader: FAILED attach_condition in dds_service_sdk_templates.cpp (10)\n");
            }
          // <<<
        }

      /**
       * Reads by default samples that have not been read yet. It returns the number of samples read,
       * or -1 if the number of available samples was exceeding the max samples.
       */
      template<class TopicInfo>
        template<typename OutputIterator>
          int
          CReader<TopicInfo>::read(OutputIterator begin, int maxsamples,
              long millis, bool use_filter)
          {
            DDS::ReturnCode_t status;

            typename TopicInfo::TypeSeq echantillons;
            DDS::SampleInfoSeq info_seq;

            m_typedReader->read(echantillons, info_seq,
                DDS::NOT_READ_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
                DDS::ALIVE_INSTANCE_STATE
                    | DDS::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE, maxsamples);

            if (0 == echantillons.length())
              {
                status = m_typedReader->return_loan(echantillons, info_seq);

                m_timeout.sec = millis / 1000;
                millis -= m_timeout.sec * 1000;
                m_timeout.nanosec = millis * 1000000;
                status = DDS::RETCODE_NO_DATA;

                while ((DDS::RETCODE_OK != status) && (DDS::RETCODE_TIMEOUT
                    != status))
                  {
                    status = m_waiter.wait(m_active, m_timeout);
                  }
                status = m_typedReader->read_w_condition(echantillons,
                    info_seq, maxsamples, m_condition.in());
              }

            int len = echantillons.length();
            for (int Each = 0; Each < len; Each++)
              {
                if (info_seq[Each].valid_data)
                  (*begin++) = echantillons[Each];
              }
            status = m_typedReader->return_loan(echantillons, info_seq);
            return len;
          }

      /**
       * Takes by default samples that have not been read yet. It returns the number of samples taken
       */
      template<class TopicInfo>
        template<typename OutputIterator>
          int
          CReader<TopicInfo>::take(OutputIterator begin, int maxsamples,
              long millis, bool use_filter)
          {
            DDS::ReturnCode_t status;

            typename TopicInfo::TypeSeq echantillons;
            DDS::SampleInfoSeq info_seq;

            m_typedReader->take(echantillons, info_seq, maxsamples,
                DDS::ANY_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
                DDS::ALIVE_INSTANCE_STATE
                    | DDS::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE);

            if (0 == echantillons.length())
              {
                status = m_typedReader->return_loan(echantillons, info_seq);

                m_timeout.sec = millis / 1000;
                millis -= m_timeout.sec * 1000;
                m_timeout.nanosec = millis * 1000000;
                status = DDS::RETCODE_NO_DATA;

                while ((DDS::RETCODE_OK != status) && (DDS::RETCODE_TIMEOUT
                    != status))
                  {
                    status = m_waiter.wait(m_active, m_timeout);
                  }
                status = m_typedReader->take_w_condition(echantillons,
                    info_seq, maxsamples, m_condition.in());
              }

            int len = echantillons.length();
            for (int Each = 0; Each < len; Each++)
              {
                if (info_seq[Each].valid_data)
                  (*begin++) = echantillons[Each];
              }
            status = m_typedReader->return_loan(echantillons, info_seq);
            return len;
          }

      /**
       * Reads all available samples. It returns the number of samples read.
       */
      template<class TopicInfo>
        template<typename SampleOutputIterator, typename InfoOutputIterator>
          int
          CReader<TopicInfo>::read(SampleOutputIterator sbegin,
              InfoOutputIterator ibegin, int maxsamples, long millis,
              bool use_filter)
          {
            DDS::ReturnCode_t status;

            typename TopicInfo::TypeSeq echantillons;
            DDS::SampleInfoSeq info_seq;

            m_typedReader->read(echantillons, info_seq, maxsamples,
                DDS::ANY_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
                DDS::ALIVE_INSTANCE_STATE
                    | DDS::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE);

            if (0 == echantillons.length())
              {
                status = m_typedReader->return_loan(echantillons, info_seq);

                m_timeout.sec = millis / 1000;
                millis -= m_timeout.sec * 1000;
                m_timeout.nanosec = millis * 1000000;
                status = DDS::RETCODE_NO_DATA;

                while ((DDS::RETCODE_OK != status) && (DDS::RETCODE_TIMEOUT
                    != status))
                  {
                    status = m_waiter.wait(m_active, m_timeout);
                  }
                status = m_typedReader->read_w_condition(echantillons,
                    info_seq, maxsamples, m_condition.in());
              }

            int len = echantillons.length();
            for (int Each = 0; Each < len; Each++)
              {
                (*sbegin++) = echantillons[Each];
                (*ibegin++) = info_seq[Each];
              }
            status = m_typedReader->return_loan(echantillons, info_seq);
            return len;
          }

      /**
       * Takes all available samples. It returns the number of samples read,
       * or -1 if the number of available samples was exceeding the max samples.
       */
      template<class TopicInfo>
        template<typename SampleOutputIterator, typename InfoOutputIterator>
          int
          CReader<TopicInfo>::take(SampleOutputIterator sbegin,
              InfoOutputIterator ibegin, int maxsamples, long millis,
              bool use_filter)
          {
            DDS::ReturnCode_t status;

            typename TopicInfo::TypeSeq echantillons;
            DDS::SampleInfoSeq info_seq;

            m_typedReader->take(echantillons, info_seq, maxsamples,
                DDS::ANY_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
                DDS::ALIVE_INSTANCE_STATE
                    | DDS::NOT_ALIVE_NO_WRITERS_INSTANCE_STATE);

            if (0 == echantillons.length())
              {
                status = m_typedReader->return_loan(echantillons, info_seq);

                m_timeout.sec = millis / 1000;
                millis -= m_timeout.sec * 1000;
                m_timeout.nanosec = millis * 1000000;
                status = DDS::RETCODE_NO_DATA;

                while ((DDS::RETCODE_OK != status) && (DDS::RETCODE_TIMEOUT
                    != status))
                  {
                    status = m_waiter.wait(m_active, m_timeout);
                  }
                status = m_typedReader->take_w_condition(echantillons,
                    info_seq, maxsamples, m_condition.in());
              }

            int len = echantillons.length();
            for (int Each = 0; Each < len; Each++)
              {
                (*sbegin++) = echantillons[Each];
                (*ibegin++) = info_seq[Each];
              }
            status = m_typedReader->return_loan(echantillons, info_seq);
            return len;
          }

      /**
       * Attaches a listener to this reader and returns the previously attached listener.
       */
      template<class TopicInfo>
        CReaderListener_ref
        CReader<TopicInfo>::set_listener(CReaderListener_ref listener,
            int status_mask)
        {
          CReaderListener_ref prev = m_listener;
          m_listener = listener;
          m_ddsReader->set_listener(m_listener.in(), status_mask);
          return prev;
        }

      template<class TopicInfo>
        CDDSReader_ref
        CReader<TopicInfo>::get_dds_reader()
        {
          return m_ddsReader;
        }

      template<class TopicInfo>
        bool
        CReader<TopicInfo>::setFilter(std::string expr,
            std::vector<std::string> params)
        {
          if (NULL == m_ddsReader.in())
            {
              Sync_Print::stdOutFormat("setFilter: No reader\n");
              return false;
            }

          m_filterExpr = expr;

          DDS::StringSeq Params;
          Params.length(params.size());
          for (unsigned int index = 0; index < params.size(); index++)
            {
              Params[index] = DDS::string_dup(params[index].c_str());
            }

          m_filterParams = Params;

          m_filter = m_ddsReader->create_querycondition(DDS::ANY_SAMPLE_STATE,
              DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE, expr.c_str(),
              Params);

          return true;
        }

      template<class TopicInfo>
        bool
        CReader<TopicInfo>::changeFilterParams(std::vector<std::string> params)
        {
          if (NULL == m_ddsReader.in())
            {
              Sync_Print::stdOutFormat("changeFilterParams: No reader\n");
              return false;
            }

          if (NULL == m_filter.in())
            {
              Sync_Print::stdOutFormat("changeFilterParams: No filter\n");
              return false;
            }

          DDS::StringSeq Params;
          Params.length(params.size());
          for (unsigned int index = 0; index < params.size(); index++)
            {
              Params[index] = DDS::string_dup(params[index].c_str());
            }

          m_filterParams = Params;

          m_filter->set_query_parameters(Params);

          return true;
        }

    }

  }
}
