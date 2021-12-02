#include "pch_qt.h"

#include "MyMainWindow.h"
#include "ui_mainwindow.h"
//#include "TrainerHandler.h"
//#include "Screenshot.h"
//#include "ScreenshotsScaleUp.h"
//#include <StrategyFactorySymbols.h>
#include <StrategyFactoryName.h>
//#include <StrategyFactory.h>
#include "SymbolFactoryAbstract.h"
#include <StrategyFactoryDummy.h>
#include <SymbolFactoryClean.h>
#include "StrategyType.h"
#include "StrategyTypeEnum.h"
#include "ISymbol.h"
#include "StatsMedianSplit.h"
#include "Util.h"
#include "PlotDataBase.h"
#include "IPeriod.h"
#include "IStrategy.h"

#include <ConfigMan.h>
#include <ConfigSym.h>
#include <ConfigTF2.h>
#include <ConfigQT.h>
#include <ConfigOpti.h>
//#include <ConfigGlob.h>

#include <Util/CoutBuf.hpp>

using namespace std;
using namespace EnjoLib;

/// relPar can be +1, -1, 0 or 2
int MyMainWindow::HandleRelativeParUpdate(int relPar, int * relMember)
{
    int prev = 0;
    if (relPar == 0)
        *relMember = 0;
    else if (relPar == 2)
    {}
    else
    {
        prev = *relMember; // backup
        *relMember += (relPar > 0 ? + 1 : -1);
    }
    return prev;
}

