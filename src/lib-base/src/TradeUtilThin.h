#ifndef TRADEUTILTHIN_HPP
#define TRADEUTILTHIN_HPP

#include "types.h"

class TradeUtilThin
{
    public:
        TradeUtilThin();
        virtual ~TradeUtilThin();
        
        void KillPythonServer();
        float CalcGain(float currCap, float gain, float maxCapUsed, float leverage = 1) const;
        float CalcGainNoCap(float currCap, float gain) const;
        int CalcDiffDays(DateInt one, DateInt two) const;
        float CalcPeriodTicksRelToHour(int numTicks) const;

        unsigned GetIdFromPrice(float price) const;
        unsigned ConvertIndexConst(unsigned i, unsigned size) const;
        constexpr static inline unsigned ConvertIndex(unsigned i, unsigned size) 
        { 
            return size - 1 - i; 
        }

    protected:

    private:
};

#endif // TRADEUTILTHIN_HPP
