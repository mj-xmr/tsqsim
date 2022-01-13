#include "pch_test.h"
#include <UnitTest++/UnitTest++.h>
#include <Math/GeneralMath.hpp>
#include "CrossValidCalc.h"

using namespace std;
using namespace EnjoLib;

static int barsOpti = 1000;
static int barsAhead = 100;
static CrossValidCalc cvc(10000, barsOpti, 0.1, false);

TEST(CrossValidCalcTest_isNotValid)
{
    const OptiXValid ret = cvc.GetPass(100000000);
    bool result = ret.isValid;
    bool expected = false;
    CHECK_EQUAL(expected, result);
}

TEST(CrossValidCalcTest_isValid)
{
    const OptiXValid ret = cvc.GetPass(0);
    bool result = ret.isValid;
    bool expected = true;
    CHECK_EQUAL(expected, result);
}

TEST(CrossValidCalcTest_1st)
{
    const OptiXValid ret = cvc.GetPass(0);
    {
        int result = ret.opti.start;
        int expected = 0;
        CHECK_EQUAL(expected, result);
    }
    {
        int result = ret.opti.end;
        int expected = barsOpti;
        CHECK_EQUAL(expected, result);
    }
    {
        int result = ret.xvalid.start;
        int expected = barsOpti;
        CHECK_EQUAL(expected, result);
    }
    {
        int result = ret.xvalid.end;
        int expected = barsOpti + barsAhead;
        CHECK_EQUAL(expected, result);
    }
}

TEST(CrossValidCalcTest_2nd)
{
    const OptiXValid ret = cvc.GetPass(1);
    {
        int result = ret.opti.start;
        int expected = barsAhead;
        CHECK_EQUAL(expected, result);
    }
    {
        int result = ret.opti.end;
        int expected = barsOpti + barsAhead;
        CHECK_EQUAL(expected, result);
    }
    {
        int result = ret.xvalid.start;
        int expected = barsOpti + barsAhead;
        CHECK_EQUAL(expected, result);
    }
    {
        int result = ret.xvalid.end;
        int expected = barsOpti + barsAhead * 2;
        CHECK_EQUAL(expected, result);
    }
}

TEST(CrossValidCalcTest_last)
{
    const OptiXValid ret = cvc.GetPass(-1);
    {
        int result = ret.opti.start;
        int expected = 8900;
        CHECK_EQUAL(expected, result);
    }
    {
        int result = ret.opti.end;
        int expected = 9900;
        CHECK_EQUAL(expected, result);
    }
    {
        int result = ret.xvalid.start;
        int expected = 9900;
        CHECK_EQUAL(expected, result);
    }
    {
        int result = ret.xvalid.end;
        int expected = 9999;
        CHECK_EQUAL(expected, result);
    }
}

TEST(CrossValidCalcTest_lastNotTesting)
{
    const CrossValidCalc cvcNotTesting(10000, barsOpti, 0, true);
    const OptiXValid ret = cvcNotTesting.GetPass(-1);
    {
        int result = ret.opti.start;
        int expected = 9000;
        CHECK_EQUAL(expected, result);
    }
    {
        int result = ret.opti.end;
        int expected = 10000;
        CHECK_EQUAL(expected, result);
    }
    {
        int result = ret.xvalid.start;
        int expected = 10000;
        CHECK_EQUAL(expected, result);
    }
    {
        int result = ret.xvalid.end;
        int expected = 9999;
        CHECK_EQUAL(expected, result);
    }
}
