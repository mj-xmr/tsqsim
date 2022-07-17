#include "Monster.h"
#include "UtilBare.h"
#include "LabelQT.h"
#include "PlotDataScreenshot.h"
#include <BufferType.h>
#include "BufferVecType.h"
#include "IBufferCandles.h"
#include <TradeUtil.h>
#include <IMainTester.h>
#include <IPeriod.h>
#include <IStrategy.h>
#include <ConfigMan.h>
#include <ConfigSym.h>
#include <ConfigTF2.h>
#include <ConfigQT.h>
#include "ConfigQTPlot.h"
#include <ConfigOpti.h>
#include <ConfigGlob.h>
#include "ISymbol.h"
#include "OptiType.h"
#include "Buffer.h"
#include <SymbolFactoryAbstract.h>
#include <StrategyFactoryAbstract.h>
#include <SimulatorFactoryAbstract.h>
#include "DataSrcType.h"

//#include <StrategyFactory.h>
//#include <StrategyFactorySymbols.h>
//#include "StrategyType.h"
//#include "StrategyTypeEnum.h"

//#include <SymbolFactory.h>
//#include <SimulatorFactory.h>
//#include <SimulatorBetFactory.h>
//#include "ISimulatorStd.h"
#include "PeriodRandomizer.h"
//#include "PeriodFactory.h"
//#include <SimulatorBet.h>

#include <Ios/Ofstream.hpp>
#include <Util/FileUtils.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Timer.hpp>
#include <Template/Array.hpp>
#include <Template/UniquePtr.hpp>


using namespace std;
using namespace EnjoLib;

Monster::~Monster(){}
Monster:: Monster(){}
Monster:: Monster(const EnjoLib::Str & screenShotOutDir, const EnjoLib::Str & screenShotSymbol,
                  const EnjoLib::Str & screenShotPeriod, const EnjoLib::Str & dataInputFileName)
: m_screenShotOutDir(screenShotOutDir)
, m_screenShotSymbol(screenShotSymbol)
, m_screenShotPeriod(screenShotPeriod)
, m_dataInputFileName(dataInputFileName)
{
}

void Monster::InitVirt()
{

}

