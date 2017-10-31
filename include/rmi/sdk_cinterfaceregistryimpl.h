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
 * @brief Implementation class of the remote interfaces repository
 *
 * @author Bernard MAUDRY
 *
 * Module   : RMI
 * Class   : CInterfaceRegistryImpl
 *
 *
 */

#ifndef _SDK_CINTERFACEREGISTRYIMPL_HPP_
#define _SDK_CINTERFACEREGISTRYIMPL_HPP_

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#include "WindowsBuild.h"
#else
#define DDS_SERVICE_API
#endif

#include <map>
#include <vector>

#include "dds_service_sdk.h"

namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {
      typedef std::map<std::string, CInterfaceProxy_ref> CInterfaceList;
      typedef std::vector<CInterfaceProxy_ref> CInterfaceProxies;

      class DDS_SERVICE_API CRuntimeImpl;

      /**
       * @brief Classe interne implementant les operations du registre des interfaces
       */
      class DDS_SERVICE_API CInterfaceRegistryImpl : public CInterfaceRegistry
      {
      public:
        /**
         * @brief Default constructor
         */
        CInterfaceRegistryImpl();

        /**
         * @brief Destructor
         */
        virtual
        ~CInterfaceRegistryImpl();

        /**
         * @brief Set the runtime this registry is for
         */
        void
        setRuntime(CRuntimeImpl* runtime);

        /**
         * @brief Resolves a interface instance and returns a proxy to it.
         */
        virtual CInterfaceProxy_ref
        resolve(const std::string& server_name, const std::string& proxy_name,
            int server_instance, int proxy_instance);

        /**
         * @brief Resolves a interface instance and returns a proxy to it. Any service instance can be used
         */
        virtual CInterfaceProxy_ref
        resolve(const std::string& server_name, const std::string& proxy_name,
            int proxy_instance);

        virtual CInterfaceProxy_ref
        resolve(const std::string& server_name);

        /**
         * @brief List the available interfaces.
         */
        virtual ::DDS_RMI::IdentificationSeq
        listMax(int max_interfaces);

        /**
         * @brief Check wether the interface matches the property
         */
        bool
        match(TInterfaceProperty& property,
            const ::DDS_RMI::Identification Ident);

        //oa for error on runtime check
        // virtual CInterfaceProxies find( TInterfaceProperty& property, int max_interfaces) ;
        /**
         * @brief Find the matching interfaces.
         */
        virtual void
        find(TInterfaceProperty& property, int max_interfaces,
            CInterfaceProxies& proxies);

        virtual ::DDS_RMI::Identification
        find(const std::string& server_name, int server_instance_id);

        /**
         * @brief Clear the registry
         */
        virtual void
        clear();

        virtual CInterfaceProxy_ref
        buildProxy(::DDS_RMI::Identification& Ident, std::string proxy_name,
            int proxy_instance);

      private:
        /**
         * @brief To setup the different DDS entities needed by the registry
         */
        virtual void
        setup();

        virtual DDS::ReturnCode_t
        waitForIdentificationData();

        /**
         * @brief To build the proxy for the given service identification
         */
        /*virtual void buildProxy (::DDS_RMI::Identification& Ident,
         CInterfaceProxy_ref & proxy);*/

        CRuntime_ref m_Runtime;
        ::DDS_RMI::IdentificationDataReader_var m_Reader;
        CInterfaceList m_Interfaces;
      };

    }

  }
}

#endif
