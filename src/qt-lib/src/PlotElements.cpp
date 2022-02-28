#include "pch_qt.h"
#include "PlotElements.h"
#include "PlotDataBase.h"
#include "ConfigQTPlot.h"
#include "IDataProvider.h"
#include "Util.h"
//#include "ConfigMan.h"
#include "ConfigQT.h"
#include "ConfigTS.h"
#include "ConfigGlob.h"
#include "ConfigMan.h"
#include <IStrategy.h>
#include <IPeriod.h>
#include <Util/VecF.hpp>
#include <Util/Pair.hpp>
#include "BufferVecUpdateable.h"
#include <BufferType.h>
#include "BufferVecType.h"
#include "PredictorOutputType.h"
#include "ISimulatorTS.h"

using namespace std;
using namespace EnjoLib;

QCPFinancial * PlotElements::SetupCandles(unsigned mi, QCustomPlot * p, const PlotDataBase & d, const ConfigQTPlot & confPlot, double binSize, bool dark)
{
    // create candlestick chart:
    QCPFinancial *candlesticks = new QCPFinancial(p->xAxis, p->yAxis);
    for (unsigned i = 0; i < mi && i < d.GetSz(); ++i)
    {
        const QCPFinancialData & fin = d.GetFinancial().at(i);
        candlesticks->addData(fin);
    }
    //candlesticks->setUseFastVectors(true);
    //if (confPlot.CANDLES)
    {
        p->addPlottable(candlesticks);
    }
    candlesticks->setAntialiased(false);
    candlesticks->setAntialiasedFill(false);
    candlesticks->setName("Candlestick");
    candlesticks->setWidth(binSize*0.9);
    candlesticks->setVisible(confPlot.CANDLES);

    ConfigureCandlesticks(candlesticks, dark);
    return candlesticks;
}

void PlotElements::ConfigureCandlesticks(QCPFinancial *candlesticks, bool dark)
{
    const int alphaCandle = 150;
    const int alphaWick = 100;
    const int colWick = dark ? 250 : 0;
    candlesticks->setChartStyle(QCPFinancial::csCandlestick);
    candlesticks->setTwoColored(true);
    candlesticks->setBrushPositive(QColor(50, 200, 50, alphaCandle));
    candlesticks->setBrushNegative(QColor(200, 50, 50, alphaCandle));
    candlesticks->setPenPositive(QPen(QColor(colWick, colWick, colWick, alphaWick)));
    candlesticks->setPenNegative(QPen(QColor(colWick, colWick, colWick, alphaWick)));
}

PlotElements::WeekendData PlotElements::GetDayWeekend(unsigned mi, const PlotDataBase & d) const
{
    WeekendData wdat;
    for (unsigned i = 1; i < mi && i < d.GetSz() - 1; ++i)
    {
        const QCPFinancialData & finCurr = d.GetFinancial().at(i);
        double dtimePrev = d.GetTimeOrig()[i-1];
        double dtimeCurr = d.GetTimeOrig()[i];

        QDateTime qtimePrev, qtimeCurr;
        qtimePrev.setTime_t(dtimePrev);
        qtimeCurr.setTime_t(dtimeCurr);
        const QDate & dateCurr = qtimeCurr.date();
        const QDate & datePrev = qtimePrev.date();
        const QTime & timeCurr = qtimeCurr.time();
        const QTime & timePrev = qtimePrev.time();
        if (dateCurr.dayOfWeek() < datePrev.dayOfWeek())
            wdat.timeWeek += finCurr.key;
        if (timeCurr.hour() < timePrev.hour())
        {
            wdat.timeDay += finCurr.key;
            if (dateCurr.dayOfWeek() == 5 && dateCurr.day() < 7)
            {
                wdat.timeNFP += finCurr.key;
            }
        }
    }
    return wdat;
}

void PlotElements::SetupDayWeekend(unsigned mi, QCustomPlot * p, const IDataProvider & period, const PlotDataBase & d, bool dark)
{
    if (period.GetName() != "d")
    {
        const WeekendData & wdat = GetDayWeekend(mi, d);
        // Vertical weekend lines
        Util::AddVLines(wdat.timeDay,    QCPRange::minRange, QCPRange::maxRange, p, dark ? "DarkGrey" : "LightGrey"); // Day
        Util::AddVLines(wdat.timeNFP,    QCPRange::minRange, QCPRange::maxRange, p, dark ? "Blue" : "Blue");          // NFP
        Util::AddVLines(wdat.timeWeek,   QCPRange::minRange, QCPRange::maxRange, p, dark ? "Green" : "Black");        // Weekend
    }
}

