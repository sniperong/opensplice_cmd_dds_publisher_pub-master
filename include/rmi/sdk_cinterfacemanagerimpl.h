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
 * @brief This class manages the implementation of the remote server interface
 *
 * @author Bernard MAUDRY
 *
 * Module   : RMI
 * Class   : CInterfaceManagerImpl
 *
 *
 */

#ifndef _SDK_CINTERFACEMANAGERIMPL_HPP_
#define _SDK_CINTERFACEMANAGERIMPL_HPP_

#include "dds_service_sdk.h"
#include "sdk_cruntimeimpl.h"
#include "sdk_cinterfaceimpl.h"

namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {
      /**
       * @brief This class allows to manage all the aspects related to the execution of a Interface instance
       *  (on the server side), such as threading, scheduling class, priority, as well as
       *  status, e.g., running, paused, etc.
       *
       */
      class CInterfaceManagerImpl : public virtual CInterfaceManager
      {
      public:
        /**
         * @brief Constructor
         */
        CInterfaceManagerImpl(const CInterface_ref& intf,
            const std::string& name, CRuntimeImpl *runtime);

        /**
         * @brief Destructor
         */
        virtual
        ~CInterfaceManagerImpl();

        /**
         * @brief Deprecated.
         */
        virtual void
        manage(const TSchedulingTraits& sched = DEFAULT_SCHEDULING_TRAITS,
            bool paused = true);

        /**
         *  @brief Deprecated
         */
        virtual void
        suspend();

        /**
         *  @brief Deprecated
         */
        virtual void
        resume();

        /**
         * @brief Deprecated
         */
        virtual void
        unManage();

        /**
         * @brief starts waiting for incoming requests
         */
        virtual void
        run();

        /**
         * @brief stops waiting for incoming requests
         */
        virtual void
        shutdown(bool wait_for_completion = true);

        /**
         * @brief returns true if the service interface is running
         */
        virtual bool
        is_running();

        /**
         *  @brief To get the managed interface
         */
        virtual CInterfaceImpl_ref&
        getInterface()
        {
          return m_Interface;
        }

        std::vector<CRequestProcessingTask_ref>
        getRequestProcessingTasks(const DDS::Condition_ptr requestInvoked);

      private:
        CInterfaceImpl_ref m_Interface;
        std::string m_Name;
        CRuntimeImpl *m_runtime;
        bool m_isReqProcessing;
        Mutex m_mutex;
      };

    }
  }
}

#endif
