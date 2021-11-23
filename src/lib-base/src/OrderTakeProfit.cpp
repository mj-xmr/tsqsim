#include "OrderTakeProfit.h"

OrderTakeProfit::OrderTakeProfit(const State & st, float level, float capUsed)
: OrderPending(st, level, capUsed)
{
    //ctor
}

OrderTakeProfit::~OrderTakeProfit()
{
    //dtor
}
