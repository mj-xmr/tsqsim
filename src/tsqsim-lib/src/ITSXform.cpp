#include "ITSXform.h"
#include "TSFunBase.h"
#include "Candle.h"

ITSXform::ITSXform(){}
ITSXform::~ITSXform(){}

unsigned ITSXform::MaxShift() const
{
    return 0;
}

double ITSXform::GetVal(const IHasCandles & input, int idx) const
{
    const Candle & can = input.GetCandle(idx);
    return can.GetClose(); /// TODO: Return a common value
}