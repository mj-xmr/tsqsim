#include "PeriodGapFinder.h"
#include "IBufferCandles.h"
#include "Candle.h"
#include "IPeriod.h"

#include <Util/Str.hpp>
#include <Util/CoutBuf.hpp>
#include <Math/GeneralMath.hpp>

#include <STD/VectorCpp.hpp>

using namespace std;
using namespace EnjoLib;

PeriodGapFinder::PeriodGapFinder(const IPeriod & per)
: m_per(per)
{
}

void PeriodGapFinder::Print() const
{
    const auto & candles = m_per.GetCandles().GetDataIter();
    const int hours = m_per.GetNumTicks() / 60;
    for (int i = 1; i < m_per.Len(); ++i)
    {
        const Candle & prev = candles[i-1];
        const Candle & curr = candles[i];

        const int diffDayHour = ( curr.GetHour() + curr.GetDay() * 24 ) - (prev.GetHour() + prev.GetDay() * 24);
        if (diffDayHour != hours)
        {
            LOGL << curr.GetDateStr() << " vs " << prev.GetDateStr() << ": diff time by " << diffDayHour << Nl;
        }
    }
}
