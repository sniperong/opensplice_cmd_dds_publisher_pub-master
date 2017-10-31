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
 * @brief Base class of all the asynchronous requests handlers.
 *  Derived by generated code to implement handleReply method.
 *
 * @author Bernard MAUDRY
 *
 *
 * Module   : RMI
 * Class   : CAsyncReplyHandlerImpl
 *
 *
 */

#ifndef SDK_CASYNCREPLYHANDLER_HPP_
#define SDK_CASYNCREPLYHANDLER_HPP_

#include "dds_service_sdk.h"
#include "sdk_garbagereader.h"
#include "sdk_mutex.h"

namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {

      class DDS_SERVICE_API CAsyncReplyHandlerImpl : public CAsyncReplyHandler
      {
      public:
        CAsyncReplyHandlerImpl() :
          bActive(false)
        {
        }

        /**
         * @brief called by the Runtime to wait for the reply.
         */
        virtual void
        asyncWait(DDS::QueryCondition * query);

        /**
         * @brief Called by the runtime to process the reply by the user application
         */
        virtual void
        handleReply(DDS::ReadCondition * query) = 0;

        /**
         * @brief Called by the runtime to stop the ReplyWaiter thread
         */
        static void
        terminate();

        /**
         * @brief Called by the proxy interface to add a reader for garbage collection
         */
        static void
        garbageCollectionAdd(org::opensplice::DDS_RMI::GarbageReaderBase::ref gcRdr);

        /**
         * @brief Called by the proxy interface to remove a reader for garbage collection
         */
        static void
        garbageCollectionRemove(org::opensplice::DDS_RMI::GarbageReaderBase::ref gcRdr);

        /**
         * @brief Called by the generated proxy to pause/resume garbage collection of a reader
         */
        static void
        garbageCollection(org::opensplice::DDS_RMI::GarbageReaderBase::ref gcRdr, bool start);

        bool bActive;

      private:
        static Mutex m_Mutex;
      };
    }

  }
}

#endif /* SDK_CASYNCREPLYHANDLER_HPP_ */
