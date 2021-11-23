#ifndef PRICEDATA_HPP
#define PRICEDATA_HPP

namespace boost
{
    namespace serialization
    {
        class access;
    }
}

class PriceData
{
    public:
        PriceData();
        PriceData(float open, float close, float hi, float lo);
        virtual ~PriceData();
        
        float hi = 0;
        float lo = 0;
        float open = 0;
        float close = 0;
        
        float bodyMin = 0;
        float bodyMax = 0;
        
        float wickHi = 0;
        float wickLo = 0;        

    protected:

    private:
};

#endif // PRICEDATA_HPP
