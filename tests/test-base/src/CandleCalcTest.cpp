#include "pch_test.h"

#include <Candle.h>
#include <CandleCalc.h>
#include <BufferCandles.h>
#include <StateFactory.h>
#include <Template/CorradePointer.h>
#include <Template/VectorViewable.hpp>
#include <STD/VectorCpp.hpp>

#include <STD/Algorithm.hpp>

static const CandleCalc cc;

static VecCanView InitCandleIncreasingCalc()
{
    VecCan vc;
    //Candle(float open, float close, float hi, float lo);
    vc.push_back(Candle(2, 3, 4, 1));
    vc.push_back(Candle(3, 4, 5, 2));
    vc.push_back(Candle(4, 5, 6, 3));
    vc.push_back(Candle(5, 6, 7, 4));
    VecCanView vcv(vc);
    return vcv;
}

static VecCanView InitCandleDecreasing()
{
    VecCanView vc = InitCandleIncreasingCalc();
    std::reverse(vc.dat.begin(), vc.dat.end());
    return vc;
}

TEST(CandleCalc_slow_increasing_1)
{
    VecCanView vc = InitCandleIncreasingCalc();

    BufferCandles bufCan(vc);
    const State past = *StateFactory().Create(BUY, 2);
    const State present = *StateFactory().Create(BUY, 0);
    const Candle & range = cc.GetRangeSlow(past, present, bufCan);
    {
        float result = range.GetLow();
        float expected = 2;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = range.GetHigh();
        float expected = 7;
        CHECK_EQUAL(expected, result);
    }
}

TEST(CandleCalc_slow_decreasing_1)
{
    VecCanView vc = InitCandleDecreasing();

    BufferCandles bufCan(vc);
    const State past = *StateFactory().Create(BUY, 2);
    const State present = *StateFactory().Create(BUY, 0);
    const Candle & range = cc.GetRangeSlow(past, present, bufCan);
    {
        float result = range.GetLow();
        float expected = 1;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = range.GetHigh();
        float expected = 6;
        CHECK_EQUAL(expected, result);
    }
}

TEST(CandleCalc_fast_increasing_1)
{
    VecCanView vc = InitCandleIncreasingCalc();

    BufferCandles bufCan(vc);
    const State past = *StateFactory().Create(BUY, 2);
    const State present = *StateFactory().Create(BUY, 0);
    const Candle & range = cc.GetRangeFast(past, present, bufCan);
    {
        float result = range.GetLow();
        float expected = 2;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = range.GetHigh();
        float expected = 7;
        CHECK_EQUAL(expected, result);
    }
}

TEST(CandleCalc_fast_decreasing_1)
{
    VecCanView vc = InitCandleDecreasing();

    BufferCandles bufCan(vc);
    const State past = *StateFactory().Create(BUY, 2);
    const State present = *StateFactory().Create(BUY, 0);
    const Candle & range = cc.GetRangeFast(past, present, bufCan);
    {
        float result = range.GetLow();
        float expected = 1;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = range.GetHigh();
        float expected = 6;
        CHECK_EQUAL(expected, result);
    }
}
