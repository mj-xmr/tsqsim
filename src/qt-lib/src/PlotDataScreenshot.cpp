#include "pch_qt.h"
#include "PlotDataScreenshot.h"
#include <Candle.h>
#include <IPeriod.h>
#include <IBufferCandles.h>
#include "Util.h"

PlotDataScreenshot::PlotDataScreenshot(const IPeriod & period)
: PlotDataBase(period)
, financial(Util::CandlesToQCPFinancialData(period.GetCandles().GetDataIter()))
, time(GetSz())
, timeOrig(GetSz())
{
    const int n = GetSz();
    for (int i=0; i<n; ++i)
    {
        const double t = financial[i].key;
        time[i] = t;
        /*
        if (maFast[i] == 0)
            maFast[i] = financial[i].close;
        if (maSlow[i] == 0)
            maSlow[i] = financial[i].close;
            */
    }
    if (isHideWeekendData)
    {
        QVector<double> fakedTime(n);
        for (int i = 0; i < n; ++i)
        {
            const double fake = Util::ToNoWeekendSeconds(time[0], i, period);
            fakedTime[i] = fake;
            financial[i].key = fake;
        }
        timeOrig = time;
        time = fakedTime;
    }
    datesStr = Util::ExtractEveryNth<QString>(Util::DatesToStr(timeOrig), everyNth);
    ticks = Util::ExtractEveryNth<double>(time, everyNth);
}

PlotDataScreenshot::~PlotDataScreenshot()
{
}
