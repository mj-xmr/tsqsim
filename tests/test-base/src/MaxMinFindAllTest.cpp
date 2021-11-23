#include "pch_test.h"

#include <Math/MaxMinFindAll.hpp>
#include <Util/VecF.hpp>
#include <UnitTest++/UnitTest++.h>

using namespace EnjoLib;

static EnjoLib::VecF GetData()
{
    EnjoLib::VecF ret;
    ret.push_back(10); // 0
    ret.push_back(9);
    ret.push_back(8);
    ret.push_back(7);  // 3  min
    ret.push_back(8);
    ret.push_back(9);
    ret.push_back(10); // 6
    ret.push_back(9);
    ret.push_back(8);
    ret.push_back(6);  // 9  min
    ret.push_back(8);
    ret.push_back(9);
    ret.push_back(10); // 12
    ret.push_back(9);
    //ret.push_back();
    return ret;
}

TEST(Two_minima_size)
{
    auto dat = GetData();
    MaxMinFindAll<float> mmfa(dat, 2);
    const MaxMinFindAll<float>::ExtremaIdx min = mmfa.GetMinimaIdx();
    int expected = 2;
    int result = min.size();
    CHECK_EQUAL(expected, result);
}

TEST(Two_minima_idx)
{
    auto dat = GetData();
    MaxMinFindAll<float> mmfa(dat, 2);
    const MaxMinFindAll<float>::ExtremaIdx min = mmfa.GetMinimaIdx();
    {
        int result = min.at(0);
        int expected = 3;
        CHECK_EQUAL(expected, result);
    }
    {
        int result = min.at(1);
        int expected = 9;
        CHECK_EQUAL(expected, result);
    }
}

TEST(Two_maxima_size_surr_1)
{
    auto dat = GetData();
    MaxMinFindAll<float> mmfa(dat, 1);
    const MaxMinFindAll<float>::ExtremaIdx max = mmfa.GetMaximaIdx();
    int expected = 2;
    int result = max.size();
    CHECK_EQUAL(expected, result);
}

TEST(One_maximum_size_surr_2)
{
    auto dat = GetData();
    MaxMinFindAll<float> mmfa(dat, 2);
    const MaxMinFindAll<float>::ExtremaIdx max = mmfa.GetMaximaIdx();
    int expected = 1;
    int result = max.size();
    CHECK_EQUAL(expected, result);
}

TEST(Two_maxima_idx_surr_1)
{
    auto dat = GetData();
    MaxMinFindAll<float> mmfa(dat, 1);
    const MaxMinFindAll<float>::ExtremaIdx max = mmfa.GetMaximaIdx();
    {
        int result = max.at(0);
        int expected = 6;
        CHECK_EQUAL(expected, result);
    }
    {
        int result = max.at(1);
        int expected = 12;
        CHECK_EQUAL(expected, result);
    }
}

TEST(One_maximum_idx_surr_2)
{
    auto dat = GetData();
    MaxMinFindAll<float> mmfa(dat, 2);
    const MaxMinFindAll<float>::ExtremaIdx max = mmfa.GetMaximaIdx();
    {
        int result = max.at(0);
        int expected = 6;
        CHECK_EQUAL(expected, result);
    }
}