void Monster::Reload(const EnjoLib::Str & symName, const EnjoLib::Str & periodName, const StrategyType & stratType,
                     int mode, int relPeriod, int relShift, int relSymbol)
{
    ELO
    //gcfgMan.Read(); WRONG
    //m_symFact = UniquePtr<SymbolFactoryAbstract>(new SymbolFactory());
    m_mainTester = UniquePtr<IMainTester>(IMainTester::Create(*m_symFact, gcfgMan.cfgTF2.get(), gcfgMan.cfgSym.get()).release());

    //StrategyType stratType = StrategyFactory::Type::STRA_SR_BRK;
    //ConfigSym conf;
    //
    /*
    gcfgMan.Read();
    ConfigSym * pconf = gcfgMan.cfgSym.get();
    try
    {
        //LOG << "Reading config" << Endl;
        stratType =     pconf->GetStrat();
        //symName =       pconf->symbol;
        //periodName =    pconf->period;
        m_percentBars = pconf->percentBars;
        m_barNum =      pconf->barNum;
    }
    catch(...)
    {
        LOG << "Couldn't read config\n";
        exit(1);
    }
    */
    reg.past = reg.future = 0;

    ConfigTF2 & confTF2 = *gcfgMan.cfgTF2;
    const ConfigOpti & confOpti = *gcfgMan.cfgOpti;
    //gcfg.OPTI_USE = confOpti.IsOperationType(OptiType::OPTI_TYPE_USE);

    if (mode == 0)
    {
        try
        {
            const Timer timer;
            //m_symbol = LoadSymbolFromFile();
            //const SymbolFactory symFact;
            //m_symbol = MainTester(symFact, &confTF2, pconf).GetSymbol(symName, VecStr {periodName});
            VecStr pers; pers.push_back(periodName);
            m_symbol = EnjoLib::SharedPtr<ISymbol>(m_mainTester->GetSymbol(symName, pers).release());
            m_periodName = periodName;
            LOG << "Got symbols " << timer.GetElapsedSeconds() << Endl;
            //setupWindow();
            LOG << "setupWindow " << timer.GetElapsedSeconds() << Endl;
            const IPeriod & periodOrig = m_symbol->GetPeriod(m_periodName);
            const IPeriod & period = periodOrig;
            /*
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
            */

            LOG << "Period len = " << period.Len() << " " << timer.GetElapsedSeconds() << Endl;

            LOG << "Strategy " << timer.GetElapsedSeconds() << Endl;
            m_strategy.reset();
            m_strategy = EnjoLib::SharedPtr<IStrategy>(m_stratFact->Create(stratType, period).release());
            const IStrategy & strat = *m_strategy;

            LOG << "Simulators " << timer.GetElapsedSeconds() << Endl;
            m_simFact->strat = m_strategy.get();
            m_simulatorGeneric = SharedPtr<ISimulator>(m_simFact->Create().release());
            //m_simulatorGeneric = SharedPtr<ISimulator>(m_simulatorGeneric->CloneRaw());
            /// TODO: Reenable, but rather through generic simulator
            //m_simulator    = EnjoLib::SharedPtr<ISimulatorStd>(SimulatorFactory().CreateStandard(strat, 0, confTF2.TRAIN, gcfg.MIN_SCORE).release());
            //m_simulatorBet = EnjoLib::SharedPtr<ISimulatorBet>(SimulatorBetFactory().CreateBet(period).release());
             //= EnjoLib::UniquePtr<SimulatorBet>(new SimulatorBet(period));

            LOG << "Labels " << timer.GetElapsedSeconds() << Endl;
            m_labelQT = EnjoLib::UniquePtr<LabelQT>(new LabelQT(period));

            LOG << "PlotData " << timer.GetElapsedSeconds() << Endl;

            LOG << "Pre Data " << timer.GetElapsedSeconds() << Endl;
            /// TODO: restore
            //m_d = EnjoLib::UniquePtr<PlotData>(new PlotData(period, strat));
            m_d = EnjoLib::UniquePtr<PlotDataBase>(new PlotDataScreenshot(period));
            LOG << "Init bufs " << timer.GetElapsedSeconds() << Endl;
            InitBufs(period);
            LOG << "Init bufs ended " << timer.GetElapsedSeconds() << Endl;
            //if (not cursorDateSignal.empty())
            {
                //DateInt dateSig = TradeUtil().SigIdUnderscore2DateInt(cursorDateSignal);
                //m_barNum = - period.GetCandles().GetIndex(dateSig) - 1; // bad for debugging
            }
            //LOG << "Setup baustelle" << Endl;
            //setupBaustelle(GetQCP(), period, strat, *(m_d.get()));
            //setWindowTitle(symPerName);
            //ui->customPlot->replot();
            reg.past = period.Len();

            //resize(1160, 700); // laptop
        }
        catch (exception & ex)
        {
            //exit(1);
            UtilBare::HandleException(ex);
        }

        //const StatsMedianSplit statMedSplit;
        //statMedSplit.Stats(period);
    }

    m_isValid = true;
}

/// Has to be done before setting up QT, else it would lead to QT init failures.
void Monster::InitBufs(const IPeriod & per) const
{
    const ConfigQT & confQT = *gcfgMan.cfgQT;
    const ConfigQTPlot & confQTPlot = *gcfgMan.cfgQTPlot;

    if (per.HasBufs())
    {
        for (int bufId : {confQT.buf1, confQT.buf2, confQT.buf3})
        {
            per.GetBuf(BufferType(bufId));
        }
        per.GetBufVec(BufferVecType(confQT.bufRainbow));
    }
}

