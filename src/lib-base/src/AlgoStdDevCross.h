#ifndef INDISTDDEVCROSSBASE_H
#define INDISTDDEVCROSSBASE_H

#include "Direction.h"

class Candle;
class AlgoStdDevCross
{
    public:
        AlgoStdDevCross();
        virtual ~AlgoStdDevCross();

        bool Calc(float stdDev, const Candle & c, Direction bullish) const;
    protected:
    private:
};

#endif // INDISTDDEVCROSSBASE_H
