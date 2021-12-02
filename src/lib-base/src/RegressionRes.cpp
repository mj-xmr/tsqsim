#include "RegressionRes.h"

RegressionRes::RegressionRes()
{
    //ctor
}

RegressionRes::~RegressionRes()
{
    //dtor
}

bool RegressionRes::IsBullish() const
{
    int degree = coeffs.size();
    if (degree == 0)
        return false;
    bool bullish = coeffs.back() > 0;
    if (degree == 2)
        bullish = not bullish;

    return bullish;
}

