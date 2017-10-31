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
 */
#ifndef SDK_MUTEX_INTERNAL_HPP_
#define SDK_MUTEX_INTERNAL_HPP_

#ifndef OS_TIME_H
#ifdef LITE
#include "dds/os/vortex_os.h"
typedef struct os_time {
    /** Seconds since the Unix epoch; 1-jan-1970 00:00:00 (UTC) */
#ifdef WIN32
    INT_PTR tv_sec;
#else
    int tv_sec;
#endif
    /** Number of nanoseconds since the Unix epoch, modulo 10^9. */
    int32_t tv_nsec;
} os_time;
#else
#include "os_time.h"
#endif
#endif

// For Windows build.
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#include "WindowsBuild.h"
#else
#define DDS_SERVICE_API
#endif

namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {
      typedef os_time Time;

      class DDS_SERVICE_API SDKMutex
      {
       public:

        SDKMutex() {};

        virtual ~SDKMutex() {};
        virtual int initialize() = 0;
        virtual int lock() = 0;
        virtual int unlock() = 0;
      };


      class DDS_SERVICE_API SDKCondition
      {
       public:

        SDKCondition() {};
        virtual ~SDKCondition() {};
        virtual int destroy() = 0;
        virtual int signal() = 0;
        virtual int broadcast() = 0;
        virtual void wait(SDKMutex & mutex) = 0;
        virtual bool timedWait(SDKMutex & mutex, Time & time) = 0;
      };

      class DDS_SERVICE_API SDKMutexFactory {
       public:
        static SDKMutex *createSDKMutex();
      };

      class SDKConditionFactory {
       public:
        static SDKCondition *createSDKCondition(SDKMutex &mutex);
      };
    }
  }
}


#endif
