#ifndef ISTRATEGY_H
#define ISTRATEGY_H

#include "Direction.h"
#include "types.h"
#include "SignalBase.h"
#include "IOptimizable.h"
#include <Util/VecF.hpp>
#include <Util/VecD.hpp>
#include <Template/ArrayFwd.hpp>
//#include <vector>

class OrderPending;
class OrderTakeProfit;
class IClassifier;
struct ScoreInput;
class IStopLoss;
class ITakeProfit;
class ISymbol;
class IModel;
class IPeriod;
class IDataProvider;
class Abstracts;
class AbstractsStrat;
class IClosePosition;
class MaPeriods;
class ISR;
class LabelCollectorPositive;
class MinMax;
class RegResultXY;
class IndiRoundBotArmMulti;
class LabelsMan;
class LabelsManSignal;
class StrategyType;
class Buffer;
class StrategyFactoryAbstract;
enum class ModelType;

class IStrategy : public SignalBase, public IOptimizable
{
    public:
        IStrategy();
        virtual ~IStrategy();

        EnjoLib::Str GetName() const;
        EnjoLib::Str GetSymSymCorrPerNameId() const;
        virtual const StrategyType & GetType() const = 0;
        virtual const IStopLoss & GetSL() const = 0;
        virtual IStopLoss & GetSLRW() = 0; 
        virtual const ITakeProfit & GetTP() const = 0;
        virtual const ISymbol & GetSymbol() const = 0;
        virtual const IPeriod & GetPeriod() const = 0;
        virtual const StrategyFactoryAbstract & GetStratFactory() const = 0;
        virtual const IDataProvider & GetDataProvider() const = 0;
        virtual const Abstracts & GetAbstracts() const = 0;
        virtual const AbstractsStrat & GetAbstractsStrat() const = 0;
        virtual const IClosePosition & GetClosePosition() const = 0;
        virtual int GetSignalStart(const State & st) const { return 0; }
        virtual ScoreInput GetSignalPoints(const State & st, bool trained) const = 0;
        virtual MaPeriods GetMaPeriods(const State & st) const = 0;
        virtual MinMax GetRange(const State & st) const;
        virtual float GetPricePendingOrder(const State & st) const { return 0; }
        virtual float GetPricePendingOrderDynamic(const State & st) const { return 0; }
        virtual EnjoLib::Array<OrderPending> GetPricesPendingOrders(const State & st) const;
        virtual EnjoLib::Array<OrderPending> GetPricesPendingOrders(const State & st, const ISR & sr, int reduction = 0) const;
        virtual EnjoLib::Array<OrderTakeProfit> GetTakeProfits(const State & st) const;
        virtual float GetTakeProfit(const State & st) const = 0;
        virtual float GetTakeProfitCap(const State & st) const = 0;
        virtual float GetPendingOrder(const State & st) const = 0;
        virtual float GetSLStdDevMulFixedPercent() const { return 0; }
        virtual int   GetSLHorizon(const State & st) const { return 0; }
        virtual float GetSLHintOpen(const State & st) const { return 0; }
        virtual float GetSLHintTrail(const State & st) const { return 0; }
        virtual bool IsOpenMarket(const State & st) const { return 0; }
        virtual const ISignal & GetSpecialSignal() const { return *this; }
        virtual const ISignal & GetSpecialSignalStart() const { return GetSpecialSignal(); }
        virtual const LabelCollectorPositive & GetLabelCollectorPositive() const = 0;
        virtual bool IsDisarm(const State & st) const { return false; }
        virtual bool IsArm(const State & st) const { return true; }
        virtual bool IsBasicCondition(const State & st) const { return true; }
        virtual bool IsTickNeeded(const State & st) const { return false; }
        virtual bool IsTickPriceOpen(const State & st) const { return false; }
        virtual EnjoLib::Pair<float, float> GetOpenPriceRangeMinMax(const State & st) const;
        virtual bool IsClosePos(const State & st) const { return false; }
        virtual float GetClosePosVol(const State & st) const { return 0; }
        virtual bool IsSignalPrecondition(const State & st) const { return IsSignal(st); }
        virtual bool IsSLAtOpen(const State & st) const { return true; }
        virtual double GetPairCap(const State & st) const { return 0; }
        virtual EnjoLib::Str DumpModel() const;
        virtual void ReinitModel(const EnjoLib::Str & model) {}

        virtual RegResultXY GetRegressionRange(const State & st, const IndiRoundBotArmMulti & irb) const = 0;
        virtual int GetRegressionRangeStart(const State & st, const IndiRoundBotArmMulti & irb) const = 0;
        virtual bool IsBreakEven(const State & st) const = 0;
        virtual float GetBreakEven(const State & st) const = 0;
        virtual EnjoLib::Str GetPatternDataXY(const State & st) const;// { return ""; }
        virtual EnjoLib::VecD GetPatternDataRaw(const State & st) const;// { return EnjoLib::VecD(); }
        virtual ModelType GetMLModelType() const;

        //bool UseCache() const override {return false;}
        void SetUsePendingOrders(bool setting) { m_usePending = setting; }
        void SetLabelBased() { m_labelBased = true; }

        virtual const LabelsMan & GetLabelsMan() const = 0;
        virtual const LabelsManSignal & GetLabelsManSignal() const = 0;
        virtual bool IsLabelSignal(const State & st) const = 0;

        virtual Buffer GetBuf(Direction dir) const = 0;

        void SetPeriodCorrel(const IPeriod * perCorrel) { m_perCorrel = perCorrel; }
        void SetLeverage(const float leverage);
        const IPeriod * GetPeriodCorrel() const { return m_perCorrel; }
        float GetLeverage() const { return m_leverage; }




    protected:
        //IClassifier & GetClassifier() const;
        //bool UseCache() const {return true;} // Doesn't work because MaAdapter
        bool m_usePending = true;
        bool m_labelBased = false;

    private:
        //IClassifier & m_classifier;
        const IPeriod * m_perCorrel = nullptr;
        float m_leverage = 1;
};

#endif // ISTRATEGY_H
