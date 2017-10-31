#ifndef Flood_BOILERPLATE_H
#define Flood_BOILERPLATE_H
#include "Boilerplate.h"
#include "Flood.h"
#include "ndds/ndds_cpp.h"

namespace FloodMsg
{
    class Publisher 
    {
        public:
            Publisher(DDSBoilerplate * boiler_object, char const * user_topic);
            Flood *instance;
            int init_publisher();
            void publish();
            int kill();

        private:
            char const * user_topic_;
            DDSBoilerplate * boiler_object_;
            DDSDomainParticipant *participant_;
            FloodDataWriter * Flood_writer_;
            DDS_ReturnCode_t retcode_;
            DDS_InstanceHandle_t instance_handle_ ;
    };

    class FloodListener : public DDSDataReaderListener 
    {
        public:
            virtual void on_requested_deadline_missed(
                DDSDataReader* /*reader*/,
                const DDS_RequestedDeadlineMissedStatus& /*status*/) {}

            virtual void on_requested_incompatible_qos(
                DDSDataReader* /*reader*/,
                const DDS_RequestedIncompatibleQosStatus& /*status*/) {}

            virtual void on_sample_rejected(
                DDSDataReader* /*reader*/,
                const DDS_SampleRejectedStatus& /*status*/) {}

            virtual void on_liveliness_changed(
                DDSDataReader* /*reader*/,
                const DDS_LivelinessChangedStatus& /*status*/) {}

            virtual void on_sample_lost(
                DDSDataReader* /*reader*/,
                const DDS_SampleLostStatus& /*status*/) {}

            virtual void on_subscription_matched(
                DDSDataReader* /*reader*/,
                const DDS_SubscriptionMatchedStatus& /*status*/) {}

            virtual void on_data_available(DDSDataReader* reader);

            FloodSeq data_seq;
            DDS_SampleInfoSeq info_seq;
    };

    class Subscriber
    {
        public:
            Subscriber(DDSBoilerplate * boiler_object, char const * user_topic);
            int init_subscriber();
            int kill();
            FloodSeq get_data_seq();
            DDS_SampleInfoSeq get_info_seq();
            bool is_read();

        private:
            char const * user_topic_;
            DDSBoilerplate * boiler_object_;
            DDSDomainParticipant *participant_;
            FloodListener *reader_listener_;
            DDS_ReturnCode_t retcode_;
    };
}
#endif