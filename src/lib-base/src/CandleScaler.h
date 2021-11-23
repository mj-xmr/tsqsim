#ifndef CANDLESCALER_H
#define CANDLESCALER_H

#include "Candle.h"
#include "typesVec.h"

class CandleScaler
{
    public:
        CandleScaler();
        virtual ~CandleScaler();

        EnjoLib::VecF Scale(const IterCan & vc, unsigned n) const;
    protected:
    private:
};

#endif // CANDLESCALER_H
