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
#ifndef SDK_GARBAGEREADER_HPP_
#define SDK_GARBAGEREADER_HPP_

#include "ccpp_dds_dcps.h"
#include "dds_service_sdk.h"

#define OPERATION_GARBAGE_READER(scope,interface,operation) \
        org::opensplice::DDS_RMI::GarbageReader< ::DDS_RMI::scope::interface::operation##_reply, \
        ::DDS_RMI::scope::interface::operation##_replySeq, \
        ::DDS_RMI::scope::interface::operation##_replyDataReader, \
        ::DDS_RMI::scope::interface::operation##_replyDataReader_var>

namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {

      class GarbageReaderBase : public virtual RefCounted
      {
      public:
          typedef org::opensplice::DDS_RMI::shared_ptr< GarbageReaderBase > ref;

          GarbageReaderBase() { }
          virtual ~GarbageReaderBase() { }

          virtual bool pauze() = 0;
          virtual bool resume() = 0;

          virtual void clean() = 0;

          virtual DDS::StatusCondition_ptr condition() = 0;
          virtual DDS::DataReader_ptr reader() = 0;
      };

      template<class Reply, class ReplySeq, class Reader, class Reader_var>
      class GarbageReader : public GarbageReaderBase
      {
      public:
          GarbageReader(DDS::DataReader_var rdr) :
              m_stopCnt(1), // we start pauzed
              m_reader(Reader::_narrow(rdr))
          {
          }

          virtual ~GarbageReader()
          {
              this->m_reader = NULL;
          }

          virtual bool pauze() {
              Locker locker(m_Mutex);
              // Garbage collection pauze request.
              bool first = false;
              if (m_stopCnt == 0) {
                  // This is a first requests. So, the garbage
                  // collection needs to be switched off.
                  first = true;
              }
              m_stopCnt++;
              return first;
          }

          virtual bool resume() {
              Locker locker(m_Mutex);
              // Garbage collection resume request.
              bool last = false;
              if (m_stopCnt > 0) {
                  m_stopCnt--;
                  if (m_stopCnt == 0) {
                      // There are no more requests that need the
                      // garbage collection to be switched off.
                      last = true;
                  }
              }
              return last;
          }

          virtual void clean()
          {
              Locker locker(m_Mutex);
              ReplySeq _replies;
              DDS::SampleInfoSeq _infoSeq;

              if (this->m_reader.in() != NULL) {
#ifndef LITE
                  DDS::ReturnCode_t status = this->m_reader->take(_replies,
                                                                  _infoSeq,
                                                                  DDS::LENGTH_UNLIMITED,
                                                                  DDS::ANY_SAMPLE_STATE,
                                                                  DDS::ANY_VIEW_STATE,
                                                                  DDS::ANY_INSTANCE_STATE);
                  this->m_reader->return_loan(_replies, _infoSeq);
#else
                  {
                      do {
                          DDS::ReturnCode_t status = this->m_reader->take(_replies,
                                                                          _infoSeq,
                                                                          1,
                                                                          DDS::ANY_SAMPLE_STATE,
                                                                          DDS::ANY_VIEW_STATE,
                                                                          DDS::ANY_INSTANCE_STATE);
                          this->m_reader->return_loan(_replies, _infoSeq);
                      } while (_replies.length() == 1);
                  }
#endif
              }
          }

          virtual DDS::StatusCondition_ptr condition()
          {
              Locker locker(m_Mutex);
              DDS::StatusCondition_ptr cond = NULL;
              if (this->m_reader.in() != NULL) {
                  cond = this->m_reader->get_statuscondition();
              }
              return cond;
          }

          virtual DDS::DataReader_ptr reader()
          {
              return this->m_reader.in();
          }

      private:
          int m_stopCnt;
          Mutex m_Mutex;
          Reader_var m_reader;
      };
    }

  }
}

#endif /* SDK_GARBAGEREADER_HPP_ */