void MyMainWindow::Reload(const Monster & monst, int mode, int relPeriod, int relShift, int relSymbol)
{
    ELO
    int prevPeriod = HandleRelativeParUpdate(relPeriod, &m_relPeriod);
    int prevShift  = HandleRelativeParUpdate(relShift,  &m_relShift);
                     HandleRelativeParUpdate(relSymbol, &m_relSymbol);

    m_regressLineUser.clear();

    EnjoLib::Str symName = "AUDUSD-min";
    EnjoLib::Str periodName = "h2";
    StrategyType stratType = StrategyFactory::Type::STRA_SR_BRK;

    gcfgMan.Read();
    ConfigSym * pconf = gcfgMan.cfgSym.get();
    const ConfigTF2 & confTF2 = *gcfgMan.cfgTF2;
    //const ConfigOpti & confOpti = *gcfgMan.cfgOpti;
    try
    {
        //LOG << "Reading config" << Endl;
        stratType =     pconf->GetStrat();
        symName =       pconf->symbol;
        periodName =    pconf->period;
        //m_percentBars = pconf->percentBars;
        //m_barNum =      pconf->barNum;
    }
    catch(...)
    {
        LOGL << "Couldn't read config\n";
        exit(1);
    }

    if (mode == 3 || m_training)
    {
        m_training = true;
        /// TODO: Restore
        //TrainerHandler().Handle(this, confTF2, pconf, mode,
        //                        monst.m_screenShotSymbol, monst.m_screenShotPeriod, monst.m_screenShotOutDir);
    }
    else
    if ((0 < mode && mode < 3) || (mode  == 4))
    {
        /// TODO: Restore
        //Screenshot().Handle(this, confTF2, pconf, mode,
        //                    monst.m_screenShotSymbol, monst.m_screenShotPeriod, monst.m_screenShotOutDir);
    }
    else
    if ((5 <= mode && mode <= 6))
    {
        /// TODO: Restore
        //ScreenshotsScaleUp().Handle(this, mode, monst.m_screenShotSymbol, monst.m_screenShotPeriod,
        //                            monst.m_screenShotOutDir, monst.m_dataInputFileName);
    }
    if (mode == 0)
    {
        EnjoLib::Str cursorDateSignal;
        if (m_relPeriod == 0 && m_relShift == 0 && m_relSymbol == 0)
        {
            cursorDateSignal = gcfgMan.cfgQT->dateTime;
        }

        if (m_relSymbol != 0)
        {
            /// TODO: Restore
            /*
            const auto & symbols = StrategyFactorySymbols().Create(stratType);
            symName = symbols.at(m_relSymbol % symbols.size());
            LOGL << "Rel symbol = " << m_relSymbol << ", sym = " << symName << Nl;
            */
        }
        if (m_relPeriod != 0)
        {
            try
            {
                const EnjoLib::Str & periodNameNext = Monster::FindNextPeriodIndex(*m_mons.m_symFact, confTF2, pconf, symName, periodName, m_relPeriod);
                if (periodNameNext == periodName)
                {
                    m_relPeriod = prevPeriod; // Rollback
                    return; // No changes needed. Return.
                }
                periodName = periodNameNext;
                }
            catch (exception & ex)
            {
                Util::HandleException(ex);
            }
        }
        if (m_relShift != 0)
        {
            if (not pconf->ShiftRange(m_relShift))
            {
                m_relShift = prevShift;
                return;
            }
        }

        LOG << "PlotData" << Endl;
        try
        {
            const QString & symPerName = Util::FormatSymPer(symName, periodName);
            m_mons = monst;
            /// TODO: Restore the original factories
            m_mons.SetStratFactory(new StrategyFactoryDummy());
            m_mons.SetSymFactory  (new SymbolFactoryClean());
            if (not m_mons.IsValid())
            {
                setWindowTitle("Loading ... " + symPerName);
                m_mons.Reload(symName, periodName, stratType, mode, m_relPeriod, m_relShift, m_relSymbol);
            }
            LOG << "PlotDataEnd" << Endl;
            if (not cursorDateSignal.empty())
            {
                //DateInt dateSig = TradeUtil().SigIdUnderscore2DateInt(cursorDateSignal);
                //m_barNum = - period.GetCandles().GetIndex(dateSig) - 1; // bad for debugging
            }
            setWindowTitle("Loading ... " + symPerName);

            LOG << "Got symbols" << Endl;
            setupWindow();

            LOG << "Setup baustelle" << Endl;

            const IPeriod & period = m_mons.m_symbol->GetPeriod(m_mons.m_periodName); /// TODO: a getter for random bars
            const IStrategy & strat = *m_mons.m_strategy;
            const Str & stratName = StrategyFactoryName().Create(strat.GetType());


            setupBaustelle(GetQCP(), period, strat, *m_mons.m_d);
            setWindowTitle(symPerName + ": " + stratName.c_str());
            ui->customPlot->replot();
            m_mons.reg.past = period.Len();

            //resize(1160, 700); // laptop

            const StatsMedianSplit statMedSplit;
            statMedSplit.Stats(period); /// Bottleneck
        }
        catch (exception & ex)
        {
            //exit(1);
            Util::HandleException(ex);
        }


    }
/*
    EnjoLib::Str symName = "AUDUSD-min";
    EnjoLib::Str periodName = "h2";
    StrategyType stratType = StrategyFactory::Type::STRA_SR_BRK;
    //ConfigSym conf;
    //
    gcfgMan.Read();
    ConfigSym * pconf = gcfgMan.cfgSym.get();
    try
    {
        //LOG << "Reading config" << Endl;
        stratType = pconf->GetStrat();
        symName = pconf->symbol;
        periodName = pconf->period;
        m_percentBars = pconf->percentBars;
        m_barNum = pconf->barNum;
    }
    catch(...)
    {
        LOG << "Couldn't read config\n";
        exit(1);
    }

    reg.past = reg.future = 0; m_regressLineUser.clear();

    ConfigTF2 & confTF2 = *gcfgMan.cfgTF2;
    const ConfigOpti & confOpti = *gcfgMan.cfgOpti;

    if (confOpti.OPTIMIZER == 1)
        gcfg.OPTI_USE = false;
    else if (confOpti.OPTIMIZER == 2)
        gcfg.OPTI_USE = true;
    else if (confOpti.OPTIMIZER == 0)
        gcfg.OPTI_USE = false;

    if (mode == 3 || m_training)
    {
        m_training = true;
        TrainerHandler().Handle(this, confTF2, pconf, mode, m_screenShotSymbol, m_screenShotPeriod, m_screenShotOutDir);
    }
    else
    if ((0 < mode && mode < 3) || (mode  == 4))
    {
        Screenshot().Handle(this, confTF2, pconf, mode, m_screenShotSymbol, m_screenShotPeriod, m_screenShotOutDir);
    }
    else
    if ((5 <= mode && mode <= 6))
    {
        ScreenshotsScaleUp().Handle(this, mode, m_screenShotSymbol, m_screenShotPeriod, m_screenShotOutDir, m_dataInputFileName);
    }
    else
    {
        EnjoLib::Str cursorDateSignal;
        if (m_relPeriod == 0 && m_relShift == 0 && m_relSymbol == 0)
        {
            cursorDateSignal = gcfgMan.cfgQT->dateTime;
        }

        if (m_relSymbol != 0)
        {
            const auto & symbols = StrategyFactorySymbols().Create(stratType);
            symName = symbols.at(m_relSymbol % symbols.size());
            LOG << "Rel symbol = " << m_relSymbol << ", sym = " << symName << Endl;
        }
        if (m_relPeriod != 0)
        {
            try
            {
                EnjoLib::Str periodNameNext = FindNextPeriodIndex(confTF2, pconf, symName, periodName, m_relPeriod);
                if (periodNameNext == periodName)
                {
                    m_relPeriod = prevPeriod; // Rollback
                    return; // No changes needed. Return.
                }
                periodName = periodNameNext;
                }
            catch (exception & ex)
            {
                HandleException(ex);
            }
        }
        if (m_relShift != 0)
        {
            if (not pconf->ShiftRange(m_relShift))
            {
                m_relShift = prevShift;
                return;
            }
        }
        QString symPerName = Util::FormatSymPer(symName, periodName);
        setWindowTitle("Loading ... " + symPerName);

        //m_symbol = LoadSymbolFromFile();
        const SymbolFactory symFact;
        //m_symbol = MainTester(symFact, &confTF2, pconf).GetSymbol(symName, VecStr {periodName});
        m_symbol = m_mainTester->GetSymbol(symName, VecStr {periodName});
        m_periodName = periodName;
        LOG << "Got symbols" << Endl;
        setupWindow();
        LOG << "setupWindow" << Endl;
        const IPeriod & periodOrig = m_symbol->GetPeriod(m_periodName);
        EnjoLib::UniquePtr<IPeriod> periodPtr;
        if (confTF2.RANDOM_BARS)
        {
            const PeriodRandomizer perRand(periodOrig, confTF2.RANDOM_BARS_SEED);
            const Ticks & ticksRandomized = perRand.Randomize(confTF2.GetRandomBarsPercent(), false);
            periodPtr = PeriodFactory().Copy(periodOrig);
            periodPtr->Feed(ticksRandomized);
            periodPtr->CalcTech();
        }
        const IPeriod & period = confTF2.RANDOM_BARS ? (*periodPtr) : periodOrig;

        LOG << "Period len = " << period.Len() << Endl;

        m_strategy.reset();
        m_strategy = StrategyFactoryConcr().Create(stratType, period);
        const IStrategy & strat = *m_strategy;
        m_simulator    = SimulatorFactory().CreateStandard(strat, 0, confTF2.TRAIN, gcfg.MIN_SCORE);
        m_simulatorBet = SimulatorFactory().CreateBet(period);
         //= EnjoLib::UniquePtr<SimulatorBet>(new SimulatorBet(period));
        m_labelQT = EnjoLib::UniquePtr<LabelQT>(new LabelQT(period));

        LOG << "PlotData" << Endl;
        try
        {
            LOG << "Pre Data" << Endl;
            m_d = EnjoLib::UniquePtr<PlotData>(new PlotData(period, strat));
            LOG << "BufSSA!" << Endl;
            //m_d->GetBuf(BUF_SSA_OSCI);
            LOG << "PlotDataEnd" << Endl;
            if (not cursorDateSignal.empty())
            {
                //DateInt dateSig = TradeUtil().SigIdUnderscore2DateInt(cursorDateSignal);
                //m_barNum = - period.GetCandles().GetIndex(dateSig) - 1; // bad for debugging
            }
            LOG << "Setup baustelle" << Endl;
            setupBaustelle(GetQCP(), period, strat, *(m_d.get()));
            setWindowTitle(symPerName);
            ui->customPlot->replot();
            reg.past = period.Len();

            //resize(1160, 700); // laptop
        }
        catch (exception & ex)
        {
            //exit(1);
            HandleException(ex);
        }

        const StatsMedianSplit statMedSplit;
        statMedSplit.Stats(period);
    }
    */
}
