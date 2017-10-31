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


#ifndef DDSRMI_H_
#define DDSRMI_H_


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#	include "WindowsBuild.h"
#else
#	define DDS_SERVICE_API
#endif

#include "sdk_cinterfaceregistryimpl.h"
#include "dds_service_sdk_templates.h"
#include <string>
#include <vector>

using namespace org::opensplice::DDS_RMI;

namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {

      /**
       * @brief this class is an implementation of the DDS_ServiceInterface on the
       * default DDS domain.
       */
      class DDS_SERVICE_API DDS_Service
      {
      public:

        /**
         * @brief registers a server interface with DDS RMI.
         *
         * @param [in] l_SrvProvider   service implementation shared pointer.
         * @param [in] p_sServerName        server name.
         * @param [in] p_iServerInstanceID  server instance id.
         * @return "true" if succeeds.
         *
         */
        template<class T1, class T2>
        static bool
        register_interface(shared_ptr<T2> l_SrvProvider,
              const std::string &p_sServerName, int p_iServerInstanceID)
        {
          return DDS_ServiceImpl->register_interface<T1, T2>(l_SrvProvider, p_sServerName, p_iServerInstanceID);
        };

        /**
         * \internal
         * @brief DEPRECATED.
         * please use @link DDS_Service::register_interface(shared_ptr<T2> l_SrvProvider,
              const std::string &p_sServerName, int p_iServerInstanceID)@endlink
           \endinternal
         */
        template<class T1, class T2>
        static inline bool
        register_interface(T2 * p_pServiceProvider,
            const std::string &p_sServerName, int p_iServerInstanceID)
        {
          bool l_bResult = false;
          CRuntime_ref l_DefaultRuntime = CRuntime::getDefaultRuntime();
          if (l_DefaultRuntime->isUsable())
            {
              // interface registration
              T1::_register_service_info();

              // service implementation class
              shared_ptr<T2> l_SrvProvider(p_pServiceProvider);
              if (l_SrvProvider.get())
                {
                  l_SrvProvider->setRuntime(l_DefaultRuntime);
                  l_SrvProvider->setInstanceNumber(p_iServerInstanceID);

                  // implementation class registration
                  CInterfaceManager_ref l_SrvProviderManager =
                      l_DefaultRuntime->register_interface(l_SrvProvider,
                          p_sServerName);
                  if (l_SrvProviderManager.get())
                    {
                      l_bResult = true;
                    }
                }
            }
          return l_bResult;
        }

        /**
         * activates the named service so that it is able to process incoming requests.
         * @param p_sServerName service name
         * @return true if successful
         */
        static bool
        run(const std::string &p_sServerName);

        /**
         * de-activates the named service.
         * @param p_sServerName service name
         * @return true if successful
         */
        static bool
        shutdown(const std::string &p_sServerName);

        /**
         * returns the service running state.
         * @param p_sServerName service name
         * @return true if the service is running, false else.
         */
        static bool
        is_running(const std::string &p_sServerName);

        /**
         * @brief unregisters an already registered interface
         *
         * @param [in] p_sServerName        server name.
         * @param [in] p_iServerInstanceID  instance id.
         *
         * @return "true" when succeeds.
         */
        static bool
        unregister_interface(const std::string &p_sServerName,
            int p_iServerInstanceID);

        /**
         * @brief creates a service proxy for a client application. This proxy allows to
         * invoke the named service operations via DDS. The proxy will represent
         * any service instance.
         * @param [in]  p_sServerName       server name.
         * @param [in]  p_iProxyInstanceID  proxy instance id.
         * @param [out] p_ServerProxy       the proxy to create.
         *
         * @return "true" when succeeds.
         */
        template<class T>
        static inline bool
        getServerProxy(const std::string & p_sServerName,
              int p_iProxyInstanceID, shared_ptr<T> &p_ServerProxy)
        {
          return DDS_ServiceImpl->getServerProxy<T>(p_sServerName,
              p_iProxyInstanceID, p_ServerProxy);
        }

        /**
           * @brief creates a service proxy for a client application. This proxy allows to
           * invoke the named service operations via DDS. The proxy will represent the provided service instance.
           * @param [in]  p_sServerName       server name.
           * @param [in]   p_iServerInstanceID server instance id.
           * @param [in]  p_iProxyInstanceID  proxy instance id.
           * @param [out] p_ServerProxy       the proxy to create.
           *
           * @return "true" when succeeds.
           */
        template<class T>
        static bool
        getServerProxy(const std::string & p_sServerName,
            int p_iServerInstanceID, int p_iProxyInstanceID,
            shared_ptr<T> &p_ServerProxy)
        {
          return DDS_ServiceImpl->getServerProxy<T>(p_sServerName,
            p_iServerInstanceID, p_iProxyInstanceID, p_ServerProxy);
        }


      private:
        static DDS_ServiceInterface_ref DDS_ServiceImpl;

      };

    }
  }
}

