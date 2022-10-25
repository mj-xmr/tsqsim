//#include "pch_base.h"

#include "Symbol.h"
#include "IPeriod.h"
#include "Spreads.h"
#include "ConfigMan.h"
#include "ConfigTF2.h"
#include "PeriodRandomizer.h"
#include "TradeUtil.h"
//#include "PeriodClean.h"
//#include "PeriodBase.h"

#include <Util/CoutBuf.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/Except.hpp>
#include <Template/Array.hpp>

#include <STD/VectorCpp.hpp>

using namespace std;
using namespace EnjoLib;

//template class Symbol<PeriodBase>; // Just include this .cpp file in a factory
//template class Symbol<PeriodClean>;

//const bool Symbol<T>::ALLOW_HIGHER = true;
template <class T> const bool Symbol<T>::ALLOW_HIGHER = false;
//template <class T> const bool Symbol<T>::ALLOW_HIGHER = true;
template <class T> const int Symbol<T>::MIN_PERIOD_MINUTES = 60; // 120

template <class T>
Symbol<T>::Symbol(const EnjoLib::Str & name, const VecStr & periodNames, bool isMetaTrader, float spread)
: m_name(CharManipulations().ToUpper(name))
, m_nameCurPrefix(TradeUtil().CutSymbolTestingPrefix(GetName()))
, m_periodNames(periodNames)
, m_ticks(ITicks::Create())
, pm1 (*this)
, pm5 (*this)
, pm15(*this)
, pm30(*this)
, ph1 (*this)
, ph2 (*this)
, ph4 (*this)
, ph8 (*this)
, ph12(*this)
, pd  (*this)
, pw  (*this)
, pm  (*this)
, m_isMetaTrader(isMetaTrader)
, m_spread(spread)
{
    for (Str & pname : m_periodNames)
    {
        pname = CharManipulations().ToLower(pname);
    }
    InitAllowedPeriods();
}

template <class T>
void Symbol<T>::InitAllowedPeriods()
{
    std::vector<const IPeriod*> periods;
    for (const IPeriod * p : GetPeriodsAll())
    {
        if (IsPeriodAllowedStr(p))
        {
            //cout << "Symbol: Adding " << p->GetName() << endl;
            periods.push_back(p);
        }
    }
    m_perAllowed = periods;
}

template <class T>
EnjoLib::Array<const IPeriod*> Symbol<T>::GetPeriods() const
{
    std::vector<const IPeriod*> periods;
    bool allowedHigher = false;
    for (const IPeriod * p : GetPeriodsAll())
    {
        if (p->GetNumTicks() >= MIN_PERIOD_MINUTES)
        {
            allowedHigher = ALLOW_HIGHER;
        }
        if (IsPeriodAllowed(p) || allowedHigher)
        {
            //cout << "Symbol: Adding " << p->GetName() << endl;
            periods.push_back(p);
           // allowedHigher = true;
           //allowedHigher = false;
        }
    }

    return periods;
}

template <class T>
EnjoLib::Array<IPeriod*> Symbol<T>::GetPeriodsRW()
{
    std::vector<IPeriod*> periods;
    bool allowedHigher = false;
    for (IPeriod * p : GetPeriodsRWAll())
    {
        if (p->GetNumTicks() >= MIN_PERIOD_MINUTES)
        {
            allowedHigher = ALLOW_HIGHER;
        }
        if (IsPeriodAllowed(p) || allowedHigher)
        {
            periods.push_back(p);
            //allowedHigher = true;
            //allowedHigher = false;
        }
    }

    return periods;
}

template <class T>
bool Symbol<T>::IsPeriodAllowed(const IPeriod * p) const
{
    if (m_periodNames.empty())
        return true;
    if (m_perAllowed.Contains(p))
        return true;
    return false;
}

template <class T>
bool Symbol<T>::IsPeriodAllowedStr(const IPeriod * p) const
{
    if (m_periodNames.empty())
        return true;
    if (m_periodNames.Contains(p->GetName()))
        return true;
    return false;
}

template <class T>
EnjoLib::Array<const IPeriod*> Symbol<T>::GetPeriodsAll() const
{
    std::vector<const IPeriod*> periods;
    periods.push_back(&pm1);
    periods.push_back(&pm5);
    periods.push_back(&pm15);
    periods.push_back(&pm30);
    periods.push_back(&ph1);
    periods.push_back(&ph2);
    periods.push_back(&ph4);
    periods.push_back(&ph8);
    periods.push_back(&ph12);
    periods.push_back(&pd);
    periods.push_back(&pw);
    periods.push_back(&pm);

    return periods;
}

template <class T>
std::vector<IPeriod*> Symbol<T>::GetPeriodsRWAll()
{
    std::vector<IPeriod*> periods;
    for (const IPeriod * p : GetPeriodsAll())
    {
        periods.push_back(const_cast<IPeriod *>(p));
    }
    return periods;
}


