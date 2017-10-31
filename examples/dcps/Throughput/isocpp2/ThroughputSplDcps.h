#ifndef THROUGHPUTSPLTYPES_H
#define THROUGHPUTSPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "Throughput_DCPS.hpp"


extern c_metaObject __Throughput_ThroughputModule__load (c_base base);

extern const char *ThroughputModule_DataType_metaDescriptor[];
extern const int ThroughputModule_DataType_metaDescriptorArrLength;
extern const int ThroughputModule_DataType_metaDescriptorLength;
extern c_metaObject __ThroughputModule_DataType__load (c_base base);
struct _ThroughputModule_DataType ;
extern  v_copyin_result __ThroughputModule_DataType__copyIn(c_base base, const class ThroughputModule::DataType *from, struct _ThroughputModule_DataType *to);
extern  void __ThroughputModule_DataType__copyOut(const void *_from, void *_to);
struct _ThroughputModule_DataType {
    c_ulonglong count;
    c_sequence payload;
};

#undef OS_API
#endif