#define REGISTER_INTERFACE( MODULE_NAME, INTERFACE_NAME, IMPL_CLASS_NAME, SRV_PROVIDER, SRV_NAME, INSTANCE_ID ) \
	DDS_Service::register_interface< ::DDS_RMI::MODULE_NAME::INTERFACE_NAME##Interface, IMPL_CLASS_NAME>( SRV_PROVIDER, SRV_NAME, INSTANCE_ID )

#define REGISTER_RECEIVER( MODULE_NAME, TOPIC_NAME, IMPL_CLASS_NAME, RECEIVER, INSTANCE_ID ) \
    DDS_Service::register_interface< ::DDS_RMI::MODULE_NAME::TOPIC_NAME##Interface, IMPL_CLASS_NAME>( RECEIVER, #TOPIC_NAME"_receiver", INSTANCE_ID )

#define UNREGISTER_INTERFACE( INTERFACE_NAME, INSTANCE_ID ) \
	DDS_Service::unregister_interface( INTERFACE_NAME, INSTANCE_ID )

#define GET_SERVER_PROXY( MODULE_NAME, INTERFACE_NAME, SERVER_NAME, INSTANCE_ID, RESULTING_PROXY ) \
	DDS_Service::getServerProxy< ::DDS_RMI::MODULE_NAME::INTERFACE_NAME##InterfaceProxy>( SERVER_NAME, INSTANCE_ID, RESULTING_PROXY )

/**
 * \internal
 * @brief Creates a topic publisher.
 *
 * @param [in]  p_sIDLTopicName         topic IDL struct name.
 * @param [in]  p_sReceiverName         receivers names.
 * @param [in]  p_iPublisherInstanceID  publisher instance id.
 * @param [out] p_TopicPublisher        the publisher to create.
 *
 * @return "true" when succeeds.
 *
 * It is recommanded to use this function via the GET_TOPIC_PUBLISHER macro
 * Example: creating a publisher for a topic named myModule::myTopic
 * shared_ptr<  ::DDS_RMI::myModule::myTopicInterfaceProxy> l_Publisher;
 * if
 *     (  GET_TOPIC_PUBLISHER( module_name, topic_name, instance_id, l_Publisher ) )
 * {
 *     // publishing
 *     l_Publisher->myTopic_publish( ... );
 * }
 * else
 * {
 *     // ERROR
 * }
 * \endinternal
 */
template<class T>
  bool
  getTopicPublisher(const std::string & p_sIDLTopicName,
      const std::string & p_sReceiverName, int p_iPublisherInstanceID,
      shared_ptr<T> &p_TopicPublisher)
  {
    bool l_bResult = false;
    CRuntime_ref l_DefaultRuntime = CRuntime::getDefaultRuntime();
    if (l_DefaultRuntime->isUsable())
      {
        T::_register_service_info();

        std::vector<CInterfaceProxy_ref> l_aProxies;
        TInterfaceProperty l_InterfaceProperty;
        l_InterfaceProperty.server_class = DDS::string_dup(
            p_sIDLTopicName.c_str());
        l_InterfaceProperty.server_impl = DDS::string_dup(
            p_sReceiverName.c_str());
        l_InterfaceProperty.properties[std::string("diffusion")] = std::string(
            "true");
        l_aProxies.resize(1);

        CInterfaceRegistry_ref l_Registry = l_DefaultRuntime->getRegistry();
        if (0
            < l_Registry->resolve<std::vector<CInterfaceProxy_ref>::iterator> (
                l_InterfaceProperty, l_aProxies.begin(), 1))
          {
            l_aProxies[0]->setIdentification(p_sIDLTopicName + "_Publisher",
                p_iPublisherInstanceID);
            p_TopicPublisher = dynamic_cast<T*> (l_aProxies[0].get());
            if (p_TopicPublisher.get())
              {
                l_bResult = true;
              }
          }
      }
    return l_bResult;
  }

#define GET_TOPIC_PUBLISHER( MODULE_NAME, TOPIC_NAME, INSTANCE_ID, RESULTING_PUBLISHER ) \
	getTopicPublisher< ::DDS_RMI::MODULE_NAME::TOPIC_NAME##InterfaceProxy>( "::"#MODULE_NAME"::"#TOPIC_NAME, #TOPIC_NAME"_receiver", INSTANCE_ID, RESULTING_PUBLISHER )

