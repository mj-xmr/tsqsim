#ifndef CANDLECALC_H
#define CANDLECALC_H

#include "Direction.h"

struct CandleWick
{
    float wickBase = 0;
    float wickExtreme = 0;
    float wickExtension = 0;
    float wickLen = 0;
};

struct PairInt
{
    PairInt(int one = 0, int two = 0) : one(one), two(two){}
    int one;
    int two;
    bool IsValid() const
    {
        return one > 0 && two > 0;
    }
};

class State;
class IBufferCandles;
class Candle;
class CandleCalc
{
    public:
        CandleCalc();
        virtual ~CandleCalc();

        float GetMidPrice(const Candle & c) const;
        float GetMidBody(const Candle & c) const;
        float GetLen(const Candle & c) const;
        float GetBodyLen(const Candle & c) const;
        float GetPriceChange(const Candle & cCurr, const Candle & cPrev) const;
        bool IsInCandle(const Candle & c, float level) const;
        bool IsAfterMidnight(const Candle & cOne, const Candle & cTwo) const;
        CandleWick CalcWick(const Candle & c, Direction bullish, float extensionMul = 0) const;
        PairInt GetMinMaxSlow(const State & past, const State & present, const IBufferCandles & bufCan) const;
        Candle GetRangeFast(const State & past, const State & present, const IBufferCandles & bufCan) const;
        Candle GetRangeSlow(const State & past, const State & present, const IBufferCandles & bufCan) const;

        float GetDiffClose(const Candle & cCurr, const Candle & cPrev) const;

    protected:
    private:
};

#endif // CANDLECALC_H
