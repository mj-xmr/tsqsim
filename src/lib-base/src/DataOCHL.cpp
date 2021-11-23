#include "DataOCHL.h"
#include "Tick.h"
#include "Candle.h"
#include "typesVec.h"

#include <Util/CoutBuf.hpp>
#include <Ios/Osstream.hpp>
#include <Template/VectorViewable.hpp>

#include <cassert>

using namespace std;
using namespace EnjoLib;

DataOCHL::DataOCHL(){}
DataOCHL::~DataOCHL(){}

DataOCHL::DataOCHL(const IterCan & candles)
{
    Copy(candles);
}

void DataOCHL::Add(const Tick & tick)
{
    opens.push_back(tick.open);
    closes.push_back(tick.close);
    highs.push_back(tick.hi);
    lows.push_back(tick.lo);
    dates.push_back(tick.YYYYMMDDhhmmss());
}

void DataOCHL::Add(const Candle & tick)
{
    return Add(tick.ToTick());
}

void DataOCHL::UpdateLast(const Candle & candle)
{
    if (opens.empty())
    {
        Add(candle);
        return;
    }

    opens.back() = candle.GetOpen();
    closes.back() = candle.GetClose();
    highs.back() = candle.GetHigh();
    lows.back() = candle.GetLow();
    dates.back() = candle.GetClose();
}

void DataOCHL::Copy(const VecCan & candles)
{
    const VecCanView view(candles);
    Copy(view);
}

void DataOCHL::Copy(const IterCan & candles)
{
    unsigned sz = candles.size();
    lows = highs = closes = opens = EnjoLib::VecF(sz);
    dates = VecT<DateInt>(sz);
    for(unsigned i = 0; i < sz; ++i)
    {
        const Candle & c = candles[i];
        opens[i] = c.GetOpen();
        closes[i] = c.GetClose();
        highs[i] = c.GetHigh();
        lows[i] = c.GetLow();
        DateInt date = c.GetDate();
        dates[i] = date;
    }
}

VecCan DataOCHL::ToCandles() const
{
    VecCan ret;
    const unsigned sz = Size();
    for(unsigned i = 0; i < sz; ++i)
    {
        Candle can(opens[i], closes[i], highs[i], lows[i]);
        can.SetDate(dates[i]);
        ret.push_back(can);
    }
    return ret;
}

float DataOCHL::GetPriceClose(int i) const
{
    return closes.at(i);
}

float DataOCHL::GetPriceMid(int i) const
{
    return (highs.at(i) + lows.at(i)) / 2.0;
}

float DataOCHL::GetPriceWeighted(int i) const
{
    return (highs.at(i) + lows.at(i) + closes.at(i) * 2) / 4.0;
}

float DataOCHL::GetPriceTypical(int i) const
{
    return (highs.at(i) + lows.at(i) + closes.at(i)) / 3.0;
}

void DataOCHL::PrintPython() const
{
    EnjoLib::Osstream oss;
    oss << opens.PrintPython("opens");
    oss << highs.PrintPython("highs");
    oss << lows.PrintPython("lows");
    oss << closes.PrintPython("closes");
    LOGL << oss.str();
}

unsigned DataOCHL::Size() const
{
    return opens.size();
}

unsigned DataOCHL::Len() const
{
    return Size();
}
