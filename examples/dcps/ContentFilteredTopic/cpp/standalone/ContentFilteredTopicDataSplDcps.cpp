#include "ContentFilteredTopicDataSplDcps.h"
#include "ccpp_ContentFilteredTopicData.h"

#include <v_copyIn.h>
#include <v_topic.h>
#include <os_stdlib.h>
#include <string.h>
#include <os_report.h>

v_copyin_result
__StockMarket_Stock__copyIn(
    c_base base,
    const struct ::StockMarket::Stock *from,
    struct _StockMarket_Stock *to)
{
    v_copyin_result result = V_COPYIN_RESULT_OK;
    (void) base;

#ifdef OSPL_BOUNDS_CHECK
    if(from->ticker){
        to->ticker = c_stringNew_s(base, from->ticker);
        if(to->ticker == NULL) {
            result = V_COPYIN_RESULT_OUT_OF_MEMORY;
        }
    } else {
        OS_REPORT (OS_ERROR, "copyIn", 0,"Member 'StockMarket::Stock.ticker' of type 'c_string' is NULL.");
        result = V_COPYIN_RESULT_INVALID;
    }
#else
    to->ticker = c_stringNew_s(base, from->ticker);
    if(to->ticker == NULL) {
        result = V_COPYIN_RESULT_OUT_OF_MEMORY;
    }
#endif
    to->price = (c_float)from->price;
    return result;
}

void
__StockMarket_Stock__copyOut(
    const void *_from,
    void *_to)
{
    const struct _StockMarket_Stock *from = (const struct _StockMarket_Stock *)_from;
    struct ::StockMarket::Stock *to = (struct ::StockMarket::Stock *)_to;
    to->ticker = DDS::string_dup(from->ticker ? from->ticker : "");
    to->price = (::DDS::Float)from->price;
}

