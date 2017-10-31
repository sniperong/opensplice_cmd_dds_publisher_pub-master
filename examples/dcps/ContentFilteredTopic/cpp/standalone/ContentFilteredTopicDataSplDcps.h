#ifndef CONTENTFILTEREDTOPICDATASPLTYPES_H
#define CONTENTFILTEREDTOPICDATASPLTYPES_H

#include <c_base.h>
#include <c_misc.h>
#include <c_sync.h>
#include <c_collection.h>
#include <c_field.h>
#include <v_copyIn.h>

#include "ccpp_ContentFilteredTopicData.h"


extern c_metaObject __ContentFilteredTopicData_StockMarket__load (c_base base);

extern const char *StockMarket_Stock_metaDescriptor[];
extern const int StockMarket_Stock_metaDescriptorArrLength;
extern const int StockMarket_Stock_metaDescriptorLength;
extern c_metaObject __StockMarket_Stock__load (c_base base);
struct _StockMarket_Stock ;
extern  v_copyin_result __StockMarket_Stock__copyIn(c_base base, const struct StockMarket::Stock *from, struct _StockMarket_Stock *to);
extern  void __StockMarket_Stock__copyOut(const void *_from, void *_to);
struct _StockMarket_Stock {
    c_string ticker;
    c_float price;
};

#undef OS_API
#endif
