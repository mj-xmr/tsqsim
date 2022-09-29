
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

#include <Util/CoutBuf.hpp>
#include <UnitTest++/UnitTest++.h>

using namespace EnjoLib;

TEST(Monster_1)
{
    //gcfgMan.cfgQTPlot->TECHS = false; // It was a way for tsqsim to work
    gcfgMan.cfgSym->SetDataSrc(DataSrcType::MONERO); /// TODO: test also generated data
    Monster mon;
    SafePtr<StrategyFactoryAbstract>    factStrat(new StrategyFactoryDummy());
    SafePtr<SymbolFactoryAbstract>      factSym(new SymbolFactoryClean());
    SafePtr<SimulatorFactoryAbstract>   factSim(new SimulatorFactoryTSImpl());
    mon.SetFactories(factSym.get()
    , factStrat.get()
    , factSim.get());
    const int mode = 0;
    mon.Reload("TXTS", "h12", StrategyFactory::Type::STRA_LIVE, mode);
    const int sz_h12 = mon.m_d->GetSz();
    CHECK(sz_h12 > 0);
    mon.Reload("TXTS", "h8", StrategyFactory::Type::STRA_LIVE, mode);
    const int sz_h8 = mon.m_d->GetSz();
    CHECK(sz_h8 > 0);
    CHECK(sz_h8 > sz_h12);
    mon.Reload("TXTS", "d", StrategyFactory::Type::STRA_LIVE, mode);
    const int sz_d = mon.m_d->GetSz();
    mon.Reload("TXTS", "w", StrategyFactory::Type::STRA_LIVE, mode);
    const int sz_w = mon.m_d->GetSz();
    LOGL << "Sizes of series: d = " << sz_d << ", w = " << sz_w << Nl;
    CHECK(sz_w > 0);
    CHECK(sz_w < sz_h12);
    CHECK(sz_w < sz_d);
}
