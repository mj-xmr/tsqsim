#include "TSXformImpl.h"

#include "IHasCandles.h"
#include "Candle.h"
#include "TSXformRes.h"

#include <Math/GeneralMath.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/CharManipulations.hpp>
#include <Statistical/Assertions.hpp>

using namespace EnjoLib;


TSXformDiff::TSXformDiff(const VecStr & params)
{
    if (params.size() > 0)
    {
         m_order = CharManipulations().ToInt(params.at(0));
    }
}
XformRes TSXformDiff::Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const
{
    //LOGL << "idx = " << idx << Nl;
    const Candle & canCurr = input.GetCandle0Based(idx);
    double prev = prevConverted ;
    double lost = 0;
    //if (idx < int(input.Len()) - int(MaxShift())) /// TODO: Retarded from a user's perspective. It should be: "if (i > 0)" ?
    //if (idx == 0)
    {
        //const Candle & canPrev = input.GetCandle(idx, 1);
        //prev = canPrev.GetPriceByType(priceType);
        //prev = 0;
    }
    //else
    if (idx == 0)
    {
        const Candle & canPrev = input.GetCandle0Based(idx);
        lost = canPrev.GetPriceByType(priceType);
        //LOGL << "Prev = " << prev << Nl;
        
        XformRes diff;
        diff.lost = lost;
        
        return diff;
    }
    else
    {
        const Candle & canPrev = input.GetCandle0Based(idx - 1);
        prev = canPrev.GetPriceByType(priceType);
        
        VecD inp;
        inp.Add(canCurr.GetPriceByType(priceType));
        inp.Add(prev);
        
        XformRes diff = Run(inp);
        
        return diff;
    }
}

XformRes TSXformDiff::Run(const EnjoLib::VecD & vals) const
{
    XformRes res;

    const double diff = vals.at(0) - vals.at(1);
    res.conv = diff;
    //VecD lost;
    //lost.Add();  // vals.at(0) ? rather not. Only add old and missing
    //res.lost = vals.at(1);

    return res;
}
/// TODO: Unit test all the inversions with CHECK_CLOSE()
double TSXformDiff::Invert(const EnjoLib::VecD & vals, double lost) const
{
    //LOGL << "Invert vars = " << vals.Print() << " Lost = " << lost << Nl;
    return vals.at(0) + vals.at(1) + lost;
}
unsigned TSXformDiff::MaxShift() const
{
    return m_order;
}

XformRes TSXformOrig::Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const
{
    XformRes res;

    const Candle & canCurr = input.GetCandle0Based(idx);
    res.conv = canCurr.GetPriceByType(priceType);

    return res; /// TODO: Get a common value of candle
}
XformRes TSXformOrig::Run(const EnjoLib::VecD & vals) const
{
    XformRes res;
    res.conv = vals.at(0);
    return res;
}
double TSXformOrig::Invert(const EnjoLib::VecD & vals, double lost) const
{
    return vals.at(0);
}

XformRes TSXformFabs::Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const
{
    if (prevConverted == ITSXform::DATA_INITIAL)
    {
        return Run(VecD(1, input.GetCandle0Based(idx).GetPriceByType(priceType)));
    }
    else
    {
        return Run(VecD(1, prevConverted));
    }
}
XformRes TSXformFabs::Run(const EnjoLib::VecD & vals) const
{
    XformRes res;
    res.conv = GeneralMath().Fabs(vals.at(0));
    res.lost = GeneralMath().sign(vals.at(0));
    return res;
}
double TSXformFabs::Invert(const EnjoLib::VecD & vals, double lost) const
{
    return vals.at(0) * lost;
}

XformRes TSXformSqrt::Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const
{
    if (prevConverted == ITSXform::DATA_INITIAL)
    {
        return Run(VecD(1, input.GetCandle0Based(idx).GetPriceByType(priceType)));
    }
    else
    {
        return Run(VecD(1, prevConverted));
    }
}
XformRes TSXformSqrt::Run(const EnjoLib::VecD & vals) const
{
    //LOGL << "TSXformSqrt::Run Vals = " << vals.Print() << Nl;
    XformRes res;
    const double valPrev = vals.at(0);
    const GMat gmat;
    if (valPrev > 0)
    {
        res.conv = gmat.Sqrt(valPrev);
    }
    else if (valPrev == 0)
    {
        res.conv = 0;
    }
    else
    {
        res.conv = -gmat.Sqrt(-valPrev);
    }
    return res;
}
double TSXformSqrt::Invert(const EnjoLib::VecD & vals, double lost) const
{
    const double valPrev = vals.at(0);
    const GMat gmat;
    const double pow = gmat.Pow(valPrev, 2);
    return valPrev < 0 ? -pow : pow;
}

