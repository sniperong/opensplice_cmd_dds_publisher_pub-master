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
 * @brief Templates for the server side generated code.
 *
 * @author Bernard MAUDRY
 *
 *
 * Module   : RMI
 * Class   : many
 *
 *
 */
#include <iostream>
#include "dds_service_sdk.h"

#define READ_DIFFUSION_REQUESTS(scope,interface,operation) \
  org::opensplice::DDS_RMI::ReceiverCode<interface##Interface, \
  ::DDS_RMI::scope::interface::operation##_request, \
  ::DDS_RMI::scope::interface::operation##_requestSeq, \
  ::DDS_RMI::scope::interface::operation##_requestDataReader, \
  ::DDS_RMI::scope::interface::operation##_requestDataReader_var>::readRequests \
     (this, "::" #scope "::" #interface "::" #operation, _op_##operation, interface##Interface_##operation##_call_, interface##Interface_##operation##_dispose_)

#define READ_REQUESTS(scope,interface,operation) \
  org::opensplice::DDS_RMI::ServerCode<interface##Interface, \
  ::DDS_RMI::scope::interface::operation##_request, \
  ::DDS_RMI::scope::interface::operation##_requestSeq, \
  ::DDS_RMI::scope::interface::operation##_requestDataReader, \
  ::DDS_RMI::scope::interface::operation##_requestDataReader_var, \
  ::DDS_RMI::scope::interface::operation##_reply, \
  ::DDS_RMI::scope::interface::operation##_replyDataWriter, \
  ::DDS_RMI::scope::interface::operation##_replyDataWriter_var>::readRequests \
     (this, "::" #scope "::" #interface "::" #operation, _op_##operation, interface##Interface_##operation##_call_)

namespace org
{
  namespace opensplice
  {
    namespace DDS_RMI
    {
      template<class Interface, class Request>
      class OnewayRmiRequest : public ServiceInvocation
      {
      public:
        typedef void
            (*ImplOnewayCall)(Interface* _intf, Request& in);

        OnewayRmiRequest(Request req, Interface * servant, int op_code,
            const char * method_name, ImplOnewayCall callFct , DDS::Time_t timestamp):
              ServiceInvocation(method_name, timestamp),
              m_req(req), m_servant(servant),
              m_op_code(op_code), m_onewayCallFct(callFct)
        {}

        virtual void
        invoke()
        {
          m_onewayCallFct(m_servant.get(), m_req);
        }


      protected :
        Request m_req;
        shared_ptr<Interface> m_servant;
        int m_op_code;
        ImplOnewayCall m_onewayCallFct;

      };

      template<class Interface, class Request, class Reply, class Writer, class Writer_var>
      class RmiRequest : virtual public ServiceInvocation
      {
      public:

        typedef void
                (*ImplCall)(Interface* _intf, Request& in, Reply& out);

        RmiRequest(Request req, Interface * servant, int op_code,
            const char * method_name, ImplCall callFct , DDS::Time_t timestamp):
              ServiceInvocation(method_name, timestamp),
              m_req(req), m_servant(servant),
              m_op_code(op_code), m_callFct(callFct)
        { }

        virtual
        ~RmiRequest()
        {}

        virtual void
        invoke(){
          // Declare out topic for the method
         Reply _out;
         // Fill the header
         _out.req_info = m_req.req_info;
         Writer_var _dw = Writer::_narrow(m_servant->getReplyWriter(m_op_code));
         // Call the actual method
         m_callFct(m_servant.get(), m_req, _out);
         // Publish the reply
         int status = _dw->write(_out, DDS::HANDLE_NIL);
         Sync_Print::checkStatus(status,
             (std::string("Sending the reply of method") + getName()).c_str());
        }

      protected:
        Request m_req;
        shared_ptr<Interface> m_servant;
        int m_op_code;
        ImplCall m_callFct;

      };


      template<class Interface, class Request, class RequestSeq, class Reader,
          class Reader_var, class Reply, class Writer, class Writer_var>
        class ServerCode
        {
        public:
          typedef void
          (*ImplCall)(Interface* _intf, Request& in, Reply& out);

          typedef RmiRequest<Interface, Request, Reply, Writer, Writer_var> InvocationObject;
          typedef std::vector<InvocationObject *> InvocationObjectCollection;

          //static std::vector<InvocationObject *>
          static std::vector<ServiceInvocation *>
          readRequests(Interface* _intf, const char * method_name,
              int op_code, ImplCall callFct)
          {
            std::vector<InvocationObject *> requests;
            // Declare in topic for the method
            RequestSeq _inSeq;
            DDS::SampleInfoSeq _infoSeq;

            // Receive the request topic
            Reader_var _dr = Reader::_narrow(_intf->getRequestReader(op_code));

            // Wait reply at max timeout and throw exception in case of timeout expired
#ifndef LITE
            DDS::ReturnCode_t status = _dr->take(_inSeq, _infoSeq,
                DDS::LENGTH_UNLIMITED, DDS::ANY_SAMPLE_STATE,
                DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE);
#else
            DDS::ReturnCode_t status = _dr->take(_inSeq, _infoSeq,
                1, DDS::ANY_SAMPLE_STATE,
                DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE);
#endif
            if (status != DDS::RETCODE_OK && status != DDS::RETCODE_NO_DATA)
              {
                std::cout << "Failed to take requests for method " << method_name
                    << " status= " << status << " seq length= "
                    << _inSeq.length() << std::endl;
              }

            if (_inSeq.length() < 1)
              {
                // If no sample retrieved throw Receive_Exception (todo)
                //std::cout << "seq length nul for method " << method_name << std::endl;
                status = _dr->return_loan(_inSeq, _infoSeq);
                return std::vector<ServiceInvocation*> (requests.begin(), requests.end());
              }

            // loop on valid samples
            for (unsigned int each_sample = 0; each_sample < _inSeq.length(); each_sample++)
              {
                // if this sample is not for us , then skip it
                if (!(_infoSeq[each_sample].valid_data) ||
                        (!_intf->isMyIdent(_inSeq[each_sample].req_info.service_id)))
                  {
                    continue;
                  }

                // Declare out topic for the method
                Reply _out;
                // Fill the header
                _out.req_info = _inSeq[each_sample].req_info;
                Writer_var _dw = Writer::_narrow(_intf->getReplyWriter(op_code));

                if(_infoSeq[each_sample].instance_state == DDS::NOT_ALIVE_DISPOSED_INSTANCE_STATE)
                  {
                    // disposing and unregistering the reply instance
                    status = _dw->dispose(_out, DDS::HANDLE_NIL);
                    Sync_Print::checkStatus(status,
                        (std::string("Reply disposal of method") + method_name).c_str());
                    status = _dw->unregister_instance(_out, DDS::HANDLE_NIL);
                    Sync_Print::checkStatus(status,
                        (std::string("Reply unregistering of method") + method_name).c_str());
                  }
                else
                  {
                    requests.push_back(new InvocationObject(_inSeq[each_sample], _intf,
                        op_code, method_name, callFct,_infoSeq[each_sample].reception_timestamp));

                  }
              }

            // Memory management
            status = _dr->return_loan(_inSeq, _infoSeq);
            Sync_Print::checkStatus(status,
                    (std::string("return_loan of method ") + method_name).c_str());

            return std::vector<ServiceInvocation*> (requests.begin(), requests.end());

          };

        };

      template<class Interface, class Request, class RequestSeq, class Reader,
          class Reader_var>
        class ReceiverCode
        {
        public:
          typedef void
          (*ImplCall)(Interface* _intf, Request& in);

          typedef OnewayRmiRequest<Interface, Request> InvocationObject;
          typedef std::vector<InvocationObject *> InvocationObjectCollection;

          static std::vector<ServiceInvocation *>
          readRequests(Interface* _intf, const char * method_name,
              int op_code, ImplCall callFct, ImplCall Dispose)
          {
            std::vector<InvocationObject *> requests;
            // Declare in topic for the method
            RequestSeq _inSeq;
            DDS::SampleInfoSeq _infoSeq;

            // Receive the request topic
            Reader_var _dr = Reader::_narrow(_intf->getRequestReader(op_code));
            DDS::QueryCondition_var Filter = _intf->getFilter(op_code);
            DDS::ReturnCode_t status;
            if (NULL != Filter.in())
              {
                // Receive the filtered samples
#ifndef LITE
                status = _dr->take_w_condition(_inSeq, _infoSeq,
                    DDS::LENGTH_UNLIMITED, Filter.in());
#else
                status = _dr->take_w_condition(_inSeq, _infoSeq,
                    1, Filter.in());
#endif
              }
            else
              {
                // Wait request
#ifndef LITE
                status = _dr->take(_inSeq, _infoSeq, DDS::LENGTH_UNLIMITED,
                    DDS::ANY_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
                    DDS::ANY_INSTANCE_STATE);
#else
                status = _dr->take(_inSeq, _infoSeq, 1,
                    DDS::ANY_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
                    DDS::ANY_INSTANCE_STATE);
#endif
              }

            if (status != DDS::RETCODE_OK && status != DDS::RETCODE_NO_DATA)
              {
                std::cout << "Failed to take requests for method " << method_name
                    << " status= " << status << " seq length= "
                    << _inSeq.length() << std::endl;
              }

            if (_inSeq.length() < 1)
              {
                // If no sample retrieved throw Receive_Exception (todo)
                //std::cout << "seq length nul for method " << method_name << std::endl;
                status = _dr->return_loan(_inSeq, _infoSeq);
                return std::vector<ServiceInvocation*> (requests.begin(), requests.end());
              }

            // loop on valid samples
            for (unsigned int each_sample = 0; each_sample < _inSeq.length(); each_sample++)
              {
                // if this sample is not for us , then skip it
                if ((!_intf->isMyIdent(_inSeq[each_sample].req_info.service_id)))
                  {
                    continue;
                  }

                if(_infoSeq[each_sample].instance_state == DDS::NOT_ALIVE_DISPOSED_INSTANCE_STATE)
                  Dispose(_intf, _inSeq[each_sample]);
                else
                  if(_infoSeq[each_sample].valid_data)
                  {
                    requests.push_back(new InvocationObject(_inSeq[each_sample], _intf,
                          op_code, method_name, callFct,_infoSeq[each_sample].reception_timestamp));

                  }
              }

            // Memory management
            status = _dr->return_loan(_inSeq, _infoSeq);
            Sync_Print::checkStatus(status,
                    (std::string("return_loan of method ") + method_name).c_str());

            return std::vector<ServiceInvocation*> (requests.begin(), requests.end());

          };

        };

    }
  }
}
