#ifndef BUFFERCANDLES_H
#define BUFFERCANDLES_H

#include "IBufferCandles.h"
#include "typesVec.h"

//#include "Candle.h"
class Candle;
class ITicks;

class BufferCandles : public IBufferCandles
{
    public:
        BufferCandles( const VecCanView & v);
        virtual ~BufferCandles();

        bool HasCandle(DateInt date) const override;
        bool HasNearestCandle(DateInt date) const override;
        const Candle & GetCandle(DateInt date) const override;
        const Candle & GetNearestCandle(DateInt date) const override;
        const Candle & GetExactOrNearestCandle(DateInt date) const override;
        long GetIndexSti(DateInt date) const override;
        long GetIndexStiPrev(DateInt date) const override;

        CorPtr<ITicks> ToTicks() const override;



        // From BufferTpl
        Candle operator[](unsigned i) const override;
        Candle operator[](const State & st) const override;
        VecCan GetBefore(unsigned iUntil, unsigned num) const override;
        VecCan GetAfter(unsigned iFrom, unsigned num) const override;
        //VecCan GetMiddle(unsigned i, unsigned num) const;
        int Len() const override;
        const VecCan & GetDataVec() const override;
        const IterCan & GetDataIter() const override;
        unsigned ConvertIndex(unsigned i) const override;

    protected:
    private:
        const VecCanView & m_data;
        //BufferTpl<Candle> m_buf;
};

#endif // BUFFERCANDLES_H
