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

#ifndef TPSWAITINGREQUESTSTHREAD_H_
#define TPSWAITINGREQUESTSTHREAD_H_

#include "dds_service_sdk.h"
#include "PriorityThreadPool.h"
#include "sdk_cinterfacemanagerimpl.h"
#include <list>
#include <set>

namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {

      class tps_WaitingRequestsThread : public virtual Thread, public virtual PriorityThreadPoolObserver
      {
      public:
        tps_WaitingRequestsThread(PriorityThreadPool_ref pool);

        virtual
        ~tps_WaitingRequestsThread();

        virtual void
        run();

        void
        execute(CRequestProcessingTask_ref task);

        void
        TaskCompleted(ComparableRunnable_ref task);

        Mutex m_mutex;
        Condition m_waitReqCond;

      private:
        void
        _copyWaitingToNewRequests();

        PriorityThreadPool_ref m_thread_pool;
        //std::list<ThreadPerServiceDispatcherTask_ref> m_waitingRequests;
        std::list<CRequestProcessingTask_ref> m_waitingRequests;
        std::priority_queue<CRequestProcessingTask_ref, std::vector<CRequestProcessingTask_ref>, Comparator> m_NewRequests;
        std::set<CInterfaceManagerImpl *> m_submittedRequestsMgers;
      };

    } /* namespace DDS_RMI */
  } /* namespace opensplice */
} /* namespace org */

#endif /* TPSWAITINGREQUESTSTHREAD_H_ */
