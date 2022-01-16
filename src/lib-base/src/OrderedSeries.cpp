#include "OrderedSeries.h"
#include "Tick.h"

OrderedSeries::OrderedSeries(const ISymbol & sym)
: PeriodClean(1, sym)
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

void OrderedSeries::FeedVal(double val)
{
    Tick tick;
    if (Len() == 0)
    {
        tick.year = 1970;
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
                if (tick.day == 29) // Dubious
                {
                    tick.day = 1;
                    tick.month++;
                    if (tick.month == 13)
                    {
                        tick.month = 1;
                        tick.year++;
                    }
                }
            }
        }
    }
    tick.open = tick.close = tick.hi = tick.lo = val;
    Feed(tick);
}