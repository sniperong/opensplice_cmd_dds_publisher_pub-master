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
 * @brief Definition of all the base classes of RMI as well as the templates
 * and the data types
 */

#ifndef _DDS_SERVICE_SDK_H_
#define _DDS_SERVICE_SDK_H_

// For Windows build
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#include "WindowsBuild.h"
// For error C2065 || C2143
//TODO remove this everywhere else
// now defined from posix sched.h in ospl==> include\dcps\C++\SACPP\eOrbC\os\win32
#define SCHED_OTHER 0
#else
#define DDS_SERVICE_API
#endif

#include <map>
#include <string>
#include <vector>
#include "sdk_shared_ptr.h"
#include "sdk_sync_print.h"
#include "ccpp_dds_rmi.h"
#include "sdk_thread.h"

#ifdef _WRS_KERNEL
#include <sched.h>
#endif

namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {
      class DDS_SERVICE_API CRuntime;
      class DDS_SERVICE_API CInterfaceManager;
      class DDS_SERVICE_API CSchedulingTraits;
      class DDS_SERVICE_API CInterfaceRegistry;
      class DDS_SERVICE_API CInterface;
      class DDS_SERVICE_API CInterfaceProxy;
      class DDS_SERVICE_API TIMEOUT;
      class DDS_SERVICE_API CAsyncReplyHandler;
      class DDS_SERVICE_API SystemException;
      class DDS_SERVICE_API INTERNAL_ERROR;
      class DDS_SERVICE_API SERVICE_NOT_FOUND;
      class DDS_SERVICE_API BAD_PARAM;
      class DDS_SERVICE_API DDS_ServiceInterface;
      class DDS_SERVICE_API ServiceInvocation;
      class DDS_SERVICE_API CRequestProcessingTask;

///@cond
      /**
       * \internal
       * @brief Qos structure for the CWriter template
       * \endinternal
       */
      struct CWriterQoSTemplate
      {
        DDS::ReliabilityQosPolicy reliability;
        DDS::DurabilityQosPolicy durability;
        DDS::TransportPriorityQosPolicy transportPriority;
        DDS::DeadlineQosPolicy deadline;
        DDS::LatencyBudgetQosPolicy latency;
        DDS::OwnershipQosPolicy ownership;
        DDS::OwnershipStrengthQosPolicy ownershipStrength;
        DDS::LifespanQosPolicy lifespan;
        DDS::DestinationOrderQosPolicy destinationOrder;
        DDS::PartitionQosPolicy partition;
      };

      /**
       * \internal
       * @brief Qos structure for the CReader template
       * \endinternal
       */
      struct CReaderQoSTemplate
      {
        DDS::ReliabilityQosPolicy reliability;
        DDS::DurabilityQosPolicy durability;
        DDS::DestinationOrderQosPolicy destinationOrder;
        DDS::PartitionQosPolicy partition;
      };

      // Other QoS template have similar structure. Notice that
      // constant with specific QoS values identifying common use cases
      // will be predefined by the SDK.
      const DDS::ReliabilityQosPolicy DEFAULT_WRITER_RELIABILITY_QOS =
        { DDS::RELIABLE_RELIABILITY_QOS,
          { 0, 100000000 }
#ifndef LITE
        , false
#endif
        };
      const DDS::ReliabilityQosPolicy DEFAULT_READER_RELIABILITY_QOS =
        { DDS::BEST_EFFORT_RELIABILITY_QOS,
          { 0, 100000000 }
#ifndef LITE
        , false
#endif
	};
      const DDS::DurabilityQosPolicy DEFAULT_DURABILITY_QOS =
        { DDS::VOLATILE_DURABILITY_QOS };
      const DDS::TransportPriorityQosPolicy DEFAULT_TRANSPORT_PRIORITY_QOS =
        { 0 };
      const DDS::DeadlineQosPolicy DEFAULT_DEADLINE_QOS =
        {
          { DDS::DURATION_INFINITE_SEC, DDS::DURATION_INFINITE_NSEC } };
      const DDS::LatencyBudgetQosPolicy DEFAULT_LATENCY_BUDGET_QOS =
        {
          { 0, 0 } };
      const DDS::OwnershipQosPolicy DEFAULT_OWNERSHIP_QOS =
        { DDS::SHARED_OWNERSHIP_QOS };
      const DDS::OwnershipStrengthQosPolicy DEFAULT_OWNERSHIP_STRENGTH_QOS =
        { 0 };
      const DDS::LifespanQosPolicy DEFAULT_LIFESPAN_QOS =
        {
          { DDS::DURATION_INFINITE_SEC, DDS::DURATION_INFINITE_NSEC } };
      const DDS::DestinationOrderQosPolicy DEFAULT_DESTINATION_ORDER_QOS =
        { DDS::BY_RECEPTION_TIMESTAMP_DESTINATIONORDER_QOS };
      const DDS::PartitionQosPolicy DEFAULT_PARTITION_QOS =
          DDS::PartitionQosPolicy();

      const CWriterQoSTemplate DEFAULT_WRITER_QOS_TEMPLATE =
        { DEFAULT_WRITER_RELIABILITY_QOS, DEFAULT_DURABILITY_QOS,
            DEFAULT_TRANSPORT_PRIORITY_QOS, DEFAULT_DEADLINE_QOS,
            DEFAULT_LATENCY_BUDGET_QOS, DEFAULT_OWNERSHIP_QOS,
            DEFAULT_OWNERSHIP_STRENGTH_QOS, DEFAULT_LIFESPAN_QOS,
            DEFAULT_DESTINATION_ORDER_QOS, DEFAULT_PARTITION_QOS };

      const CReaderQoSTemplate DEFAULT_READER_QOS_TEMPLATE =
        { DEFAULT_READER_RELIABILITY_QOS, DEFAULT_DURABILITY_QOS,
            DEFAULT_DESTINATION_ORDER_QOS, DEFAULT_PARTITION_QOS };

      const long DDS_SERVICE_SDK_INFINITE = -1;
      const int DEFAULT_STATUS_MASK = 0;


      /**
       * \internal
       * @brief Structure for a refined interface resolution
       * \endinternal
       */
      struct TInterfaceProperty
      {
        std::string server_class;
        std::string server_impl;
        std::map<std::string, std::string> properties;
      };

      /**
       * \internal
       * @brief real time rules for the remote interface implementation
       * \endinternal
       */
      struct TSchedulingTraits
      {
        unsigned short thread_num;
        int sched_policy; // e.g. SCHED_OTHER, SCHED_RR, SCHED_FIFO
        int priority;
      };

      const TSchedulingTraits DEFAULT_SCHEDULING_TRAITS =
        { 0, SCHED_OTHER, 0 };

      // Shared pointers typedefs
      typedef shared_ptr<CInterfaceManager> CInterfaceManager_ref;
      typedef shared_ptr<CInterface> CInterface_ref;
      typedef shared_ptr<CInterfaceProxy> CInterfaceProxy_ref;
      typedef shared_ptr<CRuntime> CRuntime_ref;
      typedef shared_ptr<CInterfaceRegistry> CInterfaceRegistry_ref;
      typedef ::DDS::DataWriter_var CDDSWriter_ref;
      typedef ::DDS::DataReader_var CDDSReader_ref;
      typedef ::DDS::DataReaderListener_var CReaderListener_ref;
      typedef shared_ptr<DDS_ServiceInterface> DDS_ServiceInterface_ref;
      class DDS_SERVICE_API CRuntimeImpl;
      typedef shared_ptr<CRuntimeImpl> CRuntimeImpl_ref;
      class CInterfaceImpl;
      typedef shared_ptr<CInterfaceImpl> CInterfaceImpl_ref;
      class DDS_SERVICE_API CInterfaceManagerImpl;
      typedef shared_ptr<CInterfaceManagerImpl> CInterfaceManagerImpl_ref;
      class DDS_SERVICE_API tps_WaitingRequestsThread ;

      /**
       * \internal
       * @brief operation structure including :
       *        topics names and the associated TypeSupport classes
       *        associated, as well as the description of the topics types.
       * \endinternal
       */
      struct OperationInfo
      {
        std::string m_RequestTopicName;
        std::string m_ReplyTopicName;
        DDS::TypeSupport_var m_RequestTypeSupport;
        DDS::TypeSupport_var m_ReplyTypeSupport;
        std::string m_RequestTopicCode;
        std::string m_ReplyTopicCode;
      };
///@endcond

      enum ThreadingPolicyKind {
        /**
         * Single Thread
         */
        ST = 0,
        /**
         * Multi Thread
         */
        MT,
        /**
         * Thread Per Service
         */
        TPS
      };

      static const char * ThreadingPolicyKindLabels[] = {"ST", "MT", "TPS"};
      static const char * SchedulingClassKindLabels[] = {"default", "realtime", "timeshare"};

      struct ServerThreadingPolicy {
        ThreadingPolicyKind kind;
        int threadPoolSize;

        bool operator==(const ServerThreadingPolicy& stp) const
        {
          return (kind  == stp.kind && threadPoolSize == stp.threadPoolSize);
        }
      };

      enum SchedulingClassKind {
        SCHEDULE_DEFAULT = OS_SCHED_DEFAULT ,
        SCHEDULE_REALTIME = OS_SCHED_REALTIME,
        SCHEDULE_TIMESHARING = OS_SCHED_TIMESHARE
      };

      enum SchedulingPriorityKind{
        PRIORITY_ABSOLUTE, PRIORITY_RELATIVE
      };

      struct SchedulingPolicy {
        SchedulingClassKind schedulingClass;
        int schedulingPriority;
        SchedulingPriorityKind priorityKind;
        bool operator==(const SchedulingPolicy& sp) const
        {
          return (schedulingClass  == sp.schedulingClass && schedulingPriority == sp.schedulingPriority
              && priorityKind == sp.priorityKind);
        }

        bool is_default()
        {
          if(schedulingClass == SCHEDULE_DEFAULT && schedulingPriority == 0 &&
              priorityKind == PRIORITY_RELATIVE)
            return true;
          return false;
        }
      };

      /**
       * @brief It is the base exception of all the system exceptions
       * indicating middleware-related errors.
       */

      class SystemException : public virtual std::exception
      {

      public:
        DDS::ReturnCode_t dds_code;
        std::string m_Msg;

        SystemException();

        SystemException(const char* msg, DDS::ReturnCode_t code =
            DDS::RETCODE_OK);

        virtual const char*
        what() const throw ();

        virtual
        ~SystemException() throw ();
      };

      /**
       * @brief Indicates timeout expiration.
       */
      class TIMEOUT : public virtual SystemException
      {
      public:
        TIMEOUT();
      };

      /**
       * @brief Indicates invalid parameter error.
       */
      class BAD_PARAM : public virtual SystemException
      {

      public:
        BAD_PARAM(const char* msg);

        virtual
        ~BAD_PARAM() throw ();
      };

      /**
       * @brief Indicates a middleware-internal error.
       */
      class INTERNAL_ERROR : public virtual SystemException
      {

      public:

        INTERNAL_ERROR(const char* msg, DDS::ReturnCode_t code =
            DDS::RETCODE_OK);

        virtual
        ~INTERNAL_ERROR() throw ();
      };

      /**
       * @brief Reports failure to find a given service.
       */
      class SERVICE_NOT_FOUND : public virtual SystemException
      {

      public:

        SERVICE_NOT_FOUND();

        virtual
        ~SERVICE_NOT_FOUND() throw ();
      };

      /**
       * @brief Reports a bad invocation order of the API.
       */
      class BAD_INV_ORDER : public virtual SystemException
      {

      public:

        BAD_INV_ORDER(const char* msg);

        virtual
        ~BAD_INV_ORDER() throw ();
      };

///@cond
      /**
       * \internal
       * @brief This class allows to manage all the aspects related to the execution of
       * a Interface instance (on the server side), such as threading, scheduling class,
       * priority, as well as status, e.g., running, paused, etc.
       * \endinternal
       */
      class CInterfaceManager : public virtual RefCounted
      {
      public:
        virtual
        ~CInterfaceManager()
        {
        }

        /**
         * @brief Start by default single threaded interfaces running in non-realtime scheduling class,
         * at nominal priority, with the given timeout.
         * @deprecated
         */
        virtual void
        manage(const TSchedulingTraits& sched = DEFAULT_SCHEDULING_TRAITS,
            bool paused = true) = 0;

        /**
         *  @brief To suspend the processing of the managed interface,
         *  causes also the call of the suspend callback of the interface
         *  @deprecated
         */
        virtual void
        suspend() = 0;

        /**
         *  @brief To resume the processing of the managed interface,
         *  causes also the call of the resume callback of the interface
         *  @deprecated
         */
        virtual void
        resume() = 0;

        /**
         *  @brief To get the managed interface
         */
        virtual CInterfaceImpl_ref&
        getInterface() = 0;

        /**
         * @brief starts waiting for incoming requests
         */
        virtual void
        run() = 0;

        /**
         * @brief stops waiting for incoming requests
         */
        virtual void
        shutdown(bool wait_for_completion = true) = 0;

        virtual bool
        is_running() = 0;
      };
///@endcond

      /**
       * @brief A class providing APIs to manage the runtime that allows clients to communicate with
       * servers.This runtime is an abstraction of the underlying DDS environment.
       */
      class CRuntime : public virtual RefCounted
      {
      public:
        virtual
        ~CRuntime()
        {
        }

        // ------------------------------------------------------------
        // Common (Server or Client) Operations
        // ------------------------------------------------------------

        /**
         * @brief Gets the Runtime for the default domain (id = 0).
         */
        static CRuntime_ref
        getDefaultRuntime();

        /**
         * @brief Gets the Runtime instance for the given domain.
         */

        static CRuntime_ref
        getRuntime(const DDS::Long domain);

        /**
         * @brief Sets the default timeout for all the created proxies to
         * waiting for replies.
         * @param millis timeout in milliseconds
         */
        virtual void
        setTimeout(unsigned int millis) = 0;

        /**
         * @brief Get the maximum number in milliseconds to wait before
         * considering that the reply will not come
         */
        virtual unsigned int
        getTimeout() = 0;

        /**
         * @brief Starts the DDS infrastructure entities.
         * Supported arguments :
         * --RMIClientThreadingModel=[ST|MT]
         * --RMIServiceDiscoveryTimeout=seconds
         *
         * @param argc configuration arguments count
         * @param argv  configuration arguments
         * @return true if successful
         */
        virtual bool
        start(int argc, const char* argv[]) = 0;

        /**
         * @brief Stops the runtime and releases resources.
         */
        virtual bool
        stop() = 0;

        /**
         * @brief Indicates if this runtime can be used (not stopped)
         */
        virtual bool
        isUsable() = 0;

        /**
         * @brief Gets the DDS Domain Participant used by this runtime
         */
        virtual DDS::DomainParticipant_var&
        get_dds_domain_participant() = 0;

        /**
         * Retrieves the DDS_ServiceInterface that allows to
         * @return DDS_ServiceInterface
         */
        virtual DDS_ServiceInterface_ref
        getDDS_ServiceInterface() const = 0;

        // ------------------------------------------------------------
        // Server Specific Operations
        // ------------------------------------------------------------

        /**
         * \internal
         * @brief Registers a interface instance.
         *
         * Notice that the interface instance will need to be explicitly activated
         * through its CInterfaceManager. In addition, the interface will automatically
         * be inserted in the local registry which will propagate the update to
         * remote registries.
         * \endinternal
         */
        virtual CInterfaceManager_ref
            register_interface(const CInterface_ref& svc,
                const std::string& name) = 0;

        /**
         * \internal
         * @brief Registers a interface instance.
         *
         * Notice that the interface instance will need to be explicitly activated
         * through its CInterfaceManager. In addition, the interface will automatically
         * be inserted in the local registry which will propagate the update to
         * remote registries.
         *
         * The Interface property can be used to express some specific interface features
         * that can be helpful in resolving the appropriate interface during discovery.
         * \endinternal
         */
        /*virtual CInterfaceManager_ref
        register_interface(const CInterface_ref& svc,
            const TInterfaceProperty& property) = 0;*/

        /**
         * \internal
         * @brief Removes an interface instance having the given name an id
         * \endinternal
         */
        virtual void
        unregister_interface(const std::string& name, int instance) = 0;

        /**
         * \internal
         * @brief Looks up a interface manager for a specific interface instance.
         * \endinternal
         */
        virtual CInterfaceManager_ref
        lookup_interface_manager(const std::string& name) = 0;

        /**
         * \internal
         * @brief activates all the registered services and makes them ready to process incoming requests.
         * If succeeded, it blocks the current thread until some other thread calls shutdown.
         * \endinternal
         */
        virtual void
        run() = 0;

        /**
         * @brief Activates the given service. The runtime should be run before. Suitable for services
         * that were registered after the runtime has been run.
         * @param serviceName the service that should be activated
         */
        virtual void
        run(const std::string serviceName) = 0;

        /**
         * \internal
         * @brief de-activates all the registered services.
         * \endinternal
         */
        virtual void
        shutdown(bool wait_for_completion = true) = 0;


        virtual void
        shutdown(const std::string serviceName) = 0;

        /**
        * @brief Indicates whether this CRuntime has been run or not.
        */
        virtual bool
        is_running() = 0;

        /**
         * @brief Indicates whether the provided service is running.
         *
         */
        virtual bool
        is_running(const std::string serviceName) = 0;

        /**
         * Sets the server Threading Model. The threading policy may be modified as far as the runtime is not running.
         * @param value indicates a threading policy
         * @throws BAD_INV_ORDER if the runtime is running
         * @throws BAD_PARAM if the given policy is invalid
         * @see ServerThreadPolicy
         */
        virtual void
        setServerThreadingPolicy(ServerThreadingPolicy & value) = 0;

        /**
         * Gets  a copy of the current server threading policy. Modifying the returned object has no effect.
         * @return the server threading policy
         * @see ServerThreadPolicy
         */
        virtual ServerThreadingPolicy
        getServerThreadingPolicy() = 0;

        /**
         * Sets the current server scheduling policy.
         * @param value
         * @see SchedulingPolicy
         */
        virtual void
        setServerSchedulingPolicy(SchedulingPolicy & value) = 0;

        /**
         * Gets a copy of the current server scheduling policy. Modifying the returned object has no effect.
         * @return the server scheduling policy
         * @see SchedulingPolicy
         */
        virtual SchedulingPolicy
        getServerSchedulingPolicy() = 0;


        // ------------------------------------------------------------
        // Client Specific Operations
        // ------------------------------------------------------------

        /**
         * \internal
         * @brief Allow the client to discover the available interfaces
         * \endinternal
         */
        virtual CInterfaceRegistry_ref
        getRegistry() = 0;

        /**
         * @brief Unregisters the Runtime instance for the given domain.
         */
        static void
        removeRuntime(const DDS::Long domain);

      };

      /**
       * @brief Ancestor class of all server-side interfaces
       *
       * A first level implementation of this class is provided by Opensplice RMI
       * A second level implementation of this class is generated by rmipp
       * A third level implementation of this class is to be implemented by the developper
       * For each abstract method, the level where it is be provided is indicated
       */
      class CInterface : public virtual RefCounted
      {
      public:

        CInterface(){}

        virtual
        ~CInterface(){}

        /**
         * returns the service identification information.
         * class Identification {
         *      public java.lang.String server_class;
         *      public java.lang.String server_impl;
         *      public int server_instance;
         *      }
         */
        virtual ::DDS_RMI::Identification
        getIdent() = 0;

        /**
         * @brief This operation returns a Boolean to indicate if an interface is used to broadcast calls.
         */
        virtual bool
        isDiffusion() = 0;

///@cond
        /**
         * \internal
         * @brief To indicate the instance number of this interface
         * provided by the first level
         * \endinternal
         */
        virtual void
        setInstanceNumber(int num) = 0;

        /**
          * @brief sets the partitions to be used to send requests and replies.
          * @param partition string array of 2 elements. The first one indicates
          * the requests partition and the second one indicates the replies partition name.
          * @throws BAD_PARAM
          */
        virtual void
        setPartition(std::string partition[2]) = 0;

        /**
         * \internal
         * @brief Callback called by the interface manager to inform
         * the interface implementation that the interface is paused
         * It is not abstract as it has often an empty implementation
         * Putting this as default, reduce the burden of the developer
         * provided by the third level
         * \endinternal
         */
        virtual void
        suspend()
        {
        }

        /**
         * \internal
         * @brief Callback called by the interface manager to inform
         * the interface implementation that the interface is resumed
         * It is not abstract as it has often an empty implementation
         * Putting this as default, reduce the burden of the developer
         * provided by the third level
         * \endinternal
         */
        virtual void
        resume()
        {
        }

        /**
         * \internal
         * @brief To set the runtime to use
         * \endinternal
         */
        virtual void
        setRuntime(CRuntime_ref runtime);

///@endcond

        /**
         * @brief To get the runtime used
         */
        virtual CRuntime_ref
        getRuntime();

        /**
         * \internal
         * @brief Set the reception filter to apply to an operation
         *  It is effective in diffusion mode only, else it returns false
         * \endinternal
         */
        virtual bool
        setFilter(int operation_index, std::string expr, std::vector<
            std::string> params) = 0;

        /**
         * \internal
         * @brief Change the reception filter params of an operation
         *  It is effective in diffusion mode only, else it returns false
         *  \endinternal
         */
        virtual bool
            changeFilterParams(int operation_index,
                std::vector<std::string> params) = 0;

      private:
        CRuntime_ref m_Runtime;
      };

      /**
       * @brief Ancestor class of all client-side interface proxies
       */
      class CInterfaceProxy : public virtual RefCounted
      {
      public:
        virtual
        ~CInterfaceProxy()
        {
        }

      /**
       * returns the service identification information.
       * class Identification {
       *      public java.lang.String server_class;
       *      public java.lang.String server_impl;
       *      public int server_instance;
       *      }
       */
        virtual ::DDS_RMI::Identification
        getIdent() = 0;

        /**
         * @brief This operation returns a Boolean to indicate if an interface is used to broadcast calls.
         */
        virtual bool
        isDiffusion() = 0;
///@cond
        /**
         * \internal
         * @brief Identify the client this proxy
         * No proxy operation can be called before this setting
         * The client code must set this just after retrieving this proxy
         * \endinternal
         */
        virtual void
        setIdentification(std::string name, int instance = 1) = 0;

        /**
         * @brief sets the partitions to be used to send requests and replies.
         * @param partition string array of 2 elements. The first one indicates
         * the requests partition and the second one indicates the replies partition name.
         * @throws BAD_PARAM
         */
        virtual void
        setPartition(std::string partition[2]) = 0;

        /**
         * \internal
         * @brief To set the runtime to use
         * \endinternal
         */
        void
        setRuntime(CRuntime_ref runtime)
        {
          m_Runtime = runtime;
        }

///@endcond
        /**
         * @brief To get the runtime used
         */
        CRuntime_ref
        getRuntime()
        {
          return m_Runtime;
        }

        /**
         * @brief Gets the maximum number of milliseconds to wait before
         * considering that the reply will not come
         */
        virtual unsigned int
        getTimeout() = 0;

        /**
         * @brief Sets the maximum number of milliseconds to wait before
         * considering that the reply will not come
         */
        virtual void
        setTimeout(unsigned int millis) = 0;
      private:
        CRuntime_ref m_Runtime;
      };

///@cond
      /**
       * \internal
       * @brief Ancestor class of all client-side handlers of async replies.
       * \endinternal
       */
      class CAsyncReplyHandler : public virtual RefCounted
      {
      public:
        virtual
        ~CAsyncReplyHandler()
        {
        }
      };

      /**
       * \internal
       * @brief Class to find interface proxies
       * Need not to be derived by the developer
       * \endinternal
       */
      class CInterfaceRegistry : public virtual RefCounted
      {
      public:
        virtual
        ~CInterfaceRegistry()
        {
        }

        /**
         * @brief Resolves an interface instance having the given name and returns a proxy to it.
         */
        virtual CInterfaceProxy_ref
        resolve(const std::string& name) = 0;

        virtual CInterfaceProxy_ref
        resolve(const std::string& server_name, const std::string& proxy_name,
            int server_instance, int proxy_instance) = 0;

        virtual CInterfaceProxy_ref
        resolve(const std::string& server_name, const std::string& proxy_name,
            int proxy_instance)= 0;

        /**
         *  @brief Iterator to go through the discovered interfaces
         */
        template<typename OutIterator>
          int
          list(OutIterator begin, int max_interfaces);

        /**
         * @brief Iterator that resolves a set of interface instances
         * matching the search criteria and creates proxy for them.
         */
        template<typename OutIterator>
          int
          resolve(TInterfaceProperty& property, OutIterator begin,
              int max_interfaces);

      };


      /**
       * @brief For the CWriter and CReader templates
       *
       * TopicInfo must be modeled like this
       * struct TopicInfo
       * {
       *   typedef TopicType Type ;
       *   typedef TopicTypeTypeSupport TypeTS ;
       *   typedef TopicTypeSeq TypeSeq ;
       *
       *   typedef TopicTypeDataWriter TypedWriter;
       *   typedef TopicTypeDataWriter_var TypedWriter_ref;
       *   typedef TopicTypeDataReader TypedReader;
       *   typedef TopicTypeDataReader_var TypedReader_ref;
       *
       *   std::string TopicName ;
       *   DDS::TopicQos TopicQos ;
       *  };
       * This macro helps this modeling:
       */
#define TOPIC_INFO(foo) { \
     typedef foo Type ; \
     typedef foo##TypeSupport TypeTS ; \
     typedef foo##Seq TypeSeq ; \
     typedef foo##DataWriter TypedWriter; \
     typedef foo##DataWriter_var TypedWriter_ref; \
     typedef foo##DataReader TypedReader; \
     typedef foo##DataReader_var TypedReader_ref; \
     std::string TopicName ; \
     DDS::TopicQos TopicQos ; }

      /**
       * \internal
       * @brief Template to simplify the publication of topic instances
       * \endinternal
       */
      template<class TopicInfo>
        class CWriter
        {
        public:
          /**
           * @brief  Creates a writer for a specific topic (see template) and with a set of QoS
           *
           * By default, the writer is created on a publisher associated
           * with the default partition.
           * Different from the DDS API, the Partition QoS can be passed at the time
           * of creation for the writer, and the SDK will take care of creating the
           * proper Publisher if it does not exist yet.
           */
          CWriter(CRuntime_ref runtime, const TopicInfo& info,
              const CWriterQoSTemplate qos = DEFAULT_WRITER_QOS_TEMPLATE);

          /**
           * @brief Tell the readers that this instance will be published by this writer
           * This is not a mandatory operation as "write" automatically do this
           */
          void
          register_instance(typename TopicInfo::Type& instance);

          /**
           * @brief Tell the readers that this instance will no longer be published by this writer
           */
          void
          unregister_instance(typename TopicInfo::Type& instance);

          /**
           * @brief Publish a sample
           */
          void
          write(typename TopicInfo::Type& instance);

          /**
           * @brief Destroy an instance
           */
          void
          dispose(typename TopicInfo::Type& instance);

          /**
           * @brief Get the underlying DDS DataWriter
           *
           * This will allows the access to the different DDS entities associated with it
           * to perform DDS specific operations
           * Must be used with extreme care to avoid breaking the correct behavior
           */
          CDDSWriter_ref
          get_dds_writer();

        private:
          CDDSWriter_ref m_ddsWriter;
          typename TopicInfo::TypedWriter_ref m_typedWriter;
        };

      /**
       * \internal
       * @brief Template to simplify the subscription to topic instances
       * \endinternal
       */
      template<class TopicInfo>
        class CReader
        {
        public:
          /**
           * @brief Creates a reader for a specific topic (see template) and with a set of QoS.
           *
           * By default, the reader is created on a subscriber associated with
           * the default partition.
           * Different from the DDS API, the Partition QoS can be passed at the time
           * of creation for the reader, and the SDK will take care of creating
           * the proper Subscriber if it does not exist yet.
           */
          CReader(CRuntime_ref runtime, const TopicInfo& info,
              const CReaderQoSTemplate qos = DEFAULT_READER_QOS_TEMPLATE,
              long millis = 100);

          ~CReader () { 
              m_waiter.detach_condition(m_condition);
              m_typedReader->delete_readcondition(m_condition.in());
          }
 

          /**
           * @brief Reads by default samples that have not been read yet. It returns the number of samples read,
           * or -1 if the number of available samples was exceeding the max samples.
           */
          template<typename OutputIterator>
            int
            read(OutputIterator begin, int maxsamples, long millis,
                bool use_filter = false);

          /**
           * @brief Takes by default samples that have not been read yet. It returns the number of samples taken,
           * or -1 if the number of available samples was exceeding the max samples.
           */
          template<typename OutputIterator>
            int
            take(OutputIterator begin, int maxsamples, long millis,
                bool use_filter = false);

          /**
           * @brief Reads all available samples. It returns the number of samples read,
           * or -1 if the number of available samples was exceeding the max samples.
           */
          template<typename SampleOutputIterator, typename InfoOutputIterator>
            int
            read(SampleOutputIterator sbegin, InfoOutputIterator ibegin,
                int maxsamples, long millis, bool use_filter = false);

          /**
           * @brief Takes all available samples. It returns the number of samples read,
           * or -1 if the number of available samples was exceeding the max samples.
           */
          template<typename SampleOutputIterator, typename InfoOutputIterator>
            int
            take(SampleOutputIterator sbegin, InfoOutputIterator ibegin,
                int maxsamples, long millis, bool use_filter = false);

          /**
           * @brief Attaches a listener to this reader and returns the previously attached listener.
           */
          CReaderListener_ref
          set_listener(CReaderListener_ref listener, int status_mask =
              DEFAULT_STATUS_MASK);

          /**
           * @brief Get the underlying DDS DataReader
           *
           * This will allows the access to the different DDS entities associated with it
           * to perform DDS specific operations
           * Must be used with extreme care to avoid breaking the correct behavior
           */
          CDDSReader_ref
          get_dds_reader();

          /**
           * @brief Set the reception filter to be applied
           */
          virtual bool
          setFilter(std::string expr, std::vector<std::string> params);

          /**
           * @brief Change the reception filter params
           */
          virtual bool
          changeFilterParams(std::vector<std::string> params);

        private:
          CDDSReader_ref m_ddsReader;
          typename TopicInfo::TypedReader_ref m_typedReader;
          CReaderListener_ref m_listener;
          std::string m_filterExpr;
          DDS::StringSeq m_filterParams;
          DDS::QueryCondition_var m_filter;
          DDS::ReadCondition_var m_condition;
          DDS::WaitSet m_waiter ;
          DDS::ConditionSeq  m_active;
          DDS::Duration_t m_timeout ;

        };

