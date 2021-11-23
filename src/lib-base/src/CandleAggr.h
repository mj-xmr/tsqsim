#ifndef CANDLEAGGR_H
#define CANDLEAGGR_H

#include "Candle.h"
#include "typesVec.h"

class CandleAggr
{
    public:
        CandleAggr();
        virtual ~CandleAggr();

        VecCan AggregateCandles(const IterCan & vc, unsigned n) const;
        VecCan ToNCandles(const Candle & c, unsigned n) const;
        VecCan ToNCandles(const Candle & c, const IterCan & vcSegment) const;
        Candle JoinCandles(const IterCan & vcSegment) const;

    protected:
    private:

        //Candle m_can;
};

#endif // CANDLEAGGR_H
