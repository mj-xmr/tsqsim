#include "pch_test.h"

#include <UnitTest++/UnitTest++.h>
#include <Template/VectorViewable.hpp>
#include <CandleScaler.h>

using namespace std;
using namespace EnjoLib;

static const CandleScaler cs;

static VecCanView InitCandleIncreasingPair()
{
    float open = 2, close = 3, hi = 4, lo = 1;
    VecCan vc;
    vc.push_back(Candle(2, 4, 5, 1));
    vc.push_back(Candle(4, 6, 7, 2));

    return vc;
}

static VecCanView InitCandleFour()
{
    float open = 2, close = 3, hi = 4, lo = 1;
    VecCan vc;
    vc.push_back(Candle(open++, close++, hi++, lo++));
    vc.push_back(Candle(open++, close++, hi++, lo++));
    vc.push_back(Candle(open++, close++, hi++, lo++));
    vc.push_back(Candle(open++, close++, hi++, lo++));

    return vc;
}

TEST(CandleScale_scaleUp)
{
    VecCanView vc = InitCandleFour();
    VecF res = cs.Scale(vc, 3);
    int i = 0;
    {
        float result = res.at(i++);
        float expected = 2;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = res.at(i++);
        float expected = 4;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = res.at(i++);
        float expected = 6;
        CHECK_EQUAL(expected, result);
    }
}

TEST(CandleScale_scaleDown)
{
    VecCanView vc = InitCandleIncreasingPair();
    VecF res = cs.Scale(vc, 5);

    int i = 0;
    {
        float result = res.at(i++);
        float expected = 2;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = res.at(i++);
        float expected = 3;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = res.at(i++);
        float expected = 4;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = res.at(i++);
        float expected = 5;
        CHECK_EQUAL(expected, result);
    }
    {
        float result = res.at(i++);
        float expected = 6;
        CHECK_EQUAL(expected, result);
    }
}
