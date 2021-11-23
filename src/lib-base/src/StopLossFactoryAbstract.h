#ifndef STOPLOSSFACTORYABST_H
#define STOPLOSSFACTORYABST_H

#include <Template/CorradePointerFwd.h>

#include "IStopLoss.h"

enum class StopLossType
{
	SL_ADAPT_NOW,
        SL_ADAPT_SMOOTH,
        SL_CANDLE,
        SL_CONSERV,
        SL_UNIV_OSCI,
        SL_ZZ_MA_CROSS,
        SL_FRACTAL_FAKE,
        SL_FRACTAL_ADAPT,
        SL_FRACTAL_OPEN,
        SL_SR,
        SL_SR2,
        SL_SIMPLE_MA,
        SL_MULTI_MA,
        SL_SR_GROUP,
        SL_TRENDLINE,
        SL_REGRESS,
        SL_FIXED_PERCENT,
        SL_MACD,
        SL_LONG_WICK,
        SL_AGGR,
        SL_AGGR_MULTI_OPEN
};

class IPeriod;
class StopLossFactoryAbstract
{
	public:
    virtual Corrade::Containers::Pointer<IStopLoss> Create(const IPeriod & period, const StopLossType & type) const = 0;
};


#endif // STOPLOSSFACTORYABST_H
