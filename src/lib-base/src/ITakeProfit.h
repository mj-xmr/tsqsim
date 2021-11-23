#ifndef ITAKEPROFIT_H
#define ITAKEPROFIT_H

#include "State.h"

class IStrategy;
class ITakeProfit
{
    public:
        ITakeProfit();
        virtual ~ITakeProfit(){}

        virtual float GetTP(const State & st, const IStrategy & strat) const = 0;
        virtual float GetTPFixed(const State & st, const IStrategy & strat) const = 0;

    protected:
    private:
};

#endif // ITAKEPROFIT_H
