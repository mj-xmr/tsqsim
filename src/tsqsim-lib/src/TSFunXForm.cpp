#include "TSFunXForm.h"
#include "ConfigTS.h"

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

    const double ret = gmat.Fabs(canCurr.GetPriceByType(GetTSIn().m_cfgTS.GetPriceType()) - canPrev.GetPriceByType(GetTSIn().m_cfgTS.GetPriceType()));

    TSRes res(true);
    res.val = ret;

    return res;
}

TSRes TSFunXForm::Reconstruct(int idx, const EnjoLib::VecD & input, const EnjoLib::VecD & lost) const
{
    TSRes res(true);
    return res;
}


unsigned TSFunXForm::LenProt() const
{
    return LenData() - 1;
}
