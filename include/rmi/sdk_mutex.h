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
 * @brief Synchronisation mechanisms implementation
 *
 * @author Bernard MAUDRY
 *
 *
 * Module   : RMI
 * Class   : Mutex, Locker & Condition
 *
 */

#ifndef SDK_MUTEX_HPP_
#define SDK_MUTEX_HPP_

#include "sdk_mutex_internal.h"

#include "ccpp_dds_dcps.h"

namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {
      /**
       * @brief mutex implementation
       */
      class DDS_SERVICE_API Mutex
      {
      public:
        /**
         * @brief Constructor
         */
      Mutex() : m_mutex(SDKMutexFactory::createSDKMutex())
        {
        }

        /**
         * @brief Destructor
         */
        ~Mutex()
        {
	  delete m_mutex;
        }

        /**
         * @brief To reinit a mutex
         */
        int initialize()
        {
          return m_mutex->initialize();
        }

        /**
         * @brief To lock a mutex
         * must only be called by a locker to avoid stalled mutexes
         */
        int lock()
        {
          return m_mutex->lock();
        }

        /**
         * @brief To unlock a mutex
         * must only be called by a locker to avoid a breach in critical sections
         */
        int unlock()
        {
          return m_mutex->unlock();
        }

        SDKMutex *m_mutex;
      };

      /**
       * @brief critical section protection mechanism implementation
       * Must be used in place of separate mutex calls
       */
      class DDS_SERVICE_API Locker
      {
      public:
        /**
         * @brief Constructor
         */
        Locker(Mutex & mutex) :
          m_mutex(mutex)
        {
          m_mutex.lock();
        }

        /**
         * @brief Destructor
         */
        ~Locker()
        {
          m_mutex.unlock();
        }
      private:
        Mutex & m_mutex;
      };

      /**
       * @brief Condition variable implementation
       */
      class DDS_SERVICE_API Condition
      {
      public:
        /**
         * @brief Constructor
         */
      Condition(Mutex & mutex) : m_cond(SDKConditionFactory::createSDKCondition(*mutex.m_mutex))
        {
        }

        /**
         * @brief Destructor
         */
        ~Condition()
        {
	  delete m_cond;
        }

        /**
         * @brief To destroy a condition
         */
        int destroy()
        {
	  return m_cond->destroy();
        }

        /**
         * @brief To tell the first thread waiting for this condition
         *  that the expected state has been reached
         */
        int signal()
        {
	  return m_cond->signal();
        }

        /**
         * @brief To tell all the threads waiting for this condition
         *  that the expected state has been reached
         */
        int broadcast()
        {
	  return m_cond->broadcast();
        }

        /**
         * @brief To wait for this condition
         */
        void wait(Mutex & mutex)
        {
	  m_cond->wait(*mutex.m_mutex);
        }

        /**
         * @brief To timely wait for this condition
         */
        bool timedWait(Mutex & mutex, Time & time)
        {
	  return m_cond->timedWait(*mutex.m_mutex, time);
        }

        SDKCondition *m_cond;
      };
    }
  }
}

#endif /* SDK_MUTEX_HPP_ */
