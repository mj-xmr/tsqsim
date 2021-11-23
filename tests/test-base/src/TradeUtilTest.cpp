#include "pch_test.h"
#include <UnitTest++/UnitTest++.h>
#include <TradeUtil.h>
#include <TradeUtilThin.h>
#include <Ios/Osstream.hpp>
#include <Ios/Isstream.hpp>

#include <STD/VectorCpp.hpp>

#include <STD/Algorithm.hpp>    // std::count

using namespace std;

const static TradeUtil tu;
const static TradeUtilThin tut;
const static string dateSig1 = "AUDJPY_h4_2014_08_26__00_00";
const static string date1 = "2014_08_26__00_00";
const static string dateUSA = "12.22.2016 00:41";

static EnjoLib::Str GenCorrelTable()
{
    EnjoLib::Osstream oss;
    oss << "EURGBP-GBPCHF-h1 = -0.942323\n";
    oss << "EURGBP-GBPJPY-h1 = -0.864064\n";
    oss << "NZDJPY-XAGUSD-h1 = -0.734708\n";
    oss << "EURJPY-GBPJPY-h1 = 0.719746\n";
    oss << "XAGUSD-XAUUSD-h1 = 0.834838\n";
    oss << "GBPJPY-GBPUSD-h1 = 0.900402\n";
    oss << "GBPCHF-GBPJPY-h1 = 0.939397\n";
    oss << "GBPCHF-GBPUSD-h1 = 0.962308\n";
    oss << "BCOUSD-WTIUSD-h1 = 0.981633\n";
    return oss.str();
}

static EnjoLib::Str GenStats()
{
    EnjoLib::Osstream oss;
    oss << "EURCHF-EURUSD-h1 -0.0629653 -0.4 1\n";
    oss << "CHFJPY-USDJPY-h1 -0.0394166 -0.7 1\n";
    oss << "GBPCHF-GBPUSD-h1 -0.0250109 -0.6 1\n";
    oss << "AUDJPY-NZDJPY-h1 0.128948 -0.05 1\n";
    oss << "USDJPY-CHFJPY-h1 0.0135876 -0.2 1\n";
    oss << "GBPUSD-GBPCHF-h1 0.0608711 -0.4 1\n";
    oss << "WTIUSD-BCOUSD-h1 0.32324 -0.08 1\n";
    return oss.str();
}

TEST(TradeUtil_test1)
{
    DateInt result = tu.SigIdUnderscore2DateInt(dateSig1);
    DateInt expected = 20140826000000;
    CHECK_EQUAL(expected, result);
}

TEST(TradeUtil_test2)
{
    DateInt result = tu.DateUnderscore2DateInt(date1);
    DateInt expected = 20140826000000;
    CHECK_EQUAL(expected, result);
}

TEST(TradeUtil_test3)
{
    DateInt result = tu.DateUSA2DateInt(dateUSA);
    DateInt expected = 20161222004100;
    CHECK_EQUAL(expected, result);
}

TEST(TradeUtil_test4)
{
    DateInt result = tu.DateISO2DateInt(2013, 12, 2);
    DateInt expected = 20131202000000;
    CHECK_EQUAL(expected, result);
}

TEST(TradeUtil_test5)
{
    DateInt result = tu.DateISO2DateInt(2013, 9, 10);
    DateInt expected = 20130910000000;
    CHECK_EQUAL(expected, result);
}

TEST(TradeUtil_test6)
{
    EnjoLib::Str result = tu.Date2DateRawStr(20100118020100);
    EnjoLib::Str expected = "20100118";
    CHECK_EQUAL(expected, result);
}

TEST(TradeUtil_test7)
{
    EnjoLib::Str result = tu.Date2TimeRawStr(20100118020100);
    EnjoLib::Str expected = "020100";
    CHECK_EQUAL(expected, result);
}

TEST(TradeUtil_testTimestamp1)
{
    DateInt result = tu.Timestamp2DateInt("1397858361");
    DateInt expected = 20140418215921;

    CHECK_EQUAL(expected, result);
}


TEST(TradeUtil_GetAllSymbolsFromCorrelsFile_positive_single_instances)
{
    EnjoLib::Isstream iss(GenCorrelTable().str());
    const VecStr & ret = tu.GetAllSymbolsFromCorrelsFile(0, iss);
    const int expected = 1;
    CHECK_EQUAL(expected, ret.Contains("GBPCHF"));
    CHECK_EQUAL(expected, ret.Contains("BCOUSD"));
    CHECK_EQUAL(expected, ret.Contains("WTIUSD"));
    CHECK_EQUAL(expected, ret.Contains("GBPUSD"));
}

