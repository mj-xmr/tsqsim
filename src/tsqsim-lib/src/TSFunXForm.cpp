#include "TSFunXForm.h"

#include "Candle.h"

#include <Math/GeneralMath.hpp>

using namespace EnjoLib;

TSFunXForm::~TSFunXForm(){}
TSFunXForm::TSFunXForm(const TSInput & tsin)
: TSFunBase(tsin)
{
    //ctor
}

TSRes TSFunXForm::OnDataPointProt(int idx) const
{
    const GMat gmat;

    const Candle & canCurr = GetCandle(idx);
    const Candle & canPrev = GetCandle(idx, 1);

    const double ret = gmat.Fabs(canCurr.GetClose() - canPrev.GetClose());

    TSRes res(true);
    res.val = ret;

    return res;
}

TSRes TSFunXForm::Reconstruct(int idx, const EnjoLib::VecD & input, double prev) const
{
    TSRes res(true);
    return res;
}


unsigned TSFunXForm::LenProt() const
{
    return LenData() - 1;
}
