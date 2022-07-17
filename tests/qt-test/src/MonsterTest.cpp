
#include "Monster.h"
#include "StrategyType.h"
#include "StrategyTypeEnum.h"
#include "ConfigMan.h"
#include "ConfigQT.h"
#include "ConfigQTPlot.h"
#include "ConfigSym.h"
#include "DataSrcType.h"
#include "PlotDataBase.h"

#include <StrategyFactoryDummy.h>
#include <SymbolFactoryClean.h>
#include <SimulatorFactoryTSImpl.h>

#include <UnitTest++/UnitTest++.h>

using namespace EnjoLib;

TEST(Monster_1)
{
    //gcfgMan.cfgQTPlot->TECHS = false; // It was a way for tsqsim to work
    gcfgMan.cfgSym->SetDataSrc(DataSrcType::MONERO); /// TODO: test also generated data
    Monster mon;
    SafePtr<StrategyFactoryAbstract> factStrat(new StrategyFactoryDummy());
    SafePtr<SymbolFactoryAbstract> factSym(new SymbolFactoryClean());
    SafePtr<SimulatorFactoryAbstract> factSim(new SimulatorFactoryTSImpl());
    mon.SetFactories(factSym.get()
    , factStrat.get()
    , factSim.get());
    const int mode = 0;
    mon.Reload("TXTS", "h12", StrategyFactory::Type::STRA_LIVE, mode);
    CHECK(mon.m_d->GetSz() > 0);
}
