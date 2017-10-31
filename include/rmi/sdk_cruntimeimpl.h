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
 * @brief Core RMI runtime implementation class
 */

#ifndef _SDK_CRUNTIMEIMPL_HPP_
#define _SDK_CRUNTIMEIMPL_HPP_
#include "PriorityThreadPool.h"

// For Windows build.
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#include "WindowsBuild.h"
#else
#define DDS_SERVICE_API
#endif

#include <map>
#include "dds_service_sdk.h"
#include "sdk_cinterfaceregistryimpl.h"
#include "RmiConfiguration.h"
#include "PriorityThreadPool.h"
#include "tpsWaitingRequestsThread.h"

#define SDK_REQUEST 0
#define SDK_REPLY 1

namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {

#define WAIT_REPLY_DEFAULT_TIMEOUT  600000 // 10min

      class DDS_SERVICE_API CInterfaceRegistryImpl;
      typedef shared_ptr<CInterfaceRegistryImpl> CInterfaceRegistryImpl_ref;

      typedef CInterfaceProxy_ref
      (*TInterfaceFactory)(::DDS_RMI::Identification& Ident);

      /**
       * @brief Runtime Implementation class
       */
      class CRuntimeImpl : public CRuntime
      {
      public:
        /**
         * @brief Constructor providing the domain URI
         */
        CRuntimeImpl(const DDS::Long & domain);

        /**
         * @brief Destructor
         */
        virtual
        ~CRuntimeImpl();

        virtual bool
        start(int argc, const char *argv[]);

        virtual bool
        stop();

        virtual void
        run();

        virtual void
        shutdown(bool wait_for_completion = true);

        virtual bool
        is_running();

        virtual CInterfaceManager_ref
            register_interface(const CInterface_ref & svc,
                const std::string & name);

        /**
         * \internal
         * @brief Create the interface manager which will be associated
         * with the given interface and properties (serveur side)
         * \endinternal
         */
//        virtual CInterfaceManager_ref
//        register_interface(const CInterface_ref & svc,
//            const TInterfaceProperty & property);


        virtual void
        unregister_interface(const std::string& name, int instance);

        virtual CInterfaceManager_ref
        lookup_interface_manager(const std::string & name);

        virtual CInterfaceRegistry_ref
        getRegistry();

        virtual DDS::DomainParticipant_var &
        get_dds_domain_participant();

        virtual bool
        isUsable();

        virtual unsigned int
        getTimeout()
        {
          return m_iTimeout;
        }

        virtual void
        setTimeout(unsigned int millis)
        {
          m_iTimeout = millis;
        }

        /**
         * @brief Get the DDS Publisher used by this runtime for its infrastructure
         * activities (not for the Interfaces topics)
         */
        virtual DDS::Publisher_var&
        getPublisher();

        /**
         * @brief Get the DDS Subscriber used by this runtime for its infrastructure
         * activities (not for the Interfaces topics)
         */
        virtual DDS::Subscriber_var&
        getSubscriber();

        /**
         * @brief Get the DDS Identification Topic used by this runtime
         */
        virtual DDS::Topic_var&
        getIdentificationTopic();

        /**
         * @brief Get the DDS Definition Topic used by this runtime
         */
        virtual DDS::Topic_var&
        getDefinitionTopic();

        /**
         * @brief Get the Client Identification Topic used by this runtime
         */
        virtual DDS::Topic_var&
        getClientIdentificationTopic();

        /**
         * \internal
         * @brief Create a new DDS Publisher for unique use of an interface
         * \endinternal
         */
        virtual DDS::Publisher_var
        createPublisher(std::string partition);

        /**
         * \internal
         * @brief Create a new DDS Subscriber for unique use of an interface
         * \endinternal
         */
        virtual DDS::Subscriber_var
        createSubscriber(std::string partition);

        /**
         * \internal
         * @brief Register the factory of proxies for an interface
         * \endinternal
         */
        static void
        registerFactory(std::string& interfaceClass, TInterfaceFactory factory);

        /**
         * \internal
         * @brief Return the factory of proxies for an interface
         * \endinternal
         */
        static TInterfaceFactory
        getFactory(std::string& interfaceClass);

        /**
         *
         * @brief Returns the configuration of the runtime as set from the command line options
         *
         */
        RmiConfiguration *
        getConfiguration();

        /**
         * \internal
         * To get the max time duration (in seconds) a client application may wait to find services
         * @return the corresponding DDS duration
         * \endinternal
         */
        inline DDS::Duration_t
        getServiceDiscoveryTimeout()
        {
          DDS::Duration_t timeout;
          int seconds = getConfiguration()->getServiceDiscoveryTimeout();
          if (seconds == -1)
            timeout = DDS::DURATION_INFINITE;
          else
            {
              timeout.sec = seconds;
              timeout.nanosec = 0;
            }
          return timeout;
        }

        virtual DDS_ServiceInterface_ref
        getDDS_ServiceInterface() const;

        virtual void
        run(const std::string serviceName);

        virtual void
        shutdown(const std::string serviceName);

        virtual bool
        is_running(const std::string serviceName);

        virtual void
        setServerThreadingPolicy(ServerThreadingPolicy & value);

        virtual ServerThreadingPolicy
        getServerThreadingPolicy();

        virtual void
        setServerSchedulingPolicy(SchedulingPolicy & value);

        virtual SchedulingPolicy
        getServerSchedulingPolicy();

        virtual void
        activate_service(CInterfaceManager_ref mger);

        virtual void
        deactivate_service(CInterfaceManager_ref mger);

        inline tps_WaitingRequestsThread *
        getTPSWaitingThread()
        {
          return m_TPSWaiter_thread;
        }

      private:
        // methods added because of no reentrant mutex available
        virtual void
        shutdown_nosync(const std::string serviceName);
        virtual bool
        is_running_nosync(const std::string serviceName);

        typedef std::map<std::string, TInterfaceFactory> TInterfaceFactoryMap;
        static TInterfaceFactoryMap m_InterfaceFactories;

        typedef std::map<std::string, CInterfaceManager_ref> TInterfaceMap;
        TInterfaceMap m_InterfaceMap; // servers implementations map
        CInterfaceRegistryImpl_ref m_InterfaceRegistry;
        unsigned int m_iTimeout; // reply reception timeout in millisecondes
        bool m_bStopped; // runtime availability
        bool m_bRunning; //services activation
        const DDS::Long m_sDomainURI;
        DDS::DomainParticipant_var m_Participant;
        // DDS entities for infrastructure activities (not for the Interfaces topics)
        DDS::Publisher_var m_Publisher;
        DDS::Subscriber_var m_Subscriber;
        DDS::Topic_var m_IdentificationTopic;
        DDS::Topic_var m_DefinitionTopic;
        DDS::Topic_var m_ClientIdentificationTopic;
        ::DDS_RMI::IdentificationDataWriter_var m_IdentificationWriter;
        ::DDS_RMI::DefinitionDataWriter_var m_DefinitionWriter;
        DDS::DataWriterListener_var m_IdentificationWriterListener;
        RmiConfiguration * m_Config;
        Mutex m_Mutex;
        DDS::GuardCondition_var m_shutdownCond;
        DDS::WaitSet_var m_RequestsWaitset;
        PriorityThreadPool_ref m_Thread_pool;
        DDS_ServiceInterface_ref DDSServiceInterfaceImpl;
        std::map<DDS::Condition_ptr, CInterfaceManagerImpl_ref> m_ReqToIntfMap;
        tps_WaitingRequestsThread * m_TPSWaiter_thread;
        Condition m_runningCond;

        class IdentificationDataWriterListener : public virtual DDS::DataWriterListener
        {
        public:
          IdentificationDataWriterListener(TInterfaceMap & map) :
            m_InterfaceMap(map), m_currentDRCount(0) {};

          void
          on_offered_deadline_missed (DDS::DataWriter_ptr writer, const DDS::OfferedDeadlineMissedStatus& status)
          {};

          void
          on_offered_incompatible_qos (DDS::DataWriter_ptr writer, const DDS::OfferedIncompatibleQosStatus& status)
          {};

          void
          on_liveliness_lost (DDS::DataWriter_ptr writer, const DDS::LivelinessLostStatus& status)
          {};

          virtual void
          on_publication_matched (DDS::DataWriter_ptr writer, const DDS::PublicationMatchedStatus& status);

        private:
          TInterfaceMap & m_InterfaceMap;
          DDS::Long m_currentDRCount;
        };

      };



    }
  }
}
#endif

