#include "StrategyFactoryDummy.h"

#include <Util/Except.hpp>
#include <Template/UniquePtr.hpp>

#include "IPeriod.h"
#include "StrategyType.h"
#include "StrategyTypeEnum.h"
#include "ConfigMan.h"
#include "ConfigTF.h"
#include "PlotType.h"
//#include "ModelType.h"



using namespace StrategyFactory;

StrategyFactoryDummy::StrategyFactoryDummy(){}
StrategyFactoryDummy::~StrategyFactoryDummy(){}


#include "StrategyMinDummy.h"
#include "OptiVarVec.h"
#include "ScoreInput.h"
#include "MaPeriods.h"
#include "RegResultXY.h"
#include "Buffer.h"
class StrategyDummy : public StrategyMinDummy
{
public:
    StrategyDummy(const ISymbol & sym, const IPeriod & per)
    : StrategyMinDummy(StrategyFactory::Type::STRA_DUMMY, sym, per)
    {

    }
    OptiVarVec GetOptiFloat() override { return OptiVarVec{}; }
    unsigned LenProt() const override { return 0; }; /// TODO: has to be here
    bool IsSignalProt(ST) const override { return false; }
    const Abstracts & GetAbstracts() const override { return *m_abstr; };
    const AbstractsStrat & GetAbstractsStrat() const override { return *m_abstrStrat; };
    ScoreInput GetSignalPoints(const State & st, bool trained) const override { return ScoreInput{}; }
    MaPeriods GetMaPeriods(const State & st) const override {return MaPeriods{}; }

    float GetTakeProfit(const State & st) const override { return 0; };
    float GetTakeProfitCap(const State & st) const override { return 0; };
    float GetPendingOrder(const State & st) const override { return 0; };
    const LabelCollectorPositive & GetLabelCollectorPositive() const override {return *m_labColl; }
    RegResultXY GetRegressionRange(const State & st, const IndiRoundBotArmMulti & irb) const override { return RegResultXY{}; }
    int GetRegressionRangeStart(const State & st, const IndiRoundBotArmMulti & irb) const override {return 0;}
    bool IsBreakEven(const State & st) const override { return false; }
    float GetBreakEven(const State & st) const override {return 0;}

    const LabelsMan & GetLabelsMan() const override {return *m_labMan;}
    const LabelsManSignal & GetLabelsManSignal() const override {return *m_labManSig;}
    bool IsLabelSignal(const State & st) const override { return false; }

    Buffer GetBuf(Direction dir) const override { return m_bufDataBull; }
    /*



    const StrategyType & GetType() const override { return m_type; }
    */
private:
    Abstracts * m_abstr = nullptr;
    AbstractsStrat * m_abstrStrat = nullptr;
    LabelCollectorPositive * m_labColl = nullptr;
    LabelsMan * m_labMan = nullptr;
    LabelsManSignal * m_labManSig = nullptr;

    EnjoLib::VecF m_bufDataBull;


};

Corrade::Containers::Pointer<IStrategy> StrategyFactoryDummy::Create(const StrategyType & type, const IPeriod & period) const
{
    const ISymbol & sym = period.GetSymbol();
    //IStrategy * strat = NULL;
    //switch (type.GetType())
    {
    //case Type::STRA_DIV: strat = new StrategyDivergence(type, sym, period); break;
    }
    IStrategy * strat = new StrategyDummy(sym, period);//type, sym, period);

    if (strat == NULL)
        throw EnjoLib::ExceptInvalidArg("StrategyFactory::Create(): Not defined the strategy");

    return Corrade::Containers::Pointer<IStrategy>(strat);
}


Corrade::Containers::Pointer<IStrategy> StrategyFactoryDummy::CreateRetraceLabel(const IPeriod & period, const LabelsMan & labMan) const
{
    const ISymbol & sym = period.GetSymbol();
    //return Corrade::Containers::Pointer<IStrategy>(new StrategyRetraceLabel(STRA_RETRACE_LAB, period.GetSymbol(), period, labMan));
    //return Corrade::Containers::Pointer<IStrategy>(new StrategyRetraceLabel(STRA_RETRACE_LAB, period.GetSymbol(), period));
    return Corrade::Containers::Pointer<IStrategy>(new StrategyDummy(sym, period));
}

Corrade::Containers::Pointer<IStrategy> StrategyFactoryDummy::CreatePair(const IPeriod & period, const IPeriod & periodCorr) const
{
    const ISymbol & sym = period.GetSymbol();
    return Corrade::Containers::Pointer<IStrategy>(new StrategyDummy(sym, period));
}