void PlotElements::SetupTechs(unsigned mi, QCustomPlot * p, const IStrategy & strat, QCPAxisRect *techRect, const PlotDataBase & d, bool dark)
{
    if (not strat.GetPeriod().HasBufs())
    {
        return;
    }
    const ConfigQTPlot & confPlot = *gcfgMan.cfgQTPlot;
    const ConfigQT & confQT = *gcfgMan.cfgQT;
    {
        // Buf Vec
        const auto & bufs = strat.GetPeriod().GetBufVec(BufferVecType(confQT.bufRainbow));
        for (unsigned i = 0; i < bufs.size(); ++i)
        {
            const VecF & buf = bufs.at(i);
            const float x = (i) / float(bufs.size());
            QCPGraph *newCurve = new QCPGraph(techRect->axis(QCPAxis::atBottom), techRect->axis(QCPAxis::atLeft));
            //newCurve->setAntialiased(false);
            newCurve->setPen(QColor::fromHslF(x, 0.95, 0.5));
            SetupTechLine(p, d, Util::stdVectToQVectF(buf.Data()), newCurve);
        }
    }
    {
        // Buf
        vector<EnjoLib::Pair<BufferType, QPen>> techs;
        techs.push_back(EnjoLib::MakePair(BufferType(confQT.buf1), QPen(Qt::blue)));
        techs.push_back(EnjoLib::MakePair(BufferType(confQT.buf2), QPen(Qt::green)));//QPen(Qt::darkGreen)));
        techs.push_back(EnjoLib::MakePair(BufferType(confQT.buf3), QPen(Qt::red)));

        SetupTechsVec(p, strat, techRect, d, techs);
    }
    if (dark)
    {
        const QPen & gridPen = GetDarkGridPen();
        techRect->axis(QCPAxis::atBottom)->grid()->setPen(gridPen);
        techRect->axis(QCPAxis::atLeft)  ->grid()->setPen(gridPen);
        //p->xAxis->setTickLabelColor(QColor(gridIntens, gridIntens, gridIntens));
    }
    if (confPlot.DAY_WEEK)
    {
        SetupDayWeekendTech(mi, p, techRect, d, dark);
    }
}

QPen PlotElements::GetDarkGridPen() const
{
    const int gridIntens = 50;
    const QPen gridPen(QColor(gridIntens, gridIntens, gridIntens));
    return gridPen;
}

void PlotElements::SetupDayWeekendTech(unsigned mi, QCustomPlot * p, QCPAxisRect *techRect, const PlotDataBase & d, bool dark)
{
        /// TODO: Implement this somehow
        const WeekendData & wdat = GetDayWeekend(mi, d);
        /*
        Util::AddVLines(wdat.timeDay,    QCPRange::minRange, QCPRange::maxRange, p, dark ? "DarkGrey" : "LightGrey"); // Day
        if (period.GetName() != "d")
        {
            const WeekendData & wdat = GetDayWeekend(mi, d);
            // Vertical weekend lines
            Util::AddVLines(wdat.timeDay,    QCPRange::minRange, QCPRange::maxRange, p, dark ? "DarkGrey" : "LightGrey"); // Day
            Util::AddVLines(wdat.timeNFP,    QCPRange::minRange, QCPRange::maxRange, p, dark ? "Blue" : "Blue");          // NFP
            Util::AddVLines(wdat.timeWeek,   QCPRange::minRange, QCPRange::maxRange, p, dark ? "Green" : "Black");        // Weekend
        }
        */
        Util::AddVLinesTech(wdat.timeDay,    p, techRect, dark ? "DarkGrey" : "LightGrey"); // Day
        Util::AddVLinesTech(wdat.timeNFP,    p, techRect, dark ? "Blue" : "Blue");          // NFP
        Util::AddVLinesTech(wdat.timeWeek,   p, techRect, dark ? "Green" : "Black");        // Weekend
}

void PlotElements::SetupTechsVec(QCustomPlot * p, const IStrategy & strat, QCPAxisRect *techRect, const PlotDataBase & d, const vector<EnjoLib::Pair<BufferType, QPen>> & techs)
{
    if (not strat.GetPeriod().HasBufs())
    {
        return;
    }
    //BufferType tech1 = BUF_STOCH_K;

    p->setAutoAddPlottableToLegend(false);
    for (const EnjoLib::Pair<BufferType, QPen> & bufTypePen : techs)
    {
        const BufferTypeEnum type = bufTypePen.first.GetType();
        QCPGraph *newCurve = new QCPGraph(techRect->axis(QCPAxis::atBottom), techRect->axis(QCPAxis::atLeft));
        //newCurve->setAntialiased(false);
        newCurve->setPen(bufTypePen.second);
        if (type == BUF_STRAT)
        {
            SetupTechLine(p, d, Util::BufferToQVectF(strat.GetBuf(gcfg.DIRECTION)), newCurve); // could be changed to BUF_STRAT_BULL
        }
        else if (type != BUF_NONE)
        {
            SetupTechLine(p, d, d.GetBuf(type), newCurve);
        }
    }
    QCPGraph *newCurve = new QCPGraph(techRect->axis(QCPAxis::atBottom), techRect->axis(QCPAxis::atLeft));
    newCurve->setPen(QPen(Qt::yellow));
    // Setup line with constant value
    //SetupTechLine(p, d, QVector<double>(d.GetTime().size(), 1), newCurve);
}

