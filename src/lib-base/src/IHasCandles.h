#ifndef IHASCANDLES_H
#define IHASCANDLES_H

class Candle;

class IHasCandles
{
    public:
        IHasCandles();
        virtual ~IHasCandles();
        
        virtual Candle GetCandle0Based(int idx) const = 0;
        virtual Candle GetCandleTS(int idx, int shift = 0) const = 0;
        virtual unsigned Len() const = 0;

    protected:

    private:
};

#endif // IHASCANDLE_H
