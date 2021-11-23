#ifndef INTEREST_H
#define INTEREST_H

#include "types.h"

class Interest
{
    public:
        Interest(float bid, float ask, DateInt date);
        virtual ~Interest();

        DateInt GetDate() const { return date; }
        float GetBid() const { return bid; }
        float GetAsk() const { return ask; }
        float GetMid() const { return (ask + bid) / 2.0; }

    protected:

    private:
        float bid = -1;
        float ask = -1;
        DateInt date = 0;
};

#endif // INTEREST_H
