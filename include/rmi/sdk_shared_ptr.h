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


#ifndef SDK_SHARED_PTR_HPP_
#define SDK_SHARED_PTR_HPP_

#include "sdk_mutex_internal.h"

namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {

///@cond
      /**
       * \internal
       * @brief base class of reference-couted objects. Only the derived classes pointers
       * can be managed by the shared_ptr template.
       * \endinternal
       */
      class DDS_SERVICE_API RefCounted
        {
        public:

          /**
           * @brief Constructor
           */
          RefCounted()
            {
              val = 0;
              mutex = SDKMutexFactory::createSDKMutex ();
            }

          /**
           * @brief virtual destructor, allowing dispatching to the derived
           * implementations
           */
          virtual ~RefCounted()
            { delete mutex;}

          /**
           * @brief Increment the reference counter
           */
          void inc_refcount()
            {
              mutex->lock ();
              val++;
              mutex->unlock ();
            }

          /**
           * @brief  Decriment the ref counter
           */
          void dec_refcount()
            {
              int res;
              mutex->lock ();
              res = --val;
              mutex->unlock ();
              if (res == 0)
                {
                  delete this;
                }
            }

        private:
          SDKMutex *mutex;
          unsigned int val;
        };
///@endcond

      /**
       * @brief Template class to manage reference counting of shared pointers.
       */
      template<class Ptred>
        class shared_ptr
        {
        public:
          /**
           * @brief Constructor
           */
          shared_ptr()
          {
            m_Ptr = NULL;
          }

          /**
           * @brief Constructor
           */
          shared_ptr(Ptred* ptr)
          {
            m_Ptr = ptr;

            if (ptr)
              {
                ptr->inc_refcount();
              }
          }

          /**
           * @brief Copy constructor
           */
          shared_ptr(shared_ptr const & shr)
          {
            m_Ptr = shr.m_Ptr;

            if (m_Ptr)
              {
                m_Ptr->inc_refcount();
              }
          }

          /**
           * @brief Copy Constructor from a base or a derived class.
           *
           */
          template<class derived>
            shared_ptr(shared_ptr<derived> const & shr)
            {
              m_Ptr = dynamic_cast<Ptred *> (shr.get());

              if (m_Ptr)
                {
                  m_Ptr->inc_refcount();
                }
            }

          /**
           * @brief Destructor
           */
          virtual
          ~shared_ptr()
          {
            if (m_Ptr)
              {
                dynamic_cast<RefCounted *> (m_Ptr)->dec_refcount();
              }
          }

          /**
           * @brief assignment operator
           */
          shared_ptr &
          operator=(shared_ptr const & shr)
          {
            if (m_Ptr)
              {
                dynamic_cast<RefCounted *> (m_Ptr)->dec_refcount();
              }
            m_Ptr = shr.m_Ptr;
            if (m_Ptr)
              {
                m_Ptr->inc_refcount();
              }
            return *this;
          }

          /**
           * @brief reset the pointer to null
           */
          void
          reset()
          {
            if (m_Ptr)
              {
                dynamic_cast<RefCounted *> (m_Ptr)->dec_refcount();
              }
            m_Ptr = NULL;
          }

          /**
           * @brief set the pointer to ptr
           */
          void
          reset(Ptred* ptr)
          {
            if (m_Ptr)
              {
                dynamic_cast<RefCounted *> (m_Ptr)->dec_refcount();
              }
            m_Ptr = ptr;
            if (ptr)
              {
                ptr->inc_refcount();
              }
          }

          /**
           * @brief Calling Operator
           */
          Ptred*
          operator->() const
          {
            return m_Ptr;
          }

          /**
           * @brief provides the pointer
           */
          Ptred*
          get() const
          {
            return m_Ptr;
          }
        private:
          Ptred* m_Ptr;
        };
    }
  }
}

#endif /* SDK_SHARED_PTR_HPP_ */
