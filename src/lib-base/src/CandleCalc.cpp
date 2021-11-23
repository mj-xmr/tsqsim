#include "CandleCalc.h"
#include "Candle.h"
#include "State.h"
#include "IBufferCandles.h"

#include <Template/AlgoSTDThin.hpp>
#include <Math/GeneralMath.hpp>
#include <Math/MaxMinFind.hpp>
#include <Math/GeneralMath.hpp>

using namespace EnjoLib;

CandleCalc::CandleCalc()
{}

CandleCalc::~CandleCalc(){}


float CandleCalc::GetMidPrice(const Candle & c) const
{
    float mid = (c.GetHigh()+c.GetLow()) / 2.0;
    return mid;
}

float CandleCalc::GetMidBody(const Candle & c) const
{
    float mid = (c.GetOpen()+c.GetClose()) / 2.0;
    return mid;
}

float CandleCalc::GetLen(const Candle & c) const
{
    float len = c.GetHigh() - c.GetLow();
    return len;
}

float CandleCalc::GetBodyLen(const Candle & c) const
{
    float len = EnjoLib::GeneralMath().Fabs(c.GetOpen() - c.GetClose());
    return len;
}

CandleWick CandleCalc::CalcWick(const Candle & c, Direction bullish, float extMul) const
{
    if (extMul <= 0)
    {
        //float extMul = 1.0;
        extMul = 0.5;
        //float extMul = 0;
    }

    float wickBase;
    float wickExtreme;
    if (bullish)
    {
        wickExtreme = c.GetLow();
        wickBase = c.GetBodyMin();
    }
    else
    {
        wickExtreme = c.GetHigh();
        wickBase = c.GetBodyMax();
    }
    /*
    const Abstracts & abstr = GetAbstracts();

    if (st.bullish)
    {
        wickExtreme = abstr.AbstractGetLow(st.i);
        wickBase = AlgoSTDThin().Min(abstr.AbstractGetOpen(st.i), abstr.AbstractGetClose(st.i));
    }
    else
    {
        wickExtreme = abstr.AbstractGetHigh(st.i);
        wickBase = AlgoSTDThin().Max(abstr.AbstractGetOpen(st.i), abstr.AbstractGetClose(st.i));
    }
    */
    float diff = wickExtreme - wickBase; // Negative for bullish
    float wickExt = wickExtreme + diff * extMul;
    CandleWick ret;
    ret.wickBase = wickBase;
    ret.wickExtreme = wickExtreme;
    ret.wickExtension = wickExt;
    ret.wickLen = EnjoLib::GeneralMath().Fabs(wickBase - wickExtreme);

    return ret;
}

PairInt CandleCalc::GetMinMaxSlow(const State & past, const State & present, const IBufferCandles & bufCan) const
{
    EnjoLib::MaxMinFind<float> mmf;
    for (State stInSeries = present; stInSeries.i <= past.i && stInSeries.i < bufCan.Len(); ++stInSeries)
    {
        int i = stInSeries.i;
        const Candle & c = bufCan[i];

        mmf.UpdateMax(c.GetHigh(), i);
        mmf.UpdateMin(c.GetLow(), i);
    }
    return PairInt(mmf.GetMinIdx(), mmf.GetMaxIdx());
}

float CandleCalc::GetPriceChange(const Candle & cCurr, const Candle & cPrev) const
{
    return EnjoLib::GeneralMath().RelativeChange(cCurr.GetClose(), cPrev.GetClose());
}

bool CandleCalc::IsInCandle(const Candle & c, float level) const
{
    return (c.GetLow() <= level && level <= c.GetHigh());
}

Candle CandleCalc::GetRangeSlow(const State & past, const State & present, const IBufferCandles & bufCan) const
{
    PairInt minMax = GetMinMaxSlow(past, present, bufCan);
    float cmin = bufCan[minMax.one].GetLow();
    float cmax = bufCan[minMax.two].GetHigh();
    const Candle range(cmax, cmin, cmax, cmin);
    return range;
}

Candle CandleCalc::GetRangeFast(const State & past, const State & present, const IBufferCandles & bufCan) const
{
    const Candle & c1 = bufCan[past.i];
    const Candle & c2 = bufCan[present.i];

    float cmin = AlgoSTDThin().Min(c1.GetLow(), c2.GetLow());
    float cmax = AlgoSTDThin().Max(c1.GetHigh(), c2.GetHigh());

    const Candle range(cmax, cmin, cmax, cmin);
    return range;
}

bool CandleCalc::IsAfterMidnight(const Candle & cOne, const Candle & cTwo) const
{
    Candle cCurr = cOne;
    Candle cPrev = cTwo;

    if (cCurr.GetDate() < cPrev.GetDate())
        AlgoSTDThin().Swap(cCurr, cPrev);

    if (cCurr.GetHour() > cPrev.GetHour())
    {
        return false;
    }
    if (cCurr.GetHour() < cPrev.GetHour())
    {
        return true;
    }
    if (cCurr.GetHour() == cPrev.GetHour())
    {
       // Daily
       if (cCurr.GetDay() > cPrev.GetDay())
       {
           return true;
       }
    }
    return false;
}

float CandleCalc::GetDiffClose(const Candle & cCurr, const Candle & cPrev) const
{
    return cCurr.GetClose() - cPrev.GetClose();
}
