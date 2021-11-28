#ifndef IPERIODBASE_H
#define IPERIODBASE_H

#include "IDataProvider.h"
#include "Direction.h"
#include "typesVec.h"
#include <Template/ArrayFwd.hpp>
#include <Template/View.hpp>

class BufferType;
class BufferVecType;
class Buffer;
class BufferBool;
class BufferCandles;
class SR;
class Tick;
class ITicks;
class MaPeriods;
class Candle;
class ISymbol;
class PriceFilterConfig;
class BufferUpdateable;
class BufferVecUpdateable;
class StrategyFactoryAbstract;
class SRVisibleData;

class IPeriod : public IDataProvider
{
    public:
        IPeriod(const ISymbol & sym);
        virtual ~IPeriod();

        const ISymbol & GetSymbol() const { return m_sym; }

        virtual void Feed(const Tick & tick, bool updateTech = false) = 0;
        virtual void Feed(const EnjoLib::IIterableConst<Tick> & tick, bool updateTech = false) = 0;

        virtual void FeedFromLower(const Tick & period, int periodRatio) = 0;
        virtual void CalcTech() = 0;
        virtual void UpdateTech() = 0;
        virtual void FinalizeCandle() = 0;
        virtual void LimitData(int maxLatestBars) = 0;
        virtual void FilterPrice(const PriceFilterConfig & cfg) = 0;
        //void SetMaUsed(int period) const;
        //int GetMaUsedPeriodSlow() const;
        //int GetMaUsedPeriodFast() const;
        //bool IsMaUsedPeriodSlowMax() const;
        virtual int GetNumTicks() const = 0;
        virtual int GetNumSeconds() const = 0;
        virtual DateInt GetDateStart(int numBack) const = 0;
        virtual DateInt GetDateEnd(int numBack, int n = 0) const = 0;
        virtual float GetTPRatio() const = 0;
        //virtual float GetTPRatio() const {return 100;};
        virtual bool UsingTicks() const = 0;

        const EnjoLib::VecF & GetBufData(const BufferType & type) const;
        virtual const EnjoLib::Array<EnjoLib::VecF> & GetBufVec(const BufferVecType & type) const = 0;
        virtual Buffer GetMa(int period) const = 0;
        virtual PriceFilterConfig GetPriceFilterConfigGlob() const = 0;
        virtual void SetPriceFilterConfig(const PriceFilterConfig & cfg) = 0;


        //Buffer GetMaUsedSlow() const;
        //Buffer GetMaUsedFast() const;
        virtual EnjoLib::View<MaPeriods> GetMaUsedPeriods() const = 0;
        virtual const SRVisibleData & GetSRVisible(Direction dir) const = 0;
        //virtual const StrategyFactoryAbstract & GetStratFactory() const = 0;

        //virtual Buffer GetOpensNext() const = 0;
        //const Abstracts & GetAbstracts() const { return m_abstr; };

        virtual void SetCandles(const VecCan & candles) = 0;
        virtual void SetCandles(const STDFWD::deque<Candle> & candles) = 0;
        virtual void SetCandles(const STDFWD::deque<Tick> & candles) = 0;
        //virtual void SetStates(const HmmStates & states) = 0;

        virtual const DataOCHL & GetDataFull() const = 0;

    protected:
        const ISymbol & m_sym;

    private:
};

#endif // IPERIODBASE_H
