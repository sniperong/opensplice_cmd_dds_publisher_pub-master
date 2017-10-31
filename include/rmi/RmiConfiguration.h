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

#ifndef RMICONFIGURATION_H_
#define RMICONFIGURATION_H_


#include "dds_service_sdk.h"

namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {

      #define DEFAULT_SERVICE_DISCOVERY_TIMEOUT 30 //seconds

      enum RequestInstancesManagementStrategy
      {
        instance_per_client,
        instance_per_request // FT-enabled
      };

      /**
       * @brief Holder class for RMI runtime configuration
       */
      class RmiConfiguration
      {
      public:
        RmiConfiguration();
        virtual
        ~RmiConfiguration();

        void
        init(int argc, const char *argv[]);

        void
        reset();

        /**
         * To get the threading model of the client
         * @return 'ST' if single threaded, 'MT' if multithreaded.
         */
        inline ThreadingPolicyKind
        getRMIClientThreadingModel()
        {
          return RMIClientThreadingModel;
        }

        /**
         * To get the max time duration (in seconds) a client application may wait to find services
         * @return the timeout duration in seconds
         */
        inline int
        getServiceDiscoveryTimeout()
        {
          return ServiceDiscoveryTimeout;
        }

        /**
         * To get the threading model of the server
         * @return ServerThreadingPolicy
         * @see ServerThreadingPolicy
         */
        inline const ServerThreadingPolicy &
        getRMIServerThreadingModel() {
            return RMIServerThreadingModel;
        }

        inline const SchedulingPolicy &
        getServerSchedulingPolicy() {
            return serverSchedulingPolicy;
        }

        inline int
        getThreadsPriority() {
            return serverSchedulingPolicy.schedulingPriority;
        }

        void
        setServerSchedulingPolicy(SchedulingPolicy & p);

        void
        setRMIServerThreadingModel(ServerThreadingPolicy & value);

        inline bool
        isDurabilityEnabled(){
          return durability;
        }

        inline bool
        isLegacyTopicNamesEnabled(){
            return LegacyTopicNames;
        }

      private:
        static const int optionsLength = 6;
        static const char * optionsLabels[optionsLength];
        static const char * YES_OPTION;
        static const char * NO_OPTION;

        void
        validateClientThreadingModel(const char * optionValue);

        void
        validateServiceDiscoveryTimeout (const char * optionValue);

        void
        validateServerThreadingPolicy (const char * optionValue);

        void
        validateServerSchedulingPolicy (const char * optionValue);

        ThreadingPolicyKind
        string_to_threading_kind(const char * strVal);

        SchedulingClassKind
        string_to_scheduling_class(const char * strVal);

        void
        validateDurabilitySupport(const char * optionValue);

        void
        validateLegacyTopicNames(const char * optionValue);

        void
        (org::opensplice::DDS_RMI::RmiConfiguration::* optionsValidators[optionsLength])(
                const char *);

        ThreadingPolicyKind RMIClientThreadingModel;
        RequestInstancesManagementStrategy RequestInstancesStrategy; // Not supported yet
        int ServiceDiscoveryTimeout;
        ServerThreadingPolicy RMIServerThreadingModel;
        SchedulingPolicy serverSchedulingPolicy;
        bool durability;
        bool LegacyTopicNames;

      };

    }
  }
}

#endif /* RMICONFIGURATION_H_ */
