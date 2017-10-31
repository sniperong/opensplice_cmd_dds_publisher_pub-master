#include "Boilerplate.h"
#include "EnvironmentalBoilerplate.h"
#include "EnvironmentalSupport.h"

EnvironmentalMsg::Publisher::Publisher(DDSBoilerplate * boiler_object, char const * user_topic)
{
    user_topic_ = user_topic;
    boiler_object_ = boiler_object;
    participant_ = boiler_object_->get_participant_obj();
    init_publisher();
}

int EnvironmentalMsg::Publisher::init_publisher()
{
    DDSPublisher *publisher;
    DDSTopic *topic = NULL;
    DDSDataWriter *writer = NULL;
    Environmental_writer_ = NULL;
    instance = NULL;
    instance_handle_ = DDS_HANDLE_NIL;
    const char *type_name = NULL;
    
    /* To customize publisher QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    publisher = participant_->create_publisher(
        DDS_PUBLISHER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (publisher == NULL) {
        printf("create_publisher error\n");
        boiler_object_->node_shutdown();
        return -1;
    }
    
    /* Register type before creating topic */
    type_name = EnvironmentalTypeSupport::get_type_name();
    retcode_ = EnvironmentalTypeSupport::register_type(
        participant_, type_name);
    if (retcode_ != DDS_RETCODE_OK) {
        printf("register_type error %d\n", retcode_);
        boiler_object_->node_shutdown();
        return -1;
    }

/* To customize topic QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    topic = participant_->create_topic(
        user_topic_,
        type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);    // y.publish();

    if (topic == NULL) {
        printf("create_topic error\n");
        boiler_object_->node_shutdown();
        return -1;
    }
    
    /* To customize data writer QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    writer = publisher->create_datawriter(
        topic, DDS_DATAWRITER_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (writer == NULL) {
        printf("create_datawriter error\n");
        boiler_object_->node_shutdown();
        return -1;
    }

    Environmental_writer_ = EnvironmentalDataWriter::narrow(writer);
    if (Environmental_writer_ == NULL) {
        printf("DataWriter narrow error\n");
        boiler_object_->node_shutdown();
        return -1;
    }

    /* Create data sample for writing */
    instance = EnvironmentalTypeSupport::create_data();
    if (instance == NULL) {
        printf("EnvironmentalTypeSupport::create_data error\n");
        boiler_object_->node_shutdown();
        return -1;
    }
}

void EnvironmentalMsg::Publisher::publish(){
    retcode_ = Environmental_writer_->write(*instance, instance_handle_);

    if (retcode_ != DDS_RETCODE_OK) {
        printf("write error %d\n", retcode_);
    }
}

int EnvironmentalMsg::Publisher::kill()
{
    retcode_ = EnvironmentalTypeSupport::delete_data(instance);
    if (retcode_ != DDS_RETCODE_OK) {
        printf("EnvironmentalTypeSupport::delete_data error %d\n", retcode_);
    }

    /* Delete all entities */
    return boiler_object_->node_shutdown();
}

EnvironmentalMsg::Subscriber::Subscriber(DDSBoilerplate * boiler_object, char const * user_topic)
{
    user_topic_ = user_topic;
    boiler_object_ = boiler_object;
    participant_ = boiler_object_->get_participant_obj();
    init_subscriber();
}

void EnvironmentalMsg::EnvironmentalListener::on_data_available(DDSDataReader* reader) 
{
    EnvironmentalDataReader *Environmental_reader = NULL;
    EnvironmentalSeq data_seq_;
    DDS_SampleInfoSeq info_seq_;    
    DDS_ReturnCode_t retcode;
    int i;

    Environmental_reader = EnvironmentalDataReader::narrow(reader);
    if (Environmental_reader == NULL) {
        printf("DataReader narrow error\n");
        return;
    }

    retcode = Environmental_reader->take(
        data_seq_, info_seq_, DDS_LENGTH_UNLIMITED,
        DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);

    if (retcode == DDS_RETCODE_NO_DATA) {
        return;
    } else if (retcode != DDS_RETCODE_OK) {
        printf("take error %d\n", retcode);
        return;
    }

    this->info_seq = info_seq_;
    this->data_seq = data_seq_;

    // for (i = 0; i < data_seq_.length(); ++i) {
    //     if (info_seq_[i].valid_data) {
    //         std::cout << info_seq_[i].valid_data << std::endl;
    //         //printf("Received data\n");
    //         //EnvironmentalTypeSupport::print_data(&data_seq[i]);
    //     }
    // }

    retcode = Environmental_reader->return_loan(data_seq_, info_seq_);
    if (retcode != DDS_RETCODE_OK) {
        printf("return loan error %d\n", retcode);
    }
}

int EnvironmentalMsg::Subscriber::init_subscriber()
{
    DDSSubscriber *subscriber;
    DDSTopic *topic = NULL;
    DDSDataReader *reader = NULL;
    const char *type_name = NULL;

    /* To customize publisher QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    subscriber = participant_->create_subscriber(
        DDS_SUBSCRIBER_QOS_DEFAULT, NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (subscriber == NULL) {
        printf("create_subscriber error\n");
        boiler_object_->node_shutdown();
        return -1;
    }
    
    /* Register type before creating topic */
    type_name = EnvironmentalTypeSupport::get_type_name();
    retcode_ = EnvironmentalTypeSupport::register_type(
        participant_, type_name);
    if (retcode_ != DDS_RETCODE_OK) {
        printf("register_type error %d\n", retcode_);
        boiler_object_->node_shutdown();
        return -1;
    }

/* To customize topic QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    topic = participant_->create_topic(
        user_topic_,
        type_name, DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);    
    if (topic == NULL) {
        printf("create_topic error\n");
        boiler_object_->node_shutdown();
        return -1;
    }

    /* Create a data reader listener */
    reader_listener_ = new EnvironmentalListener();
        /* To customize data writer QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    reader = subscriber->create_datareader(
        topic, DDS_DATAREADER_QOS_DEFAULT, reader_listener_ /* listener */,
        DDS_STATUS_MASK_ALL);
    if (reader == NULL) {
        printf("create_datareader error\n");
        boiler_object_->node_shutdown();
        delete reader_listener_;
        return -1;
    }
}

EnvironmentalSeq EnvironmentalMsg::Subscriber::get_data_seq()
{
    return reader_listener_->data_seq;
}

DDS_SampleInfoSeq EnvironmentalMsg::Subscriber::get_info_seq()
{
    return reader_listener_->info_seq;
}

bool EnvironmentalMsg::Subscriber::is_read()
{
    if(reader_listener_->info_seq.length()==0) //this condition fixes a bug with not receiving the first subscribed data.
        return true;
    for (int i = 0; i <reader_listener_->info_seq.length(); i++){
        if(reader_listener_->info_seq[i].sample_state == DDS_READ_SAMPLE_STATE){
            return true;
        }
        reader_listener_->info_seq[i].sample_state = DDS_READ_SAMPLE_STATE;
    }
    return false;
}

int EnvironmentalMsg::Subscriber::kill()
{
    int status = boiler_object_->node_shutdown();
    delete reader_listener_;

    return status;
}