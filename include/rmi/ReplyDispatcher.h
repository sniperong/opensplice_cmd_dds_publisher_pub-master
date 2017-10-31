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
#ifndef _REPLYDISPATCHER_H_
#define _REPLYDISPATCHER_H_

#include "sdk_mutex.h"
#include "dds_service_sdk.h"
#include "sdk_cinterfaceproxyimpl.h"

#include <map>
#include <string>

#define OPERATION_REPLY_DISPATCHER(scope,interface,operation) \
        org::opensplice::DDS_RMI::ReplyDispatcher< ::DDS_RMI::scope::interface::operation##_reply, \
        ::DDS_RMI::scope::interface::operation##_replySeq, \
        ::DDS_RMI::scope::interface::operation##_replyDataReader, \
        ::DDS_RMI::scope::interface::operation##_replyDataReader_var> \


namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {

      template<class Reply, class ReplySeq, class Reader,
          class Reader_var>
        class ReplyDispatcher : public virtual RefCounted
        {

        public:

          ReplyDispatcher(org::opensplice::DDS_RMI::CInterfaceProxyImpl* p, int code) :
            proxy(p), op_code(code), mapMutex(), leaderMutex(), newRepliesCond(
                mapMutex), repliesMap(), leader(false), waitset(), sc()
          {
            sc = proxy->getReplyReader(op_code)->get_statuscondition();
            Sync_Print::checkHandle(sc.in(),
                "ReplyDispatcher::getReply : get_statuscondition");
            DDS::ReturnCode_t status = sc->set_enabled_statuses(
                DDS::DATA_AVAILABLE_STATUS);
            Sync_Print::checkStatus(status,
                "ReplyDispatcher::getReply : set_enabled_statuses");
            waitset.attach_condition(sc.in());
          }

          ~ReplyDispatcher()
          {
          }

          /**
           * Retrieves the DDS reply corresponding to the given request id.
           */
          Reply
          getReply(int req_id)
          {
            if(proxy->getTimeout() == 0)
              throw ::org::opensplice::DDS_RMI::TIMEOUT();
            if (proxy->isMultiThreaded())
              return getReply_MT(req_id);
            else
              return getReply_ST(req_id);
          }

        private:

          /**
           * Retrieves the DDS reply corresponding to the given request id, in a SINGLE THREADED client configuration
           */
          Reply
          getReply_ST(unsigned int req_id)
          {

            Reply reply;
            unsigned int rep_id = req_id + 1; // just a value different than req_id
            DDS::ConditionSeq_var active = new DDS::ConditionSeq();

            while (rep_id != req_id)
              {
                DDS::ReturnCode_t status = waitset.wait(active, getTimeout());
                if (status == DDS::RETCODE_OK)
                  {
                    proxy->getReplyReader(op_code)->get_status_changes();
                    ReplySeq data;
                    DDS::SampleInfoSeq infos = takeData(data);
                    for (unsigned int i = 0; i < data.length(); i++)
                      {
                        if (infos[i].valid_data && proxy->isMyReply(data[i].req_info.client_id))
                          {
                            if (req_id == data[i].req_info.client_id.request_id)
                              {
                                reply = data[i];
                                rep_id = req_id;
                              }
                            else
                              {
                                Sync_Print::stdOutFormat(
                                    "Unexpected reply with id %d",
                                    data[i].req_info.client_id.request_id);
                              }
                          }
                      }
                  }
                else
                  {
                    if (status == DDS::RETCODE_TIMEOUT)
                      throw ::org::opensplice::DDS_RMI::TIMEOUT();
                    else
                      throw ::org::opensplice::DDS_RMI::INTERNAL_ERROR(
                          "Failed to wait for the replies", status);
                  }

              }

              return reply;
          }

          /**
           * Retrieves the DDS reply corresponding to the given request id, in a MULTI THREADED client configuration
           *
           */
          Reply
          getReply_MT(unsigned int req_id)
          {

            Reply reply;
            bool found = false;
            DDS::ReturnCode_t status = DDS::RETCODE_OK;

            while (!found)
              {
                mapMutex.lock();
                found = findAndRemoveReply(req_id, reply);
                while (leader && !found)
                  {
                    newRepliesCond.wait(mapMutex);
                    found = findAndRemoveReply(req_id, reply);
                  }
                mapMutex.unlock();

                if (found)
                  break;

                leaderMutex.lock();

                mapMutex.lock();
                found = findAndRemoveReply(req_id, reply);
                if (!found){
                    leader = true;
                }
                else
                  {
                    leader = false;
                    newRepliesCond.broadcast(); // waking up the followers because no more leader
                  }
                mapMutex.unlock();

                if (!found)
                  {
                    DDS::ConditionSeq_var active = new DDS::ConditionSeq();
                    status = waitset.wait(active, getTimeout());

                    mapMutex.lock();
                    if (status == DDS::RETCODE_OK) {
                      try {
                        proxy->getReplyReader(op_code)->get_status_changes();
                        ReplySeq data;
                        DDS::SampleInfoSeq infos = takeData(data);
                        for (unsigned int i = 0; i < data.length(); i++)
                          {
                            if (infos[i].valid_data && proxy->isMyReply(data[i].req_info.client_id))
                              {
                                if (req_id
                                    == data[i].req_info.client_id.request_id)
                                  {
                                    reply = data[i];
                                    found = true;
                                  }
                                else
                                  {
                                    repliesMap.insert(std::make_pair(
                                        data[i].req_info.client_id.request_id,
                                        data[i]));
                                  }
                              }
                          }
                      } catch (const ::org::opensplice::DDS_RMI::SystemException &ex) {
                          leader = false;
                          newRepliesCond.broadcast();
                          mapMutex.unlock();
                          leaderMutex.unlock();
                          throw;
                      }
                    }

                    leader = false;
                    newRepliesCond.broadcast(); // waking up the followers because no more leader
                    mapMutex.unlock();
                  }
                  leaderMutex.unlock();
               //TODO: enhance timeout management. Waitset timeout is not sufficient to
               //throw a Timeout exception
                if (status != DDS::RETCODE_OK)
                  {
                    if (status == DDS::RETCODE_TIMEOUT)
                      throw ::org::opensplice::DDS_RMI::TIMEOUT();
                      /*Sync_Print::stdOutFormat(
                            "Reply (DDS) wait timeout. Try again ...");*/
                    else
                      throw ::org::opensplice::DDS_RMI::INTERNAL_ERROR(
                          "Failed to wait for the replies", status);

                  }

              }

            return reply;
          }

          DDS::SampleInfoSeq
          takeData(ReplySeq& seq)
          {
            // Declare in topic for the method
            ReplySeq _replies;
            DDS::SampleInfoSeq _infoSeq, _outInfos;

            Reader_var _dr = Reader::_narrow(proxy->getReplyReader(op_code));
#ifndef LITE
            DDS::ReturnCode_t status = _dr->take(_replies, _infoSeq,
                DDS::LENGTH_UNLIMITED, DDS::ANY_SAMPLE_STATE,
                DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE);
#else
            DDS::ReturnCode_t status = _dr->take(_replies, _infoSeq,
                1, DDS::ANY_SAMPLE_STATE,
                DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE);
#endif
            if (status != 0 && status != 11)
              {
                ::org::opensplice::DDS_RMI::INTERNAL_ERROR ex(
                    "Failed to take reply samples", status);
                throw ex;
              }

            if (_replies.length() < 1)
              {
                _dr->return_loan(_replies, _infoSeq);
                throw ::org::opensplice::DDS_RMI::INTERNAL_ERROR(
                    "Reply sample Not found", 0);
              }
            else
              {
                seq = _replies;
                _outInfos = _infoSeq;
              }
            _dr->return_loan(_replies, _infoSeq);
            return _outInfos;
          }

          bool
          findAndRemoveReply(int req_id, Reply & rep)
          {
            typename std::map<DDS::ULong, Reply>::iterator it =
                repliesMap.find(req_id);
            if (it != repliesMap.end())
              {
                rep = it->second;
                repliesMap.erase(it);
                return true;
              }

            return false;
          }

          DDS::Duration_t
          getTimeout()
          {
            int millis = proxy->getTimeout();
            DDS::Duration_t timeout;
            if (millis == -1)
              timeout = DDS::DURATION_INFINITE;
            else
              {
                if(millis == 0)
                  timeout = DDS::DURATION_ZERO;
                else {
                    timeout.sec = millis / 1000;
                    millis -= timeout.sec * 1000;
                    timeout.nanosec = millis * 1000000;
                }

              }

            return timeout;
          }

          ::org::opensplice::DDS_RMI::CInterfaceProxyImpl* proxy;
          int op_code;
          Mutex mapMutex;
          Mutex leaderMutex;
          Condition newRepliesCond;
          std::map<DDS::ULong, Reply> repliesMap;
          bool leader; // true if there is a current leader
          DDS::WaitSet waitset;
          DDS::StatusCondition_var sc;

        };

    }
  }
}

#endif
