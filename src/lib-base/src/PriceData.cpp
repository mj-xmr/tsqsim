#include "PriceData.h"

PriceData::PriceData()
{
    //ctor
}

PriceData::PriceData(float open, float close, float hi, float lo)
: hi(hi), lo(lo), open(open), close(close)
{
    
}

PriceData::~PriceData()
{
    //dtor
}
