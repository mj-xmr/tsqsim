#ifndef IHASCANDLES_H
#define IHASCANDLES_H

class Candle;

class IHasCandles
{
    public:
        IHasCandles();
        virtual ~IHasCandles();
        
        virtual Candle GetCandle(int idx, int shift = 0) const = 0;
        virtual unsigned Len() const = 0;

    protected:

    private:
};

#endif // IHASCANDLE_H
