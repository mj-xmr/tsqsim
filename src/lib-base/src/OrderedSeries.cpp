#include "OrderedSeries.h"
#include "Tick.h"

#include <Util/CoutBuf.hpp>

OrderedSeries::OrderedSeries(const ISymbol & sym)
: PeriodClean(PeriodType::M1, sym)
{
    //ctor
}

OrderedSeries::~OrderedSeries()
{
    //dtor
}

void OrderedSeries::FeedVals(const EnjoLib::VecD & vals)
{
    for (const auto & val : vals)
    {
        FeedVal(val);
    }
}

void OrderedSeries::FeedVal(double open, double close, double high, double low)
{
    Tick tick;
    if (Len() == 0)
    {
        tick.year = 2010;
        tick.month = 1;
        tick.day = 1;
        tick.hour = 0;
        tick.minute = 0;
    }
    else
    {
        const Candle & canLast = GetCandles()[0];
        tick = canLast.ToTick();
        tick.minute++;
        if (tick.minute == 60)
        {
            tick.minute = 0;
            tick.hour++;
            if (tick.hour == 24)
            {
                tick.hour = 0;
                tick.day++;
                //LOGL << "New day = " << int(tick.day) << EnjoLib::Nl;
                if (tick.day == 29) // Dubious
                {
                    tick.day = 1;
                    tick.month++;
                    //LOGL << "New month = " << int(tick.month) << EnjoLib::Nl;

                    if (tick.month == 13)
                    {
                        tick.month = 1;
                        tick.year++;
                    }
                }
            }
        }
    }
    tick.open = open;
    tick.close = close;
    tick.hi = high;
    tick.lo = low;

    Feed(tick);
}

void OrderedSeries::FeedVal(double val)
{
    FeedVal(val, val, val, val);
}
