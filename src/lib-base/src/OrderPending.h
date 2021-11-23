#ifndef ORDERPENDING_H
#define ORDERPENDING_H

#include "State.h"

class OrderPending
{
    public:
        OrderPending(const State & st = State(SELL, 0), float level = 0, float capUsed = 0);
        virtual ~OrderPending();

        State st;
        float level = 0;
        float capUsed = 0;

    protected:
    private:
};

#endif // ORDERPENDING_H
