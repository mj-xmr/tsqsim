#ifndef IBUFFERCANDLES_HPP
#define IBUFFERCANDLES_HPP

#include "typesVec.h"
#include <Template/CorradePointerFwd.h>
#include <Template/View.hpp>

class ITicks;
class Candle;
class State;

class IBufferCandles
{
    public:
        IBufferCandles();
        virtual ~IBufferCandles();

        virtual bool HasCandle(DateInt date) const = 0;
        virtual bool HasNearestCandle(DateInt date) const = 0;
        virtual const Candle & GetCandle(DateInt date) const = 0;
        virtual const Candle & GetNearestCandle(DateInt date) const = 0;
        virtual const Candle & GetExactOrNearestCandle(DateInt date) const = 0;
        virtual long GetIndexSti(DateInt date) const = 0;
        virtual long GetIndexStiPrev(DateInt date) const = 0;

        virtual CorPtr<ITicks> ToTicks() const = 0;


        // From BufferTpl
        virtual Candle operator[](unsigned i) const = 0;
        virtual Candle operator[](const State & st) const = 0;
        virtual VecCan GetBefore(unsigned iUntil, unsigned num) const = 0;
        virtual VecCan GetAfter(unsigned iFrom, unsigned num) const = 0;
        //VecCan GetMiddle(unsigned i, unsigned num) const;
        virtual int Len() const = 0;
        virtual const VecCan & GetDataVec() const = 0; /// TODO: Return IterableConst<T> and VecDataView
        virtual const IterCan & GetDataIter() const = 0; /// TODO: Return IterableConst<T> and VecDataView
        virtual unsigned ConvertIndex(unsigned i) const = 0;


    protected:

    private:
};

#endif // IBUFFERCANDLES_HPP