/*
    {
        vector<BufferType> techs;
        techs.push_back(EnjoLib::MakePair(BufferType(confQT.buf1), QPen(Qt::blue)));
        techs.push_back(EnjoLib::MakePair(BufferType(confQT.buf2), QPen(Qt::darkGreen)));
        techs.push_back(EnjoLib::MakePair(BufferType(confQT.buf3), QPen(Qt::red)));

        const auto & bufs = strat.GetPeriod().GetBufVec(BufferVecType(confQT.bufRainbow));
*/

        /*
        bool writeCloses = true;
        writeCloses = false;

        if (writeCloses)
        {
            EnjoLib::Str baseDir = "../scripts/";
            Ofstream fopens(baseDir + period.GetSymbolPeriodId() + "-opens.dat");
            Ofstream fcloses(baseDir + period.GetSymbolPeriodId() + "-closes.dat");
            Ofstream fatr   (baseDir + period.GetSymbolPeriodId() + "-atr.dat");
            Filesystem().CreateDirIfNotExists(baseDir);
            fopens << "\"Opens\"\n";
            fcloses << "\"Closes\"\n";
            fatr    << "\"ATR\"\n";
            Buffer atr = period.GetBuf(BUF_ATR);
            for (int i = period.Len() - 1; i >= 0; --i) //gcfg.PERIOD_TECH_STANDARD
            {
                const Candle & c = period.GetCandles()[i];
                //fcloses     << c.GetDate() << " " << c.GetClose() << Endl;
                //fatr        << c.GetDate() << " " << atr[i] << Endl;
                fopens  << c.GetOpen() << '\n';
                fcloses << c.GetClose() << '\n';
                fatr    << atr[i] << '\n';

                //fopens  << c.GetOpen() / atr[i] << '\n';
                //fcloses << c.GetClose() / atr[i] << '\n';

            }
        }
        */

EnjoLib::Str Monster::FindNextPeriodIndex(const SymbolFactoryAbstract & symFact, const ConfigTF2 & confTF2, const ConfigSym * pconf, EnjoLib::Str symName, EnjoLib::Str periodName, int relPeriod)
{
    const CorPtr<IMainTester> mtest = IMainTester::Create(symFact, &confTF2, pconf);
    VecStr pers1; pers1.push_back("d");
    Corrade::Containers::Pointer<ISymbol> symbolProxy = mtest->GetSymbol(symName, pers1);
    auto pers = symbolProxy->GetPeriodsAll();
    for (int i = 0; i < (int)pers.size(); ++i)
    {
        const IPeriod* per = pers.at(i);
        if (per->GetName() == periodName)
        {
            int j = i + relPeriod;
            if (j < 0 || j >= (int)pers.size())
                return periodName; // Error - moved outside boundaries

            EnjoLib::Str periodNameNext = pers.at(j)->GetName();
            return periodNameNext;
        }
    }
    return periodName;
}

bool Monster::IsValid() const
{
    return m_isValid;
}

void Monster::SetFactories(const Monster & mons)
{
    SetFactories(mons.m_symFact, mons.m_stratFact, mons.m_simFact);
    m_simulTxt = mons.m_simulTxt;
    m_smallTxt = mons.m_smallTxt;
}

void Monster::SetFactories(  SymbolFactoryAbstract * pSymFact,
                            StrategyFactoryAbstract * pStratFact,
                            SimulatorFactoryAbstract  * pSimFact
                                                          )
{
    m_symFact = pSymFact;
    m_stratFact = pStratFact;
    m_simFact = pSimFact;
}

/*
void Monster::SetSymFactory(SymbolFactoryAbstract * pSymFact)
{
    //m_symFact = UniquePtr<SymbolFactoryAbstract>(new SymbolFactory());
    //m_symFact = UniquePtr<SymbolFactoryAbstract>(pSymFact);
    //m_symFact = SharedPtr<SymbolFactoryAbstract>(pSymFact);
    m_symFact = pSymFact;
}

void Monster::SetStratFactory(StrategyFactoryAbstract * pStratFact)
{
    //m_stratFact = UniquePtr<StrategyFactoryAbstract>(pStratFact);
    m_stratFact = pStratFact;
}
*/
