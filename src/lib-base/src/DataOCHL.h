#ifndef DATAOCHL_H
#define DATAOCHL_H

#include <Util/VecF.hpp>
#include <Template/VecT.hpp>
#include "types.h"
#include "typesVec.h"

class Tick;
class Candle;
class DataOCHL
{
    public:
        DataOCHL();
        DataOCHL(const IterCan & candles);
        virtual ~DataOCHL();

        void Add(const Tick & tick);
        void Add(const Candle & candle);
        void UpdateLast(const Candle & candle);
        void Copy(const IterCan & candles);
        void Copy(const VecCan & candles);
        unsigned Size() const;
        unsigned Len() const;
        void PrintPython() const;
        VecCan ToCandles() const;
        float GetPriceClose(int i) const;
        float GetPriceMid(int i) const;
        float GetPriceWeighted(int i) const;
        float GetPriceTypical(int i) const;

        EnjoLib::VecF opens, closes, highs, lows;
        EnjoLib::VecT<DateInt> dates;

    protected:
    private:
};

#endif // DATAOCHL_H