/**
 * \internal
 * @brief reads topic samples.
 *
 * @param [in]  p_sTopicName        topic name.
 * @param [out] p_aSamples          out samples sequence.
 * @param [in]  p_iNbSamplesToRead  the samples max number to be read.
 * @return the read samples number when succeeds, -1 when fails.
 *
 *
 * It is recommended to use DECLARE_TOPIC_INFO and READ_INITIAL_DATA macros.
 *
 * Example: reading a topic whose data struct name is myModule::myTopic
 * 	// declaring the topic information
 * 	DECLARE_TOPIC_INFO( "myModule", "myTopic")
 * //reading the samples
 * myTopic_list l_aSamples;
 * int l_iNbSamplesRead = READ_INITIAL_DATA( "myModule", "myTopic", l_aSamples );
 * if
 *     ( -1 == l_iNbSamplesRead )
 * {
 *     // ERROR.
 * }
 * else if
 *     ( 0 == l_iNbSamplesRead )
 * {
 *     // No samples.
 * }
 * else
 * {
 *     // there are samples.
 *     l_aSamples[0]...
 * }
 * \endinternal
 */
template<class TopicInfo, class TopicProxy>
  int
  readData(const std::string & p_sTopicName, std::vector<
      typename TopicInfo::Type> &p_aSamples, int p_iNbSamplesToRead = 1)
  {
    int l_iNbSamplesRead = -1;
    CRuntime_ref l_DefaultRuntime = CRuntime::getDefaultRuntime();
    if (l_DefaultRuntime->isUsable())
      {
        TopicInfo l_Info;
        l_Info.TopicName = p_sTopicName;

        // getting the default Qos
        DDS::DomainParticipant_var l_Participant =
            l_DefaultRuntime->get_dds_domain_participant();
        l_Participant->get_default_topic_qos(l_Info.TopicQos);

        // Using a temporary proxy to set the topic Qos
        shared_ptr<TopicProxy> l_DummyProxy = new TopicProxy();
        l_DummyProxy->setTopicQoS(l_Info.TopicQos, 0, 0);

        // The DatReader durability must be equal to that of the topic
        CReaderQoSTemplate l_ReaderQoS = DEFAULT_READER_QOS_TEMPLATE;
        l_ReaderQoS.durability.kind = l_Info.TopicQos.durability.kind;

        // DataReader creation and et data reading.
        CReader<TopicInfo>
            l_Reader(l_DefaultRuntime, l_Info, l_ReaderQoS, 1000);
        p_aSamples.resize(p_iNbSamplesToRead);
        l_iNbSamplesRead = l_Reader.read(p_aSamples.begin(),
            p_iNbSamplesToRead, 1000);
      }
    return l_iNbSamplesRead;
  }

#define DECLARE_TOPIC_INFO(MODULE_NAME,TOPIC_NAME) \
    struct TOPIC_NAME##TopicInfo \
    { \
        typedef  ::DDS_RMI::MODULE_NAME::TOPIC_NAME::TOPIC_NAME##_request Type; \
        typedef  ::DDS_RMI::MODULE_NAME::TOPIC_NAME::TOPIC_NAME##_requestTypeSupport TypeTS; \
        typedef  ::DDS_RMI::MODULE_NAME::TOPIC_NAME::TOPIC_NAME##_requestSeq TypeSeq; \
        typedef  ::DDS_RMI::MODULE_NAME::TOPIC_NAME::TOPIC_NAME##_requestDataWriter TypedWriter; \
        typedef  ::DDS_RMI::MODULE_NAME::TOPIC_NAME::TOPIC_NAME##_requestDataWriter_var TypedWriter_ref; \
        typedef  ::DDS_RMI::MODULE_NAME::TOPIC_NAME::TOPIC_NAME##_requestDataReader TypedReader; \
        typedef  ::DDS_RMI::MODULE_NAME::TOPIC_NAME::TOPIC_NAME##_requestDataReader_var TypedReader_ref; \
        std::string TopicName; \
        DDS::TopicQos TopicQos; \
    }; \
    typedef std::vector<TOPIC_NAME##TopicInfo::Type> TOPIC_NAME##_list;

#define READ_INITIAL_DATA( MODULE_NAME, TOPIC_NAME, RESULTING_SAMPLES, NB_SAMPLES_TO_READ ) \
    readData<TOPIC_NAME##TopicInfo, ::DDS_RMI::MODULE_NAME::TOPIC_NAME##InterfaceProxy>( "topic___"#MODULE_NAME"__"#TOPIC_NAME"__"#TOPIC_NAME"_publish_request", RESULTING_SAMPLES, NB_SAMPLES_TO_READ )

/**
 * conversion macros.
 */
#define STD_STRING_TO_DDS_STRING( STD_STRING ) (DDS::string_dup((DDS::String)((STD_STRING).c_str())))
#define QSTRING_TO_DDS_STRING( QSTRING ) (DDS::string_dup((DDS::String)((QSTRING).toStdString().c_str())))

#endif /* DDSRMI_H_ */