void PlotElements::SetupTechsXform(QCustomPlot * p, const ISimulatorTS & simTS, QCPAxisRect *techRect, const PlotDataBase & d)
{
    SetupTSLine(p, techRect, d, simTS, PredictorOutputType::SERIES,     QPen(Qt::blue),   "Series");
    //SetupTSLine(p, techRect, d, simTS, PredictorOutputType::PREDICTION, QPen(Qt::green),  "Prediction");
    //SetupTSLine(p, techRect, d, simTS, PredictorOutputType::BASELINE,   QPen(Qt::gray),   "Baseline");
}

void PlotElements::SetupReconstruction(QCustomPlot * p, const ISimulatorTS & simTS, const PlotDataBase & d)
{
    const ConfigTS & confTS = *gcfgMan.cfgTS;
    Util::AddMA(d.GetTime(), Util::stdVectToQVectF(simTS.GetOutputSeries(PredictorOutputType::RECONSTRUCTION).Data()),               p, Qt::blue);
    Util::AddMA(d.GetTime(), Util::stdVectToQVectF(simTS.GetOutputSeries(PredictorOutputType::RECONSTRUCTION_PRED).Data()),          p, Qt::green);
    //Util::AddMA(d.GetTime(), Util::stdVectToQVectF(simTS.GetOutputSeries(PredictorOutputType::PREDICTION).Data()),          p, Qt::yellow);
    if (confTS.PLOT_BASELINE)
    {
        Util::AddMA(d.GetTime(), Util::stdVectToQVectF(simTS.GetOutputSeries(PredictorOutputType::RECONSTRUCTION_PRED_BASELINE).Data()), p, Qt::gray);
    }
}

QCPGraph * PlotElements::SetupTSLine(QCustomPlot * p, QCPAxisRect *techRect, const PlotDataBase & d, const ISimulatorTS & simTS, const PredictorOutputType & type, const QPen & pen, const char * name)
{
    QCPGraph *newCurve = new QCPGraph(techRect->axis(QCPAxis::atBottom), techRect->axis(QCPAxis::atLeft));
    newCurve->setPen(pen);
    const VecD & tsdata = simTS.GetOutputSeries(type);
    SetupTechLine(p, d, Util::stdVectToQVectF(tsdata.Data()), newCurve);
    return newCurve;
}

void PlotElements::SetupTechLine(QCustomPlot * p, const PlotDataBase & d, const QVector<double> & vec, QCPGraph *newCurve)
{
    newCurve->setData(d.GetTime(), vec);
    p->addPlottable(newCurve);
}

QCPAxisRect * PlotElements::SetupGetIndicatorRect(QCustomPlot * p, const PlotDataBase & d)
{
    QCPAxisRect * techRect = new QCPAxisRect(p);
    p->plotLayout()->addElement(1, 0, techRect);
    techRect->setMaximumSize(QSize(QWIDGETSIZE_MAX, 200));
    techRect->axis(QCPAxis::atBottom)->setLayer("axes");
    techRect->axis(QCPAxis::atBottom)->grid()->setLayer("grid");
    p->plotLayout()->setRowSpacing(0);
    techRect->setAutoMargins(QCP::msLeft|QCP::msRight|QCP::msBottom);
    techRect->setMargins(QMargins(0, 0, 0, 0));
    // Weekend data
    HandleWeekendData(techRect->axis(QCPAxis::atBottom), d, d.isHideWeekendData);

    techRect->axis(QCPAxis::atBottom)->setTickLabelType(QCPAxis::ltDateTime);
    techRect->axis(QCPAxis::atBottom)->setDateTimeSpec(Qt::UTC);
    techRect->axis(QCPAxis::atBottom)->setDateTimeFormat("dd. MMM");
    techRect->axis(QCPAxis::atBottom)->setTickLabelRotation(25);
    techRect->axis(QCPAxis::atLeft)->setAutoTickCount(3);

    return techRect;
}

void PlotElements::HandleWeekendData(QCPAxis * axis, const PlotDataBase & d, bool hide)
{
    if (hide)
    {
        axis->setAutoTicks(false);
        axis->setAutoTickLabels(false);
        axis->setTickVector(d.GetTicks());
        axis->setTickVectorLabels(d.GetDatesStr());
        //axis->setAutoTickStep(true);
    }
    else
    {
        axis->setAutoTickStep(false);
        axis->setTickStep(3600*24*4); // 4 day tickstep
    }
}

