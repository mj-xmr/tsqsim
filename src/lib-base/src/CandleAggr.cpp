#include "CandleAggr.h"
#include "Tick.h"
#include "CandleCalc.h"
#include <Template/VectorViewable.hpp>

#include <STD/VectorCpp.hpp>

CandleAggr::CandleAggr(){}
CandleAggr::~CandleAggr(){}

VecCan CandleAggr::AggregateCandles(const IterCan & vc, unsigned n) const
{
    //VecCan::back_insert_iterator bit;
    VecCanView vcSegment;
    VecCan ret;
    unsigned i = 0;
    for (i = 0; i < vc.size(); ++i)
    {
        const Candle & c = vc.at(i);
        vcSegment.dat.push_back(c);
        if (i % n == 0) // might leave candles
        {
            const Candle & joined = JoinCandles(vcSegment);
            const VecCan & dispersed = ToNCandles(joined, vcSegment);
            std::copy(dispersed.begin(), dispersed.end(), std::back_inserter(ret));
            vcSegment.dat.clear();
        }
    }
    if (not vcSegment.empty()) // any candles left?
    {
        const Candle & joined = JoinCandles(vcSegment);
        const VecCan & dispersed = ToNCandles(joined, vcSegment);
        std::copy(dispersed.begin(), dispersed.end(), std::back_inserter(ret));
        vcSegment.dat.clear();
    }
    return ret;
}

VecCan CandleAggr::ToNCandles(const Candle & c, const IterCan & vcSegment) const
{
    unsigned n = vcSegment.size();
    VecCan ret;
    const float bodyLen = CandleCalc().GetBodyLen(c);
    const float partLen = bodyLen / float(n);
    const float partLenSgn = c.GetDir() == BUY ? partLen : -partLen;
    for (unsigned i = 0; i < n; ++i)
    {
        const float o = c.GetOpen();
        const float no = o + partLenSgn * (i+0);
        const float nc = o + partLenSgn * (i+1);
        //const Candle cn(no, nc, c.GetHigh(), c.GetLow());
        Candle cn;
        cn.UpdateHighLow(vcSegment.at(i).ToTick());
        cn.SetOpen(no);
        cn.SetClose(nc);
        ret.push_back(cn);
    }
    return ret;
}

VecCan CandleAggr::ToNCandles(const Candle & c, unsigned n) const
{
    VecCan ret;
    const float bodyLen = CandleCalc().GetBodyLen(c);
    const float partLen = bodyLen / float(n);
    const float partLenSgn = c.GetDir() == BUY ? partLen : -partLen;
    for (unsigned i = 0; i < n; ++i)
    {
        const float o = c.GetOpen();
        const float no = o + partLenSgn * (i+0);
        const float nc = o + partLenSgn * (i+1);
        const Candle cn(no, nc, c.GetHigh(), c.GetLow());
        ret.push_back(cn);
    }
    return ret;
}

Candle CandleAggr::JoinCandles(const IterCan & vcSegment) const
{
    Candle ret;
    for (const Candle & c : vcSegment)
        ret.UpdateHighLow(c.ToTick());
    ret.SetClose(vcSegment.at(vcSegment.size()-1).ToTick());
    return ret;
}
