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

#ifndef PRIORITYTHREADPOOL_H_
#define PRIORITYTHREADPOOL_H_

#include "sdk_thread.h"
#include "sdk_mutex.h"
#include <queue>
#include <set>
#include <list>


namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {

      class PriorityThreadPoolObserver
      {
      public:
        virtual ~PriorityThreadPoolObserver() {};

        virtual void
        TaskCompleted(ComparableRunnable_ref task) = 0;
      };

      class DDS_SERVICE_API PriorityThreadPool : virtual public Runnable, virtual public RefCounted
      {
      public:
        /**
         * Creates a Single Thread Pool with the given attributes
         */
        PriorityThreadPool(os_threadAttr * attr);

        PriorityThreadPool(
          int max_threads, /* Maximum number of threads in pool (0 == infinite) */
          int max_queue_size,   /* Maximum number of queued requests (0 == infinite) */
          os_threadAttr * attr   /* Attributes used to create pool threads (can be NULL) */
        );

        virtual
        ~PriorityThreadPool();

        os_result
        execute(ComparableRunnable_ref task);

        std::list<os_result>
        executeAll(std::list<ComparableRunnable_ref> & tasks);

        virtual void
        stop(bool wait_for_completion);

        virtual bool
        isStopped();

        virtual void
        setMaximumPoolSize(int max_threads);

        virtual int
        getMaximumPoolSize();

        virtual void
        run();

        virtual void
        registerObserver(PriorityThreadPoolObserver *);

        virtual void
        unregisterObserver(PriorityThreadPoolObserver *);

      private:
        os_result
        createNewThread(os_threadId * id);

        os_result
        _execute(ComparableRunnable_ref task);

        std::priority_queue<ComparableRunnable_ref, std::vector<ComparableRunnable_ref>, Comparator> m_tasks_queue;
        std::vector<os_threadId> m_threads; // all created threads ids
        int m_threads_count; // current threads count
        int m_max_pool_size;
        int m_max_queue_size;
        os_threadAttr m_attr;
        Mutex m_mutex;                  /* Pool guard mutex */
        org::opensplice::DDS_RMI::Condition m_tasksCond;
        bool m_stopped;
        std::set<PriorityThreadPoolObserver *> m_observers;


      };

      typedef shared_ptr<PriorityThreadPool> PriorityThreadPool_ref;

    } /* namespace DDS_RMI */
  } /* namespace opensplice */
} /* namespace org */

#endif /* PRIORITYTHREADPOOL_H_ */
