#ifndef ISYBMOL_H
#define ISYBMOL_H

#include <3rdParty/stdfwd.hh>
#include <Util/Str.hpp>
#include <Template/ArrayFwd.hpp>

class IPeriod;
class Tick;
class ITicks;
class PriceFilterConfig;

class ISymbol
{
    public:
        ISymbol();
        virtual ~ISymbol();

        virtual void Feed(const Tick & tick, bool update = false) = 0;
        virtual void Feed(const ITicks & tick, bool update = false) = 0;
        virtual void CalcTech() = 0;
        virtual void UpdateTech() = 0;
        virtual void FinalizeCandle() = 0;
        virtual void LimitData(int maxLatestBars) = 0;
        virtual void FilterPrice(const PriceFilterConfig & cfg) = 0;
        virtual const IPeriod & GetPeriod(const EnjoLib::Str & name) const = 0;
        virtual const IPeriod & GetPeriodPrev(const IPeriod & periodSelected) const = 0;
        virtual const IPeriod & GetPeriodNext(const IPeriod & periodSelected) const = 0;
        virtual bool HasPeriod(const EnjoLib::Str & name) const = 0;
        virtual bool HasPeriodPrev(const IPeriod & periodSelected) const = 0;
        virtual bool HasPeriodNext(const IPeriod & periodSelected) const = 0;
        virtual bool IsMetaTrader() const = 0;
        virtual const EnjoLib::Str & GetName() const = 0;
        virtual float GetSpread(double currentPrice) const = 0;
        virtual unsigned GetSizeAll() const = 0;

        virtual EnjoLib::Array<const IPeriod*> GetPeriods() const = 0;
        virtual EnjoLib::Array<IPeriod*> GetPeriodsRW() = 0;
        virtual IPeriod & GetPeriodRW(const EnjoLib::Str & name) = 0;
        virtual void SetTicks(const ITicks & ticks) = 0;

        virtual EnjoLib::Array<const IPeriod*> GetPeriodsAll() const = 0;

        virtual const ITicks & GetTicks() const = 0;
        virtual const IPeriod & m1() const = 0;
        virtual const IPeriod & m5() const = 0;
        virtual const IPeriod & m15() const = 0;
        virtual const IPeriod & m30() const = 0;
        virtual const IPeriod & h1() const = 0;
        virtual const IPeriod & h2() const = 0;
        virtual const IPeriod & h4() const = 0;
        virtual const IPeriod & h8() const = 0;
        virtual const IPeriod & h12() const = 0;
        virtual const IPeriod & d() const = 0;

    protected:
    private:
};

#endif // ISYBMOL_H
