#include "TSFunPrintCumul.h"

#include "Candle.h"
#include "ConfigTS.h"

#include <Math/GeneralMath.hpp>
#include <Util/CoutBuf.hpp>

using namespace EnjoLib;

TSFunPrintCumul::TSFunPrintCumul(const TSInput & tsin)
: TSFunBase(tsin)
{
    //ctor
}

TSFunPrintCumul::~TSFunPrintCumul()
{
    //dtor
}

TSRes TSFunPrintCumul::OnDataPointProt(int idx) const
{
    const GMat gmat;

    const Candle & canCurr = GetCandle(idx);
    const Candle & canPrev = GetCandle(idx, 1);

    const double ret = gmat.Sqrt(gmat.Fabs(canCurr.GetPriceByType(GetTSIn().m_cfgTS.GetPriceType()) - canPrev.GetPriceByType(GetTSIn().m_cfgTS.GetPriceType())));// - 0.035;

    TSRes res(true);
    res.val = ret;

    return res;
}

TSRes TSFunPrintCumul::Reconstruct(int idx, const EnjoLib::VecD & input, const EnjoLib::VecD & lost) const
{
    TSRes res(true);
    return res;
}

