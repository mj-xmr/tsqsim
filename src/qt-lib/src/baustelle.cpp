#include "pch_qt.h"

#include "global.h"

#include "MyMainWindow.h"
#include "ui_mainwindow.h"

/// TODO: Restore
//#include "PlotZigZag.h"
//#include "PlotSRGroup.h"
//#include "PlotStdDev.h"
//#include "PlotRegression.h"
//#include "TxtSimulator.h"
//#include "TxtSmall.h"
//#include "BetColorMap.h"
#include "PlotElements.h"

#include <IPeriod.h>
//#include <IStrategy.h>
#include <ConfigGlob.h>
#include <ConfigQT.h>
#include <ConfigQTPlot.h>
#include "Util.h"

#include "PlotDataBase.h"
#include <BufferType.h>
#include "BufferVecType.h"
#include "BufferUpdateable.h"
//#include <SimulatorBetFactory.h>

#include <Util/Except.hpp>
#include <Util/Timer.hpp>
#include <Util/CoutBuf.hpp>


using namespace std;
using namespace EnjoLib;

void MyMainWindow::setupVisualsBig(QCustomPlot * p, const IPeriod & period, const IStrategy & strat, const PlotData & d)
{
    ConfigQTPlot confPlot;
    confPlot.Read();
    //m_simulator->SetupPending();

    //TxtFractals(p, period, d);
//#undef DEBUG
#ifndef DEBUG
        //const IStrategy & strat = *(m_strategy.get());
        if (confPlot.SIGNAL_TRADE)
        {
            /// TODO: Restore
            //TxtSmall().SignalScore(p, period, strat, BUY, d);
            //TxtSmall().SignalScore(p, period, strat, SELL, d);
        }

        //cout << "Simulator" << endl;
        //TxtSmall().Pinbars(p, period, strat, d);
        /// TODO: Restore
        //TxtSimulator().Txt(p, period, strat, d);
        //cout << "SimulatorEnded" << endl;

        if (confPlot.BET)
        {
            /// TODO: Restore
            //m_mons.m_simulatorBet->Collect();
            //BetColorMap().Plot(p, period, d, *m_mons.m_simulatorBet);
        }
        if (confPlot.ZIG_ZAG)
        {
            /// TODO: Restore
            //PlotZigZag pzz(confPlot.ZIG_ZAG_INDEXES);
            //pzz.Plot(p, period, d);
            //pzz.PlotDual(p, period, d);
            //pzz.PlotMovePrediction(p, period, d);
            //pzz.PlotZZFract(p, period, d);
            //pzz.PlotZZMaCross(p, period, d);
            //pzz.PlotZZMaSuperFast(p, period, d);
            //pzz.PlotMulti(p, period, d);
            //pzz.PlotPattern(p, period, d);
            //pzz.PlotCandleSeries(p, period, d);
            //pzz.PlotCandleSeriesEMA(p, period, d);
            //pzz.PlotTrendLine(p, period, d);
            //pzz.PlotCandleSeriesLoop(p, period, d);
            //pzz.PlotCandleSeriesLoopSpread(p, period, d);

            //PlotRegression preg;
            //preg.PlotPolyGSL(p, period, d);
            //preg.PlotPolyGSLRange(p, period, d, regressionStart, regressionEnd);
        }
        if (confPlot.STD_DEV)
        {
            //PlotStdDev pltStdDev;
            //pltStdDev.PlotWicks(p, period, d);
            //pltStdDev.PlotBBands(p, period, d);
            //Util::AddMAVec(p, d, period. GetBufVec(BUF_VEC_BBANDS));
            //Util::AddMA(d.GetTime(), d.stdDevAbove, p, Qt::blue);
            //Util::AddMA(d.GetTime(), d.stdDevBelow, p, Qt::green);
        }

        if (confPlot.SR_GROUPS)
        {
            //PlotSRGroup psrg;
            //psrg.Plot(p, period, d);
            //psrg.PlotStrat(p, period, strat, d);
        }
#endif

    //const IPeriod & period = m_symbol->GetPeriod(m_periodName);
    QColor colSLBull = "Plum";//"Pink";
    QColor colSLBear = Qt::red;
    /// TODO: Restore
    //m_slBull = Util::AddMA(d.GetTime(), d.slBull, p, colSLBull);
    //m_slBear = Util::AddMA(d.GetTime(), d.slBear, p, colSLBear);
    m_txtPrice = Util::AddText(p, "");

    if (confPlot.SL)
    {
        /// TODO: Restore
        /*
        Util::AddMA(d.GetTime(), d.slBullStatic, p, colSLBull);
        Util::AddMA(d.GetTime(), d.slBearStatic, p, colSLBear);

        Util::AddMA(d.GetTime(), d.slBullAda, p, "Blue");
        Util::AddMA(d.GetTime(), d.slBearAda, p, "Blue");
        */
    }

    if (confPlot.SIGNAL_SPECIAL)
    {
        /// TODO: Restore
        //Util::AddMA(d.GetTime(), d.pullbackBuy,  p, Qt::green);
        //Util::AddMA(d.GetTime(), d.pullbackSell, p, "Plum");
    }
    if (confPlot.SIGNAL_TRADE)
    {
        /// TODO: Restore
        /*
        Util::AddMA(d.GetTime(), d.sigStartBuy,  p, "darkgreen");
        Util::AddMA(d.GetTime(), d.sigStartSell, p, "fuchsia");
#ifndef DEBUG
        TxtSmall().SpecialSignalText(p, period, strat, d);

        TxtSmall().SpecialSignalPred(p, period, strat, BUY, d);
        TxtSmall().SpecialSignalPred(p, period, strat, SELL, d);
#endif
        */
    }

    /// TODO: Restore
    /*
    Util::AddMA(d.GetTime(), d.labStart, p, "LightGray");
    Util::AddMA(d.GetTime(), d.labEnd, p,   "LightPink");
    //Util::AddMA(d.GetTime(), d.labIn, p,   "Plum");

    Util::AddMA(d.GetTime(), d.labSigBull, p,   "Blue");
    Util::AddMA(d.GetTime(), d.labSigBear, p,   "Red");

    if (confPlot.SR)
    {
        for (const Fractal & f : d.support)
        {
            Util::AddLine(f.GetTime(), f.GetData(), p, f.IsBroken() ? "LightSlateGray" : "LightGray");
        }
        for (const Fractal & f : d.resistance)
        {
            Util::AddLine(f.GetTime(), f.GetData(), p, f.IsBroken() ? "Plum" : "LightPink" );
        }
    }
    */
}

