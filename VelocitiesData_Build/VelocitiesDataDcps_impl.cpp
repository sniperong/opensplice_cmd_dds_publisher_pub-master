#include "VelocitiesDataDcps_impl.h"
#include "VelocitiesDataSplDcps.h"
//

extern v_copyin_result
__VelocitiesData_Velocities__copyIn (
    c_base base,
    const struct VelocitiesData::Velocities *from,
    struct _VelocitiesData_Velocities *to);

extern void
__VelocitiesData_Velocities__copyOut (
    const void *_from,
    void *_to);

// DDS VelocitiesData::Velocities TypeSupportMetaHolder Object Body
VelocitiesData::VelocitiesTypeSupportMetaHolder::VelocitiesTypeSupportMetaHolder () :
        DDS::OpenSplice::TypeSupportMetaHolder ("VelocitiesData::Velocities", "", "")
{
    copyIn = (DDS::OpenSplice::cxxCopyIn) __VelocitiesData_Velocities__copyIn;
    copyOut = (DDS::OpenSplice::cxxCopyOut) __VelocitiesData_Velocities__copyOut;
    metaDescriptorArrLength = 3;
    metaDescriptorLength = 319;
    const char *tmp[] = {"<MetaData version=\"1.0.0\"><Module name=\"VelocitiesData\"><Struct name=\"Velocities\"><Member name=\"robot_id\">",
"<Long/></Member><Member name=\"linear_velocity_x\"><Double/></Member><Member name=\"linear_velocity_y\">",
"<Double/></Member><Member name=\"angular_velocity_z\"><Double/></Member></Struct></Module></MetaData>"};
    metaDescriptor = new const char*[metaDescriptorArrLength];
    memcpy(metaDescriptor, tmp, sizeof(tmp));
}

VelocitiesData::VelocitiesTypeSupportMetaHolder::~VelocitiesTypeSupportMetaHolder ()
{
    // Rely on parent destructor.
}

::DDS::OpenSplice::DataWriter *
VelocitiesData::VelocitiesTypeSupportMetaHolder::create_datawriter ()
{
    return new VelocitiesData::VelocitiesDataWriter_impl();
}

::DDS::OpenSplice::DataReader *
VelocitiesData::VelocitiesTypeSupportMetaHolder::create_datareader ()
{
    return new VelocitiesData::VelocitiesDataReader_impl();
}

::DDS::OpenSplice::DataReaderView *
VelocitiesData::VelocitiesTypeSupportMetaHolder::create_view ()
{
    return new VelocitiesData::VelocitiesDataReaderView_impl();
}

// DDS VelocitiesData::Velocities TypeSupport Object Body
VelocitiesData::VelocitiesTypeSupport::VelocitiesTypeSupport () :
        DDS::OpenSplice::TypeSupport()
{
    tsMetaHolder = new VelocitiesData::VelocitiesTypeSupportMetaHolder();
}

VelocitiesData::VelocitiesTypeSupport::~VelocitiesTypeSupport ()
{
    DDS::release(tsMetaHolder);
}

// DDS VelocitiesData::Velocities DataWriter_impl Object Body
VelocitiesData::VelocitiesDataWriter_impl::VelocitiesDataWriter_impl ()
{
    // Parent constructor takes care of everything.
}

VelocitiesData::VelocitiesDataWriter_impl::~VelocitiesDataWriter_impl ()
{
    // Parent destructor takes care of everything.
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataWriter_impl::init (
        DDS::OpenSplice::Publisher *publisher,
        DDS::OpenSplice::DomainParticipant *participant,
        const DDS::DataWriterQos &qos,
        DDS::OpenSplice::Topic *a_topic,
        const char *name,
        DDS::OpenSplice::cxxCopyIn copyIn,
        DDS::OpenSplice::cxxCopyOut copyOut)
{
    return DDS::OpenSplice::FooDataWriter_impl::nlReq_init(publisher, participant, qos, a_topic, name, copyIn, copyOut);
}

::DDS::InstanceHandle_t
VelocitiesData::VelocitiesDataWriter_impl::register_instance (
    const VelocitiesData::Velocities & instance_data) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::register_instance(&instance_data);
}

