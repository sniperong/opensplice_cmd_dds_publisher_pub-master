#ifndef _THROUGHPUT_H_
#define _THROUGHPUT_H_

#include <dds/core/ddscore.hpp>

namespace ThroughputModule
{
    class DataType OSPL_DDS_FINAL
    {
    public:
        typedef std::vector<uint8_t>  _payload_seq;

        uint64_t count_;
        std::vector<uint8_t>  payload_;

    public:
        DataType() :
                count_(0) {}

        explicit DataType(
            uint64_t count,
            const std::vector<uint8_t> & payload) : 
                count_(count),
                payload_(payload) {}

        DataType(const DataType &_other) : 
                count_(_other.count_),
                payload_(_other.payload_) {}

#ifdef OSPL_DDS_CXX11
        DataType(DataType &&_other) : 
                count_(::std::move(_other.count_)),
                payload_(::std::move(_other.payload_)) {}

        DataType& operator=(DataType &&_other)
        {
            if (this != &_other) {
                count_ = ::std::move(_other.count_);
                payload_ = ::std::move(_other.payload_);
            }
            return *this;
        }
#endif

        DataType& operator=(const DataType &_other)
        {
            if (this != &_other) {
                count_ = _other.count_;
                payload_ = _other.payload_;
            }
            return *this;
        }

        bool operator==(const DataType& _other) const
        {
            return count_ == _other.count_ &&
                payload_ == _other.payload_;
        }

        bool operator!=(const DataType& _other) const
        {
            return !(*this == _other);
        }

        uint64_t count() const { return this->count_; }
        uint64_t& count() { return this->count_; }
        void count(uint64_t _val_) { this->count_ = _val_; }
        const std::vector<uint8_t> & payload() const { return this->payload_; }
        std::vector<uint8_t> & payload() { return this->payload_; }
        void payload(const std::vector<uint8_t> & _val_) { this->payload_ = _val_; }
#ifdef OSPL_DDS_CXX11
        void payload(std::vector<uint8_t> && _val_) { this->payload_ = _val_; }
#endif
    };

}

#endif /* _THROUGHPUT_H_ */