void MyMainWindow::setupVisuals(QCustomPlot * p, const IPeriod & period, const IStrategy & strat, const ISimulatorTS & simTS, const PlotDataBase & d, double binSize)
{
    ConfigQTPlot confPlot;
    confPlot.Read();
    m_dark = confPlot.DARK;
    if (m_dark)
    {
        p->setBackground(QBrush("black"));
        const int gridIntens = 50;
        const QPen gridPen(QColor(gridIntens, gridIntens, gridIntens));
        p->yAxis->grid()->setPen(gridPen);
        p->xAxis->grid()->setPen(gridPen);
        //p->xAxis->setTickLabelColor(QColor(gridIntens, gridIntens, gridIntens));
    }

    PlotElements pel;
    {
        if (confPlot.DAY_WEEK)
            pel.SetupDayWeekend(m_i, p, period, d, m_dark);
        m_candlesticks = pel.SetupCandles(m_i, p, d, confPlot, binSize, m_dark);

        if (confPlot.MA)
        {
            //Util::AddMA(p, d, BUF_MA_FAST, "LightGreen");
            //Util::AddMA(p, d, BUF_MA_SLOW, Qt::green);
            //Util::AddMA(p, d, BUF_TEST, Qt::yellow);

            //Util::AddMA(p, d, BUF_MA_SUPER_FAST, Qt::blue);
            //Util::AddMA(p, d, BUF_SSA_OSCI, Qt::blue);

            //Util::AddMAVec(p, d, period.GetBufVec(BUF_VEC_MA_RIBBON));
            //Util::AddMAVec(p, d, period.GetBufVec(BUF_VEC_MA_REG_RIBBON));

            //Util::AddMA(p, d, BUF_MA_AVG, "Pink");
        }
        {
            pel.SetupReconstruction(p, simTS, d);
        }
    }

    pel.HandleWeekendData(p->xAxis, d, d.isHideWeekendData);

    p->xAxis->setTickLabels(false);
    p->xAxis->setTicks(false); // only want vertical grid in main axis rect, so hide xAxis backbone, ticks, and labels

    p->rescaleAxes();
    p->xAxis->scaleRange(1.025, p->xAxis->range().center());
    p->yAxis->scaleRange(1.1, p->yAxis->range().center());

    // make axis rects' left side line up:
    QCPMarginGroup *group = new QCPMarginGroup(p);
    p->axisRect()->setMarginGroup(QCP::msLeft|QCP::msRight, group);
    p->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    m_hCursor = new QCPItemLine(p);
    m_vCursor = new QCPItemLine(p);
    m_trendLine = new QCPItemLine(p);
    pel.SetPenGrey(m_dark, m_hCursor);
    pel.SetPenGrey(m_dark, m_vCursor);
    pel.SetPenGrey(m_dark, m_trendLine);

    p->addItem(m_vCursor);
    p->addItem(m_hCursor);
    p->addItem(m_trendLine);


    // Indicator plot
    if (confPlot.TECHS)
    {
        m_techRect = SetupTechs(p, strat, simTS, d);
        m_techRect->setMarginGroup(QCP::msLeft|QCP::msRight, group);
    }
}

void MyMainWindow::setupBaustelle(QCustomPlot *p, const IPeriod & period, const IStrategy & strat, const ISimulatorTS & simTS, const PlotDataBase & d)
{
    try
    {
        const Timer timer;
        demoName = "Meine Baustelle";
        p->legend->setVisible(false);
        p->setNoAntialiasingOnDrag(true);
        double binSize = period.GetNumSeconds();

        gcfg.SIMUL_VERBOSE = true;
        if (m_training)
        {
            gcfg.SIMUL_VERBOSE = false;
        }

        if (m_mons.m_barNum == 0)
            m_i = d.GetSz() * m_mons.m_percentBars / 100;
        else if (m_mons.m_barNum > 0)
            m_i = m_mons.m_barNum;
        else
            m_i = d.GetSz() + m_mons.m_barNum;

        setupVisuals(p, period, strat, simTS, d, binSize);
        /// TODO: Restore
        //const PlotData * dBig = dynamic_cast<const PlotData*>(&d);
        const PlotData * dBig = nullptr;
        if (dBig)
        {
            setupVisualsBig(p, period, strat, *dBig);
        }

        p->rescaleAxes();
        //p->setBackground(Qt::black);
        LOGL << "Took " << timer.GetElapsedSeconds() << "s\n";
        //throw EnjoLib::ExceptRuntimeError("Test");
    }
    catch (exception & ex)
    {
        qDebug() << "\n\nEXCEPTION!\n";
        qDebug() << ex.what();
        throw EnjoLib::ExceptRuntimeError(ex.what());
    }
}
