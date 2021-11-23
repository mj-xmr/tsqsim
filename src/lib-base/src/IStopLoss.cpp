#include "IStopLoss.h"
#include "IStrategy.h"
#include "IPeriod.h"
#include "ISymbol.h"
#include "OptiVarVec.h"
#include "State.h"

//const float IStopLoss::SPREAD_MUL = 4; // was 6.5
const float IStopLoss::SPREAD_MUL = 6.5; // was 6.5

IStopLoss::IStopLoss(){}

float IStopLoss::GetSLWithSpreadMul(const State & st, const IStrategy & strat, float spread, float sl, float spreadMul) const
{
    float spreadActive = GetActiveSpread(st, strat, spread);
    const float spreadMultiplied = spreadActive * spreadMul;
    const float maxMinWSpread = sl + (st.bullish ? -spreadMultiplied : +spreadMultiplied);

    return maxMinWSpread;
}

float IStopLoss::GetActiveSpread(const State & st, const IStrategy & strat, float spread) const
{
    const float spreadStatic = strat.GetPeriod().GetSymbol().GetSpread(strat.GetPeriod().GetClose(st.i));
    if (spread == 0)
        spread = spreadStatic;
    return spread;
}

OptiVarVec IStopLoss::GetOptiFloat()
{ 
    return OptiVarVec();
}
