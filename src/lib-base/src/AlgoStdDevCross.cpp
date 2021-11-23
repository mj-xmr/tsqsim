#include "AlgoStdDevCross.h"
#include "Candle.h"
#include "CandleCalc.h"

AlgoStdDevCross::AlgoStdDevCross(){}
AlgoStdDevCross::~AlgoStdDevCross(){}

bool AlgoStdDevCross::Calc(float stdDev, const Candle & c, Direction bullish) const
{
    //const float multiplier = 1.5;
    //const float multiplier = 2.0; // used in TF
    const float multiplier = 2.5;
    //const float multiplier = 3.0;
    //const float multiplier = 3.5;
    //const float multiplier = 1.5;
    //const float multiplier = 1.0;
    //const float multiplier = 0.5;
    const float stdDevMul = stdDev * multiplier;
    const CandleCalc cc;
    const float mid = cc.GetMidPrice(c);
    if (bullish)
    {
        const float refPrice = mid - stdDevMul;
        if (c.GetLow() < refPrice)
            return true;
    }
    else
    {
        const float refPrice = mid + stdDevMul;
        if (c.GetHigh() > refPrice)
            return true;
    }
    return false;
}
