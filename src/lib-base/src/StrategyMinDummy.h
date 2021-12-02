#ifndef STRATEGYMINDUMMY_H
#define STRATEGYMINDUMMY_H

#include <IStrategy.h>

#include "StopLossFactoryAbstract.h" ///THIN DOWN!
#include "TakeProfitFactoryAbstract.h"
#include "ClosePositionFactoryAbstract.h"
#include <Template/SafePtr.hpp>

class StrategyType;
class IPeriod;
class ISymbol;
class MaPeriods;
class ScoreInput;
class StrategyFactoryAbstract;

/// TODO: Make it a base class of StrategyMin?
class StrategyMinDummy : public IStrategy
{
    public:
        StrategyMinDummy(const StrategyType & type, const ISymbol & sym, const IPeriod & period);
        virtual ~StrategyMinDummy();

        const StrategyType & GetType() const override;
        const ISymbol & GetSymbol() const override {return m_sym;}
        const IPeriod & GetPeriod() const override {return m_period;}
        const IDataProvider & GetDataProvider() const override;

        const ITakeProfit & GetTP() const override {return *(m_tp);}
        const IClosePosition & GetClosePosition() const override {return *(m_cp);}
        const IStopLoss & GetSL() const override {return *(m_sl);}
        IStopLoss & GetSLRW() override {return *(m_sl);}
        const StrategyFactoryAbstract & GetStratFactory() const override;

    protected:
        virtual int GetSLHorizonProt(const State & st) const { return 0; }

        const ISymbol & m_sym;
        const IPeriod & m_period;
        const IDataProvider & m_data;;
        EnjoLib::SafePtr<StrategyFactoryAbstract> m_stratFact; // TODO: unique_ptr

    private:
        IStopLoss * m_sl = nullptr;
        ITakeProfit * m_tp = nullptr;
        IClosePosition * m_cp = nullptr;
        EnjoLib::SafePtr<StrategyType> m_type;
};

#endif // STRATEGYMIN_H