::DDS::InstanceHandle_t
VelocitiesData::VelocitiesDataWriter_impl::register_instance_w_timestamp (
    const Velocities & instance_data,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::register_instance_w_timestamp(&instance_data, source_timestamp);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataWriter_impl::unregister_instance (
    const VelocitiesData::Velocities & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::unregister_instance(&instance_data, handle);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataWriter_impl::unregister_instance_w_timestamp (
    const Velocities & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::unregister_instance_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataWriter_impl::write (
    const VelocitiesData::Velocities & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::write(&instance_data, handle);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataWriter_impl::write_w_timestamp (
    const Velocities & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::write_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataWriter_impl::dispose (
    const VelocitiesData::Velocities & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::dispose(&instance_data, handle);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataWriter_impl::dispose_w_timestamp (
    const Velocities & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::dispose_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataWriter_impl::writedispose (
    const VelocitiesData::Velocities & instance_data,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::writedispose(&instance_data, handle);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataWriter_impl::writedispose_w_timestamp (
    const Velocities & instance_data,
    ::DDS::InstanceHandle_t handle,
    const ::DDS::Time_t & source_timestamp) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::writedispose_w_timestamp(&instance_data, handle, source_timestamp);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataWriter_impl::get_key_value (
    Velocities & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
VelocitiesData::VelocitiesDataWriter_impl::lookup_instance (
    const VelocitiesData::Velocities & instance_data) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataWriter_impl::lookup_instance(&instance_data);
}

// DDS VelocitiesData::Velocities DataReader_impl Object Body
VelocitiesData::VelocitiesDataReader_impl::VelocitiesDataReader_impl ()
{
    // Parent constructor takes care of everything.
}

VelocitiesData::VelocitiesDataReader_impl::~VelocitiesDataReader_impl ()
{
    // Parent destructor takes care of everything.
}

DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::init (
    DDS::OpenSplice::Subscriber *subscriber,
    const DDS::DataReaderQos &qos,
    DDS::OpenSplice::TopicDescription *a_topic,
    const char *name,
    DDS::OpenSplice::cxxCopyIn copyIn,
    DDS::OpenSplice::cxxCopyOut copyOut)
{
    return DDS::OpenSplice::FooDataReader_impl::nlReq_init(
            subscriber, qos, a_topic, name, copyIn, copyOut,
            this->dataSeqAlloc, this->dataSeqLength, this->dataSeqGetBuffer, this->dataSeqCopyOut);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::read (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status = DDS::RETCODE_OK;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::take (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status = DDS::RETCODE_OK;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::read_w_condition (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status = DDS::RETCODE_OK;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::take_w_condition (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status = DDS::RETCODE_OK;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::read_next_sample (
    VelocitiesData::Velocities & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReader_impl::read_next_sample(&received_data, sample_info);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::take_next_sample (
    VelocitiesData::Velocities & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReader_impl::take_next_sample(&received_data, sample_info);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::read_instance (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::take_instance (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::read_next_instance (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::take_next_instance (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::read_next_instance_w_condition (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::take_next_instance_w_condition (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReader_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::return_loan (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t result = ::DDS::RETCODE_OK;

    result = this->write_lock ();
    if (result == DDS::RETCODE_OK) {
        if ( received_data.length() > 0 ) {
            if (received_data.length() == info_seq.length() &&
                received_data.release() == info_seq.release() ) {
                if (!received_data.release()) {
                    result = DDS::OpenSplice::FooDataReader_impl::wlReq_return_loan( received_data.get_buffer(),
                                                                                     info_seq.get_buffer() );
                    if ( result == ::DDS::RETCODE_OK ) {
                        if ( !received_data.release() ) {
                            VelocitiesData::VelocitiesSeq::freebuf( received_data.get_buffer(false) );
                            received_data.replace(0, 0, NULL, false);
                            ::DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                            info_seq.replace(0, 0, NULL, false);
                        }
                    }
                }
            } else {
                result = ::DDS::RETCODE_PRECONDITION_NOT_MET;
            }
        }
        this->unlock();
    }
    return result;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::get_key_value (
    VelocitiesData::Velocities & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReader_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
VelocitiesData::VelocitiesDataReader_impl::lookup_instance (
    const VelocitiesData::Velocities & instance) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReader_impl::lookup_instance(&instance);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReader_impl::check_preconditions (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples)
{
    if ((max_samples < 0) && (max_samples != DDS::LENGTH_UNLIMITED)) {
        return DDS::RETCODE_BAD_PARAMETER;
    }

    /* Rule 1 : The values of len, max_len, and owns
     * for the two collections must be identical.
     */
    if ((received_data.length()  != info_seq.length())  ||
        (received_data.maximum() != info_seq.maximum()) ||
        (received_data.release() != info_seq.release()))
    {
        return DDS::RETCODE_PRECONDITION_NOT_MET;
    }

    /* Rule 4: If the input max_len>0 and the input owns==FALSE,
     * then the read operation will fail.
     */
    if ((info_seq.maximum() > 0) &&
        (info_seq.release() == false))
    {
        return DDS::RETCODE_PRECONDITION_NOT_MET;
    }

    /* Rule 5: If input max_len>0 and the input owns==TRUE,
     * then the read operation will...
     */
    if (info_seq.maximum() > 0) { /* owns is true, because of rule 4. */
        /* Rule 5a: If max_samples = LENGTH_UNLIMITED,
         * then at most max_len values will be copied.
         * Rule 5b: If max_samples <= max_len,
         * then at most max_samples values will be copied.
         */
        /* Rule 5c: If max_samples > max_len,
         * then the read operation will fail.
         */
        if ((max_samples != DDS::LENGTH_UNLIMITED) &&
            ((DDS::ULong)max_samples > info_seq.maximum())) {
            return DDS::RETCODE_PRECONDITION_NOT_MET;
        }
    }

    if ((max_samples == 0) ||
        ((info_seq.maximum() == 0) && (info_seq.release()))) {
        return DDS::RETCODE_NO_DATA;
    }

    return DDS::RETCODE_OK;
}

void *
VelocitiesData::VelocitiesDataReader_impl::dataSeqAlloc (
    void * received_data,
    DDS::ULong len)
{
    VelocitiesData::VelocitiesSeq *data_seq = reinterpret_cast<VelocitiesData::VelocitiesSeq *>(received_data);
    data_seq->replace(len, len, data_seq->allocbuf(len), false);
    return data_seq->get_buffer();
}

void *
VelocitiesData::VelocitiesDataReader_impl::dataSeqGetBuffer (
    void * received_data,
    DDS::ULong index)
{
	VelocitiesData::VelocitiesSeq *data_seq = reinterpret_cast<VelocitiesData::VelocitiesSeq *>(received_data);
	return &((*data_seq)[index]);
}

void
VelocitiesData::VelocitiesDataReader_impl::dataSeqLength (
    void * received_data,
    DDS::ULong len)
{
    VelocitiesData::VelocitiesSeq *data_seq = reinterpret_cast<VelocitiesData::VelocitiesSeq *>(received_data);
    data_seq->length(len);
}

void
VelocitiesData::VelocitiesDataReader_impl::dataSeqCopyOut (
    const void * from,
    void * to)
{
    VelocitiesData::Velocities *data = reinterpret_cast<VelocitiesData::Velocities *>(to);
    __VelocitiesData_Velocities__copyOut(from, data);
}

void
VelocitiesData::VelocitiesDataReader_impl::copyDataOut (
    const void * from,
    void * to)
{
    VelocitiesData::Velocities *data = reinterpret_cast<VelocitiesData::Velocities *>(to);
    __VelocitiesData_Velocities__copyOut(from, data);
}


// DDS VelocitiesData::Velocities DataReaderView_impl Object Body
VelocitiesData::VelocitiesDataReaderView_impl::VelocitiesDataReaderView_impl ()
{
    // Parent constructor takes care of everything.
}

VelocitiesData::VelocitiesDataReaderView_impl::~VelocitiesDataReaderView_impl ()
{
    // Parent destructor takes care of everything.
}

DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::init (
    DDS::OpenSplice::DataReader *reader,
    const char *name,
    const DDS::DataReaderViewQos &qos,
    DDS::OpenSplice::cxxCopyIn copyIn,
    DDS::OpenSplice::cxxCopyOut copyOut)
{
    return DDS::OpenSplice::FooDataReaderView_impl::nlReq_init(
            reader, name, qos, copyIn, copyOut, VelocitiesData::VelocitiesDataReader_impl::dataSeqAlloc,
            VelocitiesData::VelocitiesDataReader_impl::dataSeqLength);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::read (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = VelocitiesData::VelocitiesDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::read(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::take (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = VelocitiesData::VelocitiesDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::take(&received_data, info_seq, max_samples, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::read_w_condition (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = VelocitiesData::VelocitiesDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::read_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::take_w_condition (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = VelocitiesData::VelocitiesDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::take_w_condition(&received_data, info_seq, max_samples, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::read_next_sample (
    VelocitiesData::Velocities & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReaderView_impl::read_next_sample(&received_data, sample_info);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::take_next_sample (
    VelocitiesData::Velocities & received_data,
    ::DDS::SampleInfo & sample_info) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReaderView_impl::take_next_sample(&received_data, sample_info);
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::read_instance (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = VelocitiesData::VelocitiesDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::read_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::take_instance (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = VelocitiesData::VelocitiesDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::take_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::read_next_instance (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = VelocitiesData::VelocitiesDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::read_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::take_next_instance (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::SampleStateMask sample_states,
    ::DDS::ViewStateMask view_states,
    ::DDS::InstanceStateMask instance_states) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = VelocitiesData::VelocitiesDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::take_next_instance(&received_data, info_seq, max_samples, a_handle, sample_states, view_states, instance_states);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::read_next_instance_w_condition (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = VelocitiesData::VelocitiesDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::read_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::take_next_instance_w_condition (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq,
    ::DDS::Long max_samples,
    ::DDS::InstanceHandle_t a_handle,
    ::DDS::ReadCondition_ptr a_condition) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t status;

    status = VelocitiesData::VelocitiesDataReader_impl::check_preconditions(received_data, info_seq, max_samples);
    if ( status == ::DDS::RETCODE_OK ) {
        status = DDS::OpenSplice::FooDataReaderView_impl::take_next_instance_w_condition(&received_data, info_seq, max_samples, a_handle, a_condition);
    }
    return status;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::return_loan (
    VelocitiesData::VelocitiesSeq & received_data,
    ::DDS::SampleInfoSeq & info_seq) THROW_ORB_EXCEPTIONS
{
    ::DDS::ReturnCode_t result = ::DDS::RETCODE_OK;

    result = this->write_lock ();
    if (result == DDS::RETCODE_OK) {
        if ( received_data.length() > 0 ) {
            if (received_data.length() == info_seq.length() &&
                received_data.release() == info_seq.release() ) {
                if (!received_data.release()) {
                    result = DDS::OpenSplice::FooDataReaderView_impl::wlReq_return_loan( received_data.get_buffer(),
                                                           info_seq.get_buffer() );

                    if ( result == ::DDS::RETCODE_OK ) {
                        if ( !received_data.release() ) {
                            VelocitiesData::VelocitiesSeq::freebuf( received_data.get_buffer(false) );
                            received_data.replace(0, 0, NULL, false);
                            ::DDS::SampleInfoSeq::freebuf( info_seq.get_buffer(false) );
                            info_seq.replace(0, 0, NULL, false);
                        }
                    } else if ( result == ::DDS::RETCODE_NO_DATA ) {
                        if ( received_data.release() ) {
                            result = ::DDS::RETCODE_OK;
                        } else {
                            result = ::DDS::RETCODE_PRECONDITION_NOT_MET;
                        }
                    }
                }
            } else {
                result = ::DDS::RETCODE_PRECONDITION_NOT_MET;
            }
        }
        this->unlock();
    }
    return result;
}

::DDS::ReturnCode_t
VelocitiesData::VelocitiesDataReaderView_impl::get_key_value (
    VelocitiesData::Velocities & key_holder,
    ::DDS::InstanceHandle_t handle) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReaderView_impl::get_key_value(&key_holder, handle);
}

::DDS::InstanceHandle_t
VelocitiesData::VelocitiesDataReaderView_impl::lookup_instance (
    const VelocitiesData::Velocities & instance) THROW_ORB_EXCEPTIONS
{
    return DDS::OpenSplice::FooDataReaderView_impl::lookup_instance(&instance);
}
