#ifndef ORDERTAKEPROFIT_H
#define ORDERTAKEPROFIT_H

#include "OrderPending.h"


class OrderTakeProfit : public OrderPending
{
    public:
        OrderTakeProfit(const State & st = State(SELL, 0), float level = 0, float capUsed = 0);
        virtual ~OrderTakeProfit();
    protected:
    private:
};

#endif // ORDERTAKEPROFIT_H
