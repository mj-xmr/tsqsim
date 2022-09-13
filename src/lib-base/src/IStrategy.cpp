#include "IStrategy.h"
#include "ISymbol.h"
#include "IPeriod.h"
#include "IModel.h"
#include "MinMax.h"
#include "StrategyFactoryName.h"
#include "TradeUtil.h"
#include "ScoreInput.h"
#include "OrderTakeProfit.h"
#include "OrderPending.h"
#include "ModelType.h"

#include <Util/Str.hpp>
#include <Template/Array.hpp>

using namespace std;

IStrategy::IStrategy()
//: m_classifier(classifier)
{
    //ctor
}
IStrategy::~IStrategy(){}

EnjoLib::Array<OrderPending> IStrategy::GetPricesPendingOrders(const State & st) const { return EnjoLib::Array<OrderPending>(); }
EnjoLib::Array<OrderPending> IStrategy::GetPricesPendingOrders(const State & st, const ISR & sr, int reduction) const { return EnjoLib::Array<OrderPending>(); }
EnjoLib::Array<OrderTakeProfit> IStrategy::GetTakeProfits(const State & st) const { return EnjoLib::Array<OrderTakeProfit>(); }

/*
IClassifier & IStrategy::GetClassifier() const
{
    return m_classifier;
}
*/

MinMax IStrategy::GetRange(const State & st) const
{
    return MinMax();
}


EnjoLib::Str IStrategy::GetName() const
{
    return StrategyFactoryName().Create(GetType());
}

EnjoLib::Str IStrategy::GetSymSymCorrPerNameId() const
{
    return TradeUtil().GetSymSymCorrPerNameId(GetDataProvider(), GetPeriodCorrel());
}

void IStrategy::SetLeverage(const float leverage)
{
    if (leverage <= 0) return;
    m_leverage = leverage;
}

ModelType IStrategy::GetMLModelType() const
{
    return ModelType::MODEL_NONE;
}

EnjoLib::Str IStrategy::GetPatternDataXY(const State & st) const { return ""; }
EnjoLib::VecD IStrategy::GetPatternDataRaw(const State & st) const { return EnjoLib::VecD(); }
        
EnjoLib::Str IStrategy::DumpModel() const
{
    return "";
}

EnjoLib::Pair<float, float> IStrategy::GetOpenPriceRangeMinMax(const State & st) const { return EnjoLib::Pair<float, float>(0,0); }