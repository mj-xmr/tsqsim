#include "pch_test.h"

#include "typesVec.h"

#include <UnitTest++/UnitTest++.h>

#include <Template/VectorViewable.hpp>
#include <CandleAggr.h>
#include <Util/CoutBuf.hpp>

using namespace std;

static const CandleAggr cag;

static VecCanView InitCandleIncreasingAggr()
{
    float open = 2, close = 3, hi = 4, lo = 1;
    VecCan vc;
    vc.push_back(Candle(open++, close++, hi++, lo++));
    vc.push_back(Candle(open++, close++, hi++, lo++));
    vc.push_back(Candle(open++, close++, hi++, lo++));
    vc.push_back(Candle(open++, close++, hi++, lo++));

    return vc;
}

static VecCanView InitCandleIncreasingAggrNoisy()
{
    VecCan vc;
    //Candle(float open, float close, float hi, float lo); // for unit testing
    float open = 2, close = 3, hi = 4, lo = 1;
    vc.push_back(Candle(open++, close++, hi++, lo++));
    vc.push_back(Candle(open++, close++, hi++, lo++));
    vc.push_back(Candle(close,   open-2, hi, lo));
    vc.push_back(Candle(open++, close++, hi++, lo++));
    vc.push_back(Candle(open++, close++, hi++, lo++));

    return vc;
}

TEST(CandleAggr_increasing_1)
{
    VecCanView vc = InitCandleIncreasingAggr();
    const Candle & res = cag.JoinCandles(vc);
    {
        float result = res.GetLow();
        float expected = 1;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = res.GetHigh();
        float expected = 7;
        CHECK_EQUAL(expected, result);
    }
}

TEST(CandleAggr_increasing_noisy_1)
{
    VecCanView vc = InitCandleIncreasingAggrNoisy();
    const Candle & res = cag.JoinCandles(vc);
    //cout << "Joined: " << res.PrintOCHL() << endl;
    {
        float result = res.GetLow();
        float expected = 1;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = res.GetHigh();
        float expected = 7;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = res.GetOpen();
        float expected = 2;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = res.GetClose();
        float expected = 6;
        CHECK_EQUAL(expected, result);
    }
}

TEST(CandleAggr_increasing_noisy_join_disperse)
{
    VecCanView vc = InitCandleIncreasingAggrNoisy();
    const Candle & res = cag.JoinCandles(vc);
    //cout << "Joined: " << res.PrintOCHL() << endl;
    VecCan vcAg = cag.ToNCandles(res, 4);
    {
        for (const Candle & c : vcAg)
        {
            //cout << "ASD: " << c.PrintOCHL() << endl;
        }
        LOGL << EnjoLib::Nl;
    }
    float result = 0;
    float expected = 0;
    CHECK_EQUAL(expected, result);
}

TEST(CandleAggr_increasing_noisy_aggr)
{
    VecCanView vc = InitCandleIncreasingAggrNoisy();
    VecCan vcAg = cag.AggregateCandles(vc, 4);
    {
        for (const Candle & c : vcAg)
        {
            //cout << "ASD: " << c.PrintOCHL() << endl;
        }
    }
    float result = 0;
    float expected = 0;
    CHECK_EQUAL(expected, result);
}

TEST(CandleAggr_aggr_sizes_equal)
{
    VecCanView vc = InitCandleIncreasingAggr();
    VecCan vcAg = cag.AggregateCandles(vc, 2);
    {
        float result = vcAg.size();
        float expected = vc.size();
        CHECK_EQUAL(expected, result);
    }
}

TEST(CandleAggr_aggr_split)
{
    VecCanView vc = InitCandleIncreasingAggrNoisy();
    VecCan vcAg = cag.AggregateCandles(vc, 1);
    {
        for (const Candle & c : vcAg)
        {
            //cout << "ASD: " << c.PrintOCHL() << endl;
        }
        float result = vcAg.size();
        float expected = vc.size();
        CHECK_EQUAL(expected, result);
    }
}

TEST(CandleAggr_split_simple)
{
    const unsigned sz = 4;
    const Candle c(0, 4, 4, 0);
    VecCan vcAg = cag.ToNCandles(c, sz);
    {
        for (const Candle & c : vcAg)
        {
            //cout << "ASD: " << c.PrintOCHL() << endl;
        }

        float result = vcAg.size();
        float expected = sz;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = vcAg.at(0).GetOpen();
        float expected = 0;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = vcAg.at(0).GetClose();
        float expected = 1;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = vcAg.at(1).GetOpen();
        float expected = 1;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = vcAg.at(1).GetClose();
        float expected = 2;
        CHECK_EQUAL(expected, result);
    }
}