///@endcond

      /**
       * This interface provides the APIs for performing remote services invocations over DDS.
       * Unlike the DDS_Service utility class that operates on the default DDS domain, this
       * interface implementations operate on user-defined DDS domains.
       * It allows the client applications to get a server proxy to invoke the service.
       * It allows the server applications to register the services and run them in
       * order to be invoked.
      */
     class DDS_ServiceInterface : public virtual RefCounted {

     public:

     virtual ~DDS_ServiceInterface() {}
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
     bool
     register_interface(shared_ptr<T2> l_SrvProvider,
           const std::string &p_sServerName, int p_iServerInstanceID)
     {
       bool l_bResult = false;

       if (runtime->isUsable())
         {
           // interface registration
           T1::_register_service_info();

           // service implementation class
           if (l_SrvProvider.get())
             {
               l_SrvProvider->setRuntime(runtime);
               l_SrvProvider->setInstanceNumber(p_iServerInstanceID);

               // implementation class registration
               CInterfaceManager_ref l_SrvProviderManager =
                   runtime->register_interface(l_SrvProvider,
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
      * @brief unregisters an already registered interface
      * @param [in] p_sServerName        server name.
      * @param [in] p_iServerInstanceID  server instance id.
      * @return true if successful.
      */
     virtual bool
     unregister_interface(const std::string &p_sServerName,
                 int p_iServerInstanceID) = 0;

     /**
      * activates the named service so that it is able to process incoming requests.
      * @param p_sServerName service name
      * @return true if successful
      */
     virtual bool
     run(const std::string &p_sServerName) = 0;

     /**
      * de-activates the named service.
      * @param p_sServerName service name
      * @return true if successful
      */
     virtual bool
     shutdown(const std::string &p_sServerName) = 0;

     /**
     * returns the service running state.
     * @param p_sServerName service name
     * @return true if the service is running, false else.
     */
     virtual bool
     is_running(const std::string &p_sServerName) = 0;


     /**
     * @brief creates a service proxy for a client application. This proxy allows to
     * invoke the named service operations via DDS. The proxy will represent
     * any service instance.
     * @param [in]  p_sServerName       server name.
     * @param [in]  p_iProxyInstanceID  proxy instance id.
     * @param [out] p_ServerProxy       the proxy to create.
     *
     * @return "true" when succeeds.
     * @throws SERVICE_NOT_FOUND if the service name is not found
     */
     template<class T>
     bool
     getServerProxy(const std::string & p_sServerName,
     int p_iProxyInstanceID, shared_ptr<T> &p_ServerProxy)
     {
       return getServerProxy(p_sServerName, -1, p_iProxyInstanceID,
                  p_ServerProxy);
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
     * @throws SERVICE_NOT_FOUND if the service name is not found
     */
     template<class T>
     bool
     getServerProxy(const std::string & p_sServerName,
     int p_iServerInstanceID, int p_iProxyInstanceID,
     shared_ptr<T> &p_ServerProxy)
     {
       bool l_bResult = false;
       if (runtime->isUsable())
        {
          // Interface registration
          T::_register_service_info();

          // Proxy creation
          CInterfaceRegistry_ref l_Registry =
              runtime->getRegistry();
          CInterfaceProxy_ref l_Proxy = l_Registry->resolve(
              p_sServerName, p_sServerName + "_Proxy",
              p_iServerInstanceID, p_iProxyInstanceID);
          if (l_Proxy.get() != NULL)
            {
              //l_Proxy->setIdentification( p_sServerName + "_Proxy", p_iProxyInstanceID );
              p_ServerProxy = dynamic_cast<T *> (l_Proxy.get());
              if (p_ServerProxy.get())
                {
                  l_bResult = true;
                }
            }
        }
       return l_bResult;
     }

     protected:
     CRuntime_ref runtime;

     };

     class ServiceInvocation
     {
     public:
       ServiceInvocation(const char * name, DDS::Time_t time):
         receptionTime(time), m_name(name), m_index(m_nextIndex++) {};

       virtual ~ServiceInvocation() {};

       virtual void invoke() = 0 ;

       inline const char *
       getName() const
       {
         return m_name;
       }

       inline unsigned long
       getIndex() const
       {
         return m_index;
       }

       virtual bool
       operator<(const ServiceInvocation& inv) const;

       DDS::Time_t receptionTime;

     private:
       const char * m_name;
       unsigned long m_index;
       static unsigned long m_nextIndex;
     };

     class CRequestProcessingTask : virtual public ComparableRunnable
       {
       public:
         CRequestProcessingTask(CInterfaceManagerImpl_ref mger, ServiceInvocation* req, int priority);

         ~CRequestProcessingTask();

           virtual void
           run();

           virtual bool
           operator<(const ComparableRunnable& c) const;

           int
           get_priority() const;

           ServiceInvocation *
           get_request();

           CInterfaceManagerImpl_ref
           get_manager();

       private:
           ServiceInvocation * m_request;
           int m_priority;
           CInterfaceManager_ref m_manager;
       };
     typedef shared_ptr<CRequestProcessingTask> CRequestProcessingTask_ref;

    }
  }
}

#endif

