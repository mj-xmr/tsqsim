#ifndef SYMBOL_H
#define SYMBOL_H

#include <3rdParty/stdfwd.hh>

#include "Periods.h"

#include "ISymbol.h"
#include "Spreads.h"
#include "ITicks.h"
#include "typesStr.h"

#include <Util/Str.hpp>
#include <Template/Array.hpp>

class Tick;
class IPeriod;

template <class PeriodType>
class Symbol : public ISymbol
{
public:
    Symbol(const EnjoLib::Str & name, const VecStr & periodNames = VecStr(), bool isMetaTrader = false, float spread = 0);
    virtual ~Symbol(){}

    void Feed(const Tick & tick, bool updateTech = false) override;
    void Feed(const ITicks & tick, bool updateTech = false) override;
    void CalcTech() override;
    void UpdateTech() override;
    void FinalizeCandle() override;
    void LimitData(int maxLatestBars) override;
    void FilterPrice(const PriceFilterConfig & cfg) override;
    const IPeriod & GetPeriod(const EnjoLib::Str & name) const override;
    const IPeriod & GetPeriodPrev(const IPeriod & periodSelected) const override;
    const IPeriod & GetPeriodNext(const IPeriod & periodSelected) const override;
    bool HasPeriod(const EnjoLib::Str & name) const override;
    bool HasPeriodPrev(const IPeriod & periodSelected) const override;
    bool HasPeriodNext(const IPeriod & periodSelected) const override;
    bool IsMetaTrader() const override { return m_isMetaTrader; }
    const EnjoLib::Str & GetName() const override;
    float GetSpread(double currentPrice) const override;
    unsigned GetSizeAll() const override;

    EnjoLib::Array<const IPeriod*> GetPeriods() const override;
    EnjoLib::Array<IPeriod*> GetPeriodsRW() override;
    IPeriod & GetPeriodRW(const EnjoLib::Str & name) override;
    void SetTicks(const ITicks & ticks) override;

    EnjoLib::Array<const IPeriod*> GetPeriodsAll() const override;

    const ITicks & GetTicks()    const override { return *m_ticks; }
    const IPeriod & m1()        const override { return pm1; }
    const IPeriod & m5()        const override { return pm5; }
    const IPeriod & m15()       const override { return pm15; }
    const IPeriod & m30()       const override { return pm30; }
    const IPeriod & h1()        const override { return ph1; }
    const IPeriod & h2()        const override { return ph2; }
    const IPeriod & h4()        const override { return ph4; }
    const IPeriod & h8()        const override { return ph8; }
    const IPeriod & h12()       const override { return ph12; }
    const IPeriod & d()         const override { return pd; }

private:
    void InitAllowedPeriods();
    stdfwd::vector<IPeriod*> GetPeriodsRWAll();
    bool IsPeriodAllowedStr(const IPeriod * p) const;
    bool IsPeriodAllowed(const IPeriod * p) const;

    EnjoLib::Str m_name;
    EnjoLib::Str m_nameCurPrefix;
    VecStr m_periodNames;

    CorPtr<ITicks> m_ticks;
    Minute1<PeriodType> pm1;
    Minute5<PeriodType> pm5;
    Minute15<PeriodType>pm15;
    Minute30<PeriodType>pm30;
    Hour1<PeriodType>   ph1;
    Hour2<PeriodType>   ph2;
    Hour4<PeriodType>   ph4;
    Hour8<PeriodType>   ph8;
    Hour12<PeriodType>  ph12;
    Day<PeriodType>     pd;
    EnjoLib::Array<const IPeriod*> m_perAllowed;

    Spreads m_spreads;
    bool m_isMetaTrader = false;
    float m_spread = 0;

    static const bool ALLOW_HIGHER;
    static const int MIN_PERIOD_MINUTES;
};

#endif // SYMBOL_H
