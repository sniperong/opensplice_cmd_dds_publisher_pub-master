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

#ifndef SDK_THREAD_HPP_
#define SDK_THREAD_HPP_

#include <string>
#include "os_thread.h"
#include "sdk_shared_ptr.h"


namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {

      class DDS_SERVICE_API Runnable {
      public:

        virtual
        ~Runnable() {};

        /**
         * @brief Core of the thread; to be implemented in the derivative class
         */
        virtual void
        run () = 0;

      };


      class DDS_SERVICE_API ComparableRunnable : virtual public RefCounted, virtual public Runnable
      {
      public:
        virtual
        ~ComparableRunnable() {};

        virtual bool operator<(const ComparableRunnable&) const = 0;
      };
      typedef shared_ptr<ComparableRunnable> ComparableRunnable_ref;

      //template <typename T>
      class Comparator
      {
      public:
        bool operator() (const ComparableRunnable_ref c1, const ComparableRunnable_ref c2) const
          {
            return *c1.get()<*c2.get();
          }
      };


      class DDS_SERVICE_API Thread : virtual public Runnable
      {
      public:
        /**
         * @brief Constructor setting the name of the thread
         */
        Thread(std::string name) :
          m_Name(name), m_ThreadId(OS_THREAD_ID_NONE)
        {
        }

        /**
         * @brief Destructor
         */
        virtual
        ~Thread();

        /**
         * @brief Core of the thread; to be implemented in the derivative class
         */
        virtual void
        run () = 0;

        /**
         * @brief Starts the thread processing
         */
        void
        start();

        /**
         * @brief Ask the thread to stop the processing and wait for the effective stop
         */
        void
        waitStop();

        const char *
        getCName ();

      private:
        std::string m_Name;
        os_threadId m_ThreadId;
      };
    }

  }
}


/**
 * @brief Function to call the core of threads
 */
extern "C"
{
  static void *start_thread(void * param)
  {
    using namespace org::opensplice::DDS_RMI;
    Runnable * This = (Runnable *) param;
#ifdef LITE
    int status = dds_thread_init (This->getCName ());
    if (status != DDS_RETCODE_OK)
    {
      printf("start_thread : Failed to initialize the thread (error %d)!", status);
      return NULL;
    }
#endif
    This->run();
#ifdef LITE
    dds_thread_fini ();
#endif
    return NULL;
  }
}


#endif /* SDK_THREAD_HPP_ */
