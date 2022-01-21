#include "ITSXform.h"
#include "TSFunBase.h"
#include "Candle.h"

ITSXform::ITSXform(){}
ITSXform::~ITSXform(){}

const double ITSXform::DATA_INITIAL = -100000;

unsigned ITSXform::MaxShift() const
{
    return 0;
}

double ITSXform::GetVal(const IHasCandles & input, const PriceType & priceType, int idx) const
{
    const Candle & can = input.GetCandle0Based(idx);
    return can.GetPriceByType(priceType); /// TODO: Return a common value
}