#include "pch_base.h"

#include "MainTesterUtil.h"
#include "ConfigTF2.h"
#include "ConfigSym.h"
#include "ISymbol.h"
#include "IPeriod.h"
#include "Tick.h"
#include "Ticks.h"
#include "ITicksProvider.h"
#include "PriceFilterConfig.h"

#include <Template/UniquePtr.hpp>
#include <Template/Array.hpp>

#include <STD/Ostream.hpp>
#include <STD/Algorithm.hpp>
#include <STD/VectorCpp.hpp>

using namespace std;

MainTesterUtil::MainTesterUtil(const ConfigTF2 * confTF2, ISymbol * sym, std::ostream & log)
: m_confTF2(confTF2)
, m_sym(sym)
, m_log(log)
{
}

void MainTesterUtil::FilterBySpread() const
{
    if (not m_confTF2) return;
    float spreadMulFilter = m_confTF2->SPREAD_MUL_FILTER;
    if (not m_confTF2->FILTER_PRICE)
    {
        spreadMulFilter = 0;
    }

    m_log << "Filtering '" << m_sym->GetName() << "' up by '" << spreadMulFilter << "'" << endl;

    PriceFilterConfig cfg;
    cfg.spreadMulFilter = spreadMulFilter;
    m_sym->FilterPrice(cfg);
    for (IPeriod * per : m_sym->GetPeriodsRW())
    {
        per->SetPriceFilterConfig(cfg);
    }
}

void MainTesterUtil::RestoreTicks(const ITicksProvider * tickProvider, const ConfigSym * confSym) const
{
    if (m_confTF2 && m_confTF2->SIM_USE_TICKS)
    {
        m_log << "Restoring Ticks '" << m_sym->GetName() << "'" << endl;
        CorPtr<ITicks> t = tickProvider->GetTicks(m_sym->GetName(), confSym);
        t = CorPtr<ITicks>(Filter(m_sym->GetName(), *t, confSym).release());
        m_sym->SetTicks(*t);
    }
}

CorPtr<ITicks> MainTesterUtil::Filter(EnjoLib::Str symbolName, const ITicks & ticks, const ConfigSym * confSym) const
{
    Ticks t(ticks);
    if (!confSym)
        return CorPtr<ITicks>(new Ticks(t));
    m_log << symbolName << ": Filtering" << endl;
    //t = t.FromYear(confSym->yearStart);
    //t = t.TillYear(confSym->yearEnd);
    t = t.BetweenYears(confSym->dates.yearStart, confSym->dates.yearEnd)->GetTicksView();
    t = t.FromMonth(confSym->dates.monthStart, confSym->dates.yearStart)->GetTicksView();
    t = t.TillMonth(confSym->dates.monthEnd, confSym->dates.yearEnd)->GetTicksView();
    return CorPtr<ITicks>(new Ticks(t));
}

vector<ISymbol*> MainTesterUtil::SortISymbolsGrowing(const vector<ISymbol*> & vecSyms)
{
    std::vector<ISymbol*> symbolSizes;
    for (ISymbol * sym : vecSyms)
    {
        symbolSizes.push_back(sym);
    }

    std::sort(symbolSizes.begin(), symbolSizes.end(),
              [](const ISymbol * a, const ISymbol * b) -> bool
                {
                    return a->GetSizeAll() > b->GetSizeAll();
                });
    return symbolSizes;
}
