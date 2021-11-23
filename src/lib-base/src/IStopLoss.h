#ifndef ISTOPLOSS_H
#define ISTOPLOSS_H

//#include "State.h"
#include "IOptimizable.h"

class State;
class IDataProvider;
class IStrategy;
class IStopLoss : public IOptimizable
{
    public:
        IStopLoss();
        virtual ~IStopLoss(){}

        static const float SPREAD_MUL; // was 6.5

        virtual float GetSLOpen(const State & st, const IStrategy & strat, int offset = 0, float spread = 0) const = 0;
        virtual float GetSL(const State & st, const IStrategy & strat, float paramMul = 1, int offset = 0, float spread = 0) const = 0;
        float GetSLWithSpreadMul(const State & st, const IStrategy & strat, float spread, float sl, float spreadMul = SPREAD_MUL) const;
        virtual OptiVarVec GetOptiFloat() override;


        virtual bool IsSane(const State & st) const {return true;}
    protected:

        float GetActiveSpread(const State & st, const IStrategy & strat, float spread) const;
    private:
};

#endif // ISTOPLOSS_H