template <class T>
void Symbol<T>::Feed(const ITicks & ticks, bool updateTech)
{
    for (const Tick & tick : ticks)
    {
        Feed(tick);
    }
}

template <class T>
void Symbol<T>::Feed(const Tick & tick, bool updateTech)
{
    for(IPeriod * period : GetPeriodsRW())
    {
        //LOGL << "Feeding " << period->GetName() << Nl;
        period->Feed(tick, updateTech);
    }
}

template <class T>
void Symbol<T>::CalcTech()
{
    for(IPeriod * period : GetPeriodsRW())
    {
        const ConfigTF2 & confTF2 = *gcfgMan.cfgTF2.get();
        if (confTF2.RANDOM_BARS)
        {
            const PeriodRandomizer perRand(*period, confTF2.RANDOM_BARS_SEED);
            const auto & ticksRandomized = perRand.Randomize(confTF2.GetRandomBarsPercent(), false);
            period->SetCandles(VecCan{});
            for (const Tick & t : *ticksRandomized)
                period->Feed(t);
        }
        period->CalcTech();
    }
}


template <class T>
unsigned Symbol<T>::GetSizeAll() const
{
    unsigned sumLen = 0;
    for(const IPeriod * period : GetPeriods())
    {
        sumLen += period->Len();
    }
    return sumLen;
}

template <class T>
void Symbol<T>::UpdateTech()
{
    for(IPeriod * period : GetPeriodsRW())
        period->UpdateTech();
}

template <class T>
void Symbol<T>::FinalizeCandle()
{
    for(IPeriod * period : GetPeriodsRW())
        period->FinalizeCandle();
}

template <class T>
void Symbol<T>::LimitData(int maxLatestBars)
{
    for(IPeriod * period : GetPeriodsRW())
        period->LimitData(maxLatestBars);
}

template <class T>
const IPeriod & Symbol<T>::GetPeriod(const EnjoLib::Str & name) const
{
    for(const IPeriod * period : GetPeriods())
        if (period->GetName() == name)
            return *period;
    throw EnjoLib::ExceptInvalidArg("Couldn't find period = " + name);
}

template <class T>
IPeriod & Symbol<T>::GetPeriodRW(const EnjoLib::Str & name)
{
    for(IPeriod * period : GetPeriodsRW())
        if (period->GetName() == name)
            return *period;
    throw EnjoLib::ExceptInvalidArg("Couldn't find period = " + name);
}

template <class T>
bool Symbol<T>::HasPeriod(const EnjoLib::Str & name) const
{
    for(const IPeriod * period : GetPeriods())
        if (period->GetName() == name)
            return true;
    return false;
}

template <class T>
const IPeriod & Symbol<T>::GetPeriodPrev(const IPeriod & periodSelected) const
{
    EnjoLib::Str name = periodSelected.GetName();
    EnjoLib::Array<const IPeriod*> periods = GetPeriods();
    for(unsigned i = 0; i < periods.size(); ++i)
        if (periods[i]->GetName() == name && i > 0)
            return *periods[i-1];
    throw EnjoLib::ExceptInvalidArg("Couldn't find period smaller than = " + name);
}

template <class T>
bool Symbol<T>::HasPeriodPrev(const IPeriod & periodSelected) const
{
    EnjoLib::Str name = periodSelected.GetName();
    EnjoLib::Array<const IPeriod*> periods = GetPeriods();
    for(unsigned i = 0; i < periods.size(); ++i)
        if (periods[i]->GetName() == name && i > 0)
            return true;
    return false;
}

template <class T>
const IPeriod & Symbol<T>::GetPeriodNext(const IPeriod & periodSelected) const
{
    EnjoLib::Str name = periodSelected.GetName();
    EnjoLib::Array<const IPeriod*> periods = GetPeriods();
    for(unsigned i = 0; i < periods.size(); ++i)
        if (periods[i]->GetName() == name && i < periods.size() - 1)
            return *periods[i+1];
    throw EnjoLib::ExceptInvalidArg("Couldn't find period larger than = " + name);
}

template <class T>
bool Symbol<T>::HasPeriodNext(const IPeriod & periodSelected) const
{
    EnjoLib::Str name = periodSelected.GetName();
    EnjoLib::Array<const IPeriod*> periods = GetPeriods();
    for(unsigned i = 0; i < periods.size(); ++i)
        if (periods[i]->GetName() == name && i < periods.size() - 1)
            return true;
    return false;
}

template <class T>
void Symbol<T>::FilterPrice(const PriceFilterConfig & cfg)
{
    for(IPeriod * period : GetPeriodsRW())
        period->FilterPrice(cfg);
}

template <class T>
void Symbol<T>::SetTicks(const ITicks & ticks)
{
    m_ticks->Set(ticks);
}

template <class T>
const EnjoLib::Str & Symbol<T>::GetName() const
{
    return m_name;
}

template <class T>
float Symbol<T>::GetSpread(double currentPrice) const
{
    if (m_spread != 0)
        return m_spread;

    return m_spreads.GetSpread(m_nameCurPrefix, currentPrice);
}
