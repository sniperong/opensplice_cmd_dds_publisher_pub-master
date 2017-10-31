#ifndef VELOCITIESDATADCPS_IMPL_H_
#define VELOCITIESDATADCPS_IMPL_H_

#include "ccpp.h"
#include "ccpp_VelocitiesData.h"
#include "TypeSupportMetaHolder.h"
#include "TypeSupport.h"
#include "FooDataWriter_impl.h"
#include "FooDataReader_impl.h"
#include "FooDataReaderView_impl.h"


namespace VelocitiesData {

    class  VelocitiesTypeSupportMetaHolder : public ::DDS::OpenSplice::TypeSupportMetaHolder
    {
    public:
        VelocitiesTypeSupportMetaHolder ();
        virtual ~VelocitiesTypeSupportMetaHolder ();
    
    private:
        ::DDS::OpenSplice::DataWriter * create_datawriter ();
    
        ::DDS::OpenSplice::DataReader * create_datareader ();
    
        ::DDS::OpenSplice::DataReaderView * create_view ();
    };
    
    class  VelocitiesTypeSupport : public virtual VelocitiesTypeSupportInterface,
                                                       public ::DDS::OpenSplice::TypeSupport
    {
    public:
        VelocitiesTypeSupport ();
    
        virtual ~VelocitiesTypeSupport ();
    
    private:
        VelocitiesTypeSupport (const VelocitiesTypeSupport &);
    
        void operator= (const VelocitiesTypeSupport &);
    };
    
    typedef VelocitiesTypeSupportInterface_var VelocitiesTypeSupport_var;
    typedef VelocitiesTypeSupportInterface_ptr VelocitiesTypeSupport_ptr;
    
    class  VelocitiesDataWriter_impl : public virtual VelocitiesDataWriter,
                                                           public ::DDS::OpenSplice::FooDataWriter_impl
    {
        friend class DDS::OpenSplice::Publisher;
        friend class VelocitiesTypeSupportMetaHolder;
    
    public:
        virtual ::DDS::InstanceHandle_t register_instance (
            const Velocities & instance_data) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t register_instance_w_timestamp (
            const Velocities & instance_data,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance (
            const Velocities & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t unregister_instance_w_timestamp (
            const Velocities & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write (
            const Velocities & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t write_w_timestamp (
            const Velocities & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose (
            const Velocities & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t dispose_w_timestamp (
            const Velocities & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose (
            const Velocities & instance_data,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t writedispose_w_timestamp (
            const Velocities & instance_data,
            ::DDS::InstanceHandle_t handle,
            const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value (
            Velocities & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance (
            const Velocities & instance_data) THROW_ORB_EXCEPTIONS;
    
    protected:
        VelocitiesDataWriter_impl ();
    
        virtual ~VelocitiesDataWriter_impl ();
    
        virtual DDS::ReturnCode_t init (
                        DDS::OpenSplice::Publisher *publisher,
                        DDS::OpenSplice::DomainParticipant *participant,
                        const DDS::DataWriterQos &qos,
                        DDS::OpenSplice::Topic *a_topic,
                        const char *name,
                        DDS::OpenSplice::cxxCopyIn copyIn,
                        DDS::OpenSplice::cxxCopyOut copyOut);
    
    private:
        VelocitiesDataWriter_impl (const VelocitiesDataWriter_impl &);
    
        void operator= (const VelocitiesDataWriter &);
    };
    
    class  VelocitiesDataReader_impl : public virtual VelocitiesDataReader,
                                                           public ::DDS::OpenSplice::FooDataReader_impl
    {
        friend class DDS::OpenSplice::Subscriber;
        friend class VelocitiesTypeSupportMetaHolder;
        friend class VelocitiesDataReaderView_impl;
    
    public:
        virtual ::DDS::ReturnCode_t read (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_w_condition (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_w_condition (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample (
            Velocities & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample (
            Velocities & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_instance (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_instance (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value (
            Velocities & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance (
            const Velocities & instance) THROW_ORB_EXCEPTIONS;
    
    protected:
        VelocitiesDataReader_impl ();
    
        virtual ~VelocitiesDataReader_impl ();
    
        DDS::ReturnCode_t init (
                DDS::OpenSplice::Subscriber *subscriber,
                const DDS::DataReaderQos &qos,
                DDS::OpenSplice::TopicDescription *a_topic,
                const char *name,
                DDS::OpenSplice::cxxCopyIn copyIn,
                DDS::OpenSplice::cxxCopyOut copyOut);
    
        static void* dataSeqAlloc (
            void * data_values,
            DDS::ULong len);
    
        static void dataSeqLength (
            void * data_values,
            DDS::ULong len);
    
        static void * dataSeqGetBuffer (
            void * data_values,
            DDS::ULong index);
    
        static void dataSeqCopyOut (
            const void * from,
            void * received_data);
        static void copyDataOut(const void *from, void *to);
    
    private:
        VelocitiesDataReader_impl (const VelocitiesDataReader &);
        void operator= (const VelocitiesDataReader &);
    
        static ::DDS::ReturnCode_t check_preconditions (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples);
    };
    
    class  VelocitiesDataReaderView_impl : public virtual VelocitiesDataReaderView,
                                                               public ::DDS::OpenSplice::FooDataReaderView_impl
    {
        friend class DDS::OpenSplice::DataReader;
        friend class VelocitiesTypeSupportMetaHolder;
    
    public:
        virtual ::DDS::ReturnCode_t read (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_w_condition (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_w_condition (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_sample (
            Velocities & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_sample (
            Velocities & received_data,
            ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_instance (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_instance (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::SampleStateMask sample_states,
            ::DDS::ViewStateMask view_states,
            ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t read_next_instance_w_condition (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t take_next_instance_w_condition (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq,
            ::DDS::Long max_samples,
            ::DDS::InstanceHandle_t a_handle,
            ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t return_loan (
            VelocitiesSeq & received_data,
            ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::ReturnCode_t get_key_value (
            Velocities & key_holder,
            ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS;
    
        virtual ::DDS::InstanceHandle_t lookup_instance (
            const Velocities & instance) THROW_ORB_EXCEPTIONS;
    
    protected:
        VelocitiesDataReaderView_impl ();
    
        virtual ~VelocitiesDataReaderView_impl ();
    
        virtual DDS::ReturnCode_t init (
            DDS::OpenSplice::DataReader *reader,
            const char *name,
            const DDS::DataReaderViewQos &qos,
            DDS::OpenSplice::cxxCopyIn copyIn,
            DDS::OpenSplice::cxxCopyOut copyOut);
    
    private:
        VelocitiesDataReaderView_impl (const VelocitiesDataReaderView &);
    
        void operator= (const VelocitiesDataReaderView &);
    };
    
}

#undef OS_API
#endif
