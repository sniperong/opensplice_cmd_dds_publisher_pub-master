#ifndef ISOCPP2_THROUGHPUT_H
#define ISOCPP2_THROUGHPUT_H

#include "dds/dds.hpp"

#include "Throughput.h"
#include "ThroughputSplDcps.h"

#include "org/opensplice/topic/TopicTraits.hpp"
#include "org/opensplice/topic/DataRepresentation.hpp"

namespace org { namespace opensplice { namespace topic {
template <>
class TopicTraits<ThroughputModule::DataType>
{
public:
    static ::org::opensplice::topic::DataRepresentationId_t getDataRepresentationId()
    {
        return ::org::opensplice::topic::OSPL_REPRESENTATION;
    }

    static ::std::vector<os_uchar> getMetaData()
    {
        return ::std::vector<os_uchar>();
    }

    static ::std::vector<os_uchar> getTypeHash()
    {
        return ::std::vector<os_uchar>();
    }

    static ::std::vector<os_uchar> getExtentions()
    {
        return ::std::vector<os_uchar>();
    }

    static const char *getKeyList()
    {
        return "";
    }

    static const char *getTypeName()
    {
        return "ThroughputModule::DataType";
    }

    static std::string getDescriptor()
    {
        const char *elements[] = {
            "<MetaData version=\"1.0.0\"><Module name=\"ThroughputModule\"><Struct name=\"DataType\"><Member name=\"count\">",
"<ULongLong/></Member><Member name=\"payload\"><Sequence><Octet/></Sequence></Member></Struct></Module>",
"</MetaData>"
        };
        std::string descriptor;
        descriptor.reserve(224);
        for (int i = 0; i < 3; i++) {
            descriptor.append(elements[i]);
        }

        return descriptor;
    }

    static copyInFunction getCopyIn()
    {
        return (copyInFunction) __ThroughputModule_DataType__copyIn;
    }

    static copyOutFunction getCopyOut()
    {
        return (copyOutFunction) __ThroughputModule_DataType__copyOut;
    }
};
}}}

namespace dds { namespace topic {
template <>
struct topic_type_name<ThroughputModule::DataType>
{
    static std::string value()
    {
        return org::opensplice::topic::TopicTraits<ThroughputModule::DataType>::getTypeName();
    }
};
}}

REGISTER_TOPIC_TYPE(ThroughputModule::DataType)

#endif /* ISOCPP2_THROUGHPUT_H */