TEST(TradeUtil_GetAllSymbolsFromCorrelsFile_filter_poor_correl)
{
    EnjoLib::Isstream iss(GenCorrelTable().str());
    const VecStr & ret = tu.GetAllSymbolsFromCorrelsFile(0.9, iss);
    CHECK_EQUAL(0, ret.Contains("EURJPY"));
    CHECK_EQUAL(0, ret.Contains("XAGUSD"));
}

TEST(TradeUtil_GetAllSymbolsFromCorrelsFile_leave_good_correl)
{
    EnjoLib::Isstream iss(GenCorrelTable().str());
    const VecStr & ret = tu.GetAllSymbolsFromCorrelsFile(0.9, iss);
    CHECK_EQUAL(1, ret.Contains("WTIUSD"));
    CHECK_EQUAL(1, ret.Contains("BCOUSD"));
    CHECK_EQUAL(1, ret.Contains("GBPUSD"));
}

TEST(TradeUtil_GetPairsSymbolsFromCorrelsFile_get_both_good)
{
    EnjoLib::Isstream iss(GenCorrelTable().str());
    const vector<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> & ret = tu.GetPairsSymbolsFromCorrelsFile(0.9, iss);
    CHECK_EQUAL("WTIUSD", ret.at(ret.size() - 1).first);
    CHECK_EQUAL("BCOUSD", ret.at(ret.size() - 1).second);
    CHECK_EQUAL("BCOUSD", ret.at(ret.size() - 2).first);
    CHECK_EQUAL("WTIUSD", ret.at(ret.size() - 2).second);

    CHECK_EQUAL("GBPUSD", ret.at(ret.size() - 3).first);
    CHECK_EQUAL("GBPCHF", ret.at(ret.size() - 3).second);
    CHECK_EQUAL("GBPCHF", ret.at(ret.size() - 4).first);
    CHECK_EQUAL("GBPUSD", ret.at(ret.size() - 4).second);
}

TEST(TradeUtil_GetPairsSymbolsFromStatsFile_get_both_good)
{
    EnjoLib::Isstream iss(GenStats().str());
    const float minSharpe = 0.1;
    const float maxMaxDD = 0.1;
    const std::vector<EnjoLib::Tuple<EnjoLib::Str, EnjoLib::Str, float>> & ret = tu.GetPairsSymbolsLeverageFromStatsFile(minSharpe, maxMaxDD, iss);
    CHECK_EQUAL("WTIUSD", EnjoLib::Get<0>(ret.at(ret.size() - 1)));
    CHECK_EQUAL("BCOUSD", EnjoLib::Get<1>(ret.at(ret.size() - 1)));
    CHECK_EQUAL(1.25    , EnjoLib::Get<2>(ret.at(ret.size() - 1)));

    CHECK_EQUAL("AUDJPY", EnjoLib::Get<0>(ret.at(ret.size() - 2)));
    CHECK_EQUAL("NZDJPY", EnjoLib::Get<1>(ret.at(ret.size() - 2)));
    CHECK_EQUAL(2       , EnjoLib::Get<2>(ret.at(ret.size() - 2)));

    CHECK_EQUAL(2       , ret.size());
}

TEST(TradeUtil_GetIdFromPrice_1_leading)
{
    const int actual = tut.GetIdFromPrice(1.12345);
    const int expected = 112345;

    CHECK_EQUAL(expected, actual);
}

TEST(TradeUtil_GetIdFromPrice_2_leading)
{
    const int actual = tut.GetIdFromPrice(11.1234);
    const int expected = 111234;

    CHECK_EQUAL(expected, actual);
}

TEST(TradeUtil_GetIdFromPrice_3_leading)
{
    const int actual = tut.GetIdFromPrice(111.123);
    const int expected = 111123;

    CHECK_EQUAL(expected, actual);
}

TEST(TradeUtil_DateZeroMinute)
{
    const DateInt actual = tu.DateZeroMinute(20100118020100);
    const DateInt expected = 20100118020000;

    CHECK_EQUAL(expected, actual);
}


TEST(TradeUtil_DateZeroHour)
{
    const DateInt actual = tu.DateZeroHour(20100118020100);
    const DateInt expected = 20100118000000;

    CHECK_EQUAL(expected, actual);
}