XformRes TSXformLog::Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const
{
    if (prevConverted == ITSXform::DATA_INITIAL)
    {
        return Run(VecD(1, input.GetCandle0Based(idx).GetPriceByType(priceType)));
    }
    else
    {
        return Run(VecD(1, prevConverted));
    }
}
XformRes TSXformLog::Run(const EnjoLib::VecD & vals) const
{
    XformRes res;
    const double valPrev = vals.at(0);
    const GMat gmat;
    if (valPrev > VAL_BORDER)
    {
        res.conv = gmat.Log(valPrev);
    }
    else if (valPrev == VAL_BORDER)
    {
        res.conv = 0;
    }
    else
    {
        const double diff = gmat.Fabs(VAL_BORDER - valPrev);
        res.conv = -gmat.Log(diff + VAL_BORDER); /// TODO: Call Log only once (after UTs)
    }
    return res;
}
double TSXformLog::Invert(const EnjoLib::VecD & vals, double lost) const
{
    const double val = vals.at(0);
    const GMat gmat;
    if (val > 0)
    {
        return gmat.Exp(val);
    }
    else
    {
        return -gmat.Exp(-val) + 2* VAL_BORDER; /// TODO: Call Exp only once (after UTs)
    }
}


TSXformAdd::TSXformAdd(const VecStr & params)
: m_add(CharManipulations().ToDouble(params.at(0)))
{
}
XformRes TSXformAdd::Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const
{
    if (prevConverted == ITSXform::DATA_INITIAL)
    {
        return Run(VecD(1, input.GetCandle0Based(idx).GetPriceByType(priceType)));
    }
    else
    {
        return Run(VecD(1, prevConverted));
    }
}
XformRes TSXformAdd::Run(const EnjoLib::VecD & vals) const
{
    return XformRes(vals.at(0) + m_add);
}
double TSXformAdd::Invert(const EnjoLib::VecD & vals, double lost) const
{
    return vals.at(0) - m_add;
}

TSXformMul::TSXformMul(const VecStr & params)
: m_mul(CharManipulations().ToDouble(params.at(0)))
{
    Assertions::IsNonZero(m_mul, "TSXformMul::TSXformMul()");
}
XformRes TSXformMul::Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const
{
    if (prevConverted == ITSXform::DATA_INITIAL)
    {
        return Run(VecD(1, input.GetCandle0Based(idx).GetPriceByType(priceType)));
    }
    else
    {
        return Run(VecD(1, prevConverted));
    }
}
XformRes TSXformMul::Run(const EnjoLib::VecD & vals) const
{
    return XformRes(vals.at(0) * m_mul);
}
double TSXformMul::Invert(const EnjoLib::VecD & vals, double lost) const
{
    return vals.at(0) / m_mul;
}

TSXformDiv::TSXformDiv(const VecStr & params)
: m_div(CharManipulations().ToDouble(params.at(0)))
{
    Assertions::IsNonZero(m_div, "TSXformDiv::TSXformDiv()");
}
XformRes TSXformDiv::Run(const IHasCandles & input, const PriceType & priceType, int idx, double prevConverted) const
{
    if (prevConverted == ITSXform::DATA_INITIAL)
    {
        return Run(VecD(1, input.GetCandle0Based(idx).GetPriceByType(priceType)));
    }
    else
    {
        return Run(VecD(1, prevConverted));
    }
}
XformRes TSXformDiv::Run(const EnjoLib::VecD & vals) const
{
    return XformRes(vals.at(0) / m_div);
}
double TSXformDiv::Invert(const EnjoLib::VecD & vals, double lost) const
{
    return vals.at(0) * m_div;
}
