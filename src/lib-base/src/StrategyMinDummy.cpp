#include "StrategyMinDummy.h"
#include "IDataProvider.h"
#include "StrategyType.h"
#include "IPeriod.h"
#include "StrategyFactoryDummy.h"
#include "OptiVarVec.h"
#include <Template/CorradePointer.h>

StrategyMinDummy::StrategyMinDummy(const StrategyType & type, const ISymbol & sym, const IPeriod & per)
: IStrategy()
, m_sym(sym)
, m_period(per)
, m_data(per)
, m_stratFact(new StrategyFactoryDummy())
//, m_sl(StopLossFactory().Create(per, sl).release())
//, m_tp(TakeProfitFactory().Create(tp).release())
//, m_cp(ClosePositionFactory().Create(cp, *this).release())
, m_type(new StrategyType(type))
{
}


StrategyMinDummy::~StrategyMinDummy(){}

const StrategyType & StrategyMinDummy::GetType() const
{
    return *m_type;
}

const StrategyFactoryAbstract & StrategyMinDummy::GetStratFactory() const { return *m_stratFact; }

const IDataProvider & StrategyMinDummy::GetDataProvider() const {return m_period;}

