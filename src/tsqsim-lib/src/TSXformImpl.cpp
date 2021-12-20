#include "TSXformImpl.h"

#include "TSFunBase.h"
#include "Candle.h"

#include <Math/GeneralMath.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/CharManipulations.hpp>
#include <Statistical/Assertions.hpp>

using namespace EnjoLib;

double TSXformDiff::Run(const TSFunBase & input, int idx, double valPrev) const
{
    const Candle & canCurr = input.GetCandle(idx);
    double prev = canCurr.GetOpen();
    if (idx < int(input.Len()) - 1) /// TODO: Retarded from a user's perspective. It should be: "if (i > 0)" ?
    {
        const Candle & canPrev = input.GetCandle(idx, 1);
        prev = canPrev.GetClose();
    }
    else
    {
        //LOGL << "Prev = " << prev << Nl;
    }
    const double diff = canCurr.GetClose() - prev;
    //const double diff = canCurr.GetHigh() - prev;
    return diff;
}
double TSXformDiff::Run(const EnjoLib::VecD & vals) const
{
    const double diff = vals.at(0) - vals.at(1);
    return diff;
}
/// TODO: Unit test all the inversions with CHECK_CLOSE()
double TSXformDiff::Invert(const EnjoLib::VecD & vals) const
{
    return vals.at(0) + vals.at(1);
}
unsigned TSXformDiff::MaxShift() const
{
    return 0;
}

double TSXformFabs::Run(const TSFunBase & input, int idx, double valPrev) const
{
    return GeneralMath().Fabs(valPrev);
}
double TSXformFabs::Run(const EnjoLib::VecD & vals) const
{
    return GeneralMath().Fabs(vals.at(0));
}
double TSXformFabs::Invert(const EnjoLib::VecD & vals) const
{
    return vals.at(0);
}

double TSXformSqrt::Run(const TSFunBase & input, int idx, double valPrev) const
{
    return Run(VecD(1, valPrev));
}
double TSXformSqrt::Run(const EnjoLib::VecD & vals) const
{
    const double valPrev = vals.at(0);
    const GMat gmat;
    if (valPrev > 0)
    {
        return gmat.Sqrt(valPrev);
    }
    else if (valPrev == 0)
    {
        return 0;
    }
    else
    {
        return -gmat.Sqrt(-valPrev);
    }
}
double TSXformSqrt::Invert(const EnjoLib::VecD & vals) const
{
    const double valPrev = vals.at(0);
    const GMat gmat;
    const double pow = gmat.Pow(valPrev, 2);
    return valPrev < 0 ? -pow : pow;
}

double TSXformLog::Run(const TSFunBase & input, int idx, double valPrev) const
{
    return Run(VecD(1, valPrev));
}
double TSXformLog::Run(const EnjoLib::VecD & vals) const
{
    const double valPrev = vals.at(0);
    const GMat gmat;
    if (valPrev > VAL_BORDER)
    {
        return gmat.Log(valPrev);
    }
    else if (valPrev == VAL_BORDER)
    {
        return 0;
    }
    else
    {
        const double diff = gmat.Fabs(VAL_BORDER - valPrev);
        return -gmat.Log(diff + VAL_BORDER); /// TODO: Call Log only once (after UTs)
    }
}
double TSXformLog::Invert(const EnjoLib::VecD & vals) const
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
double TSXformAdd::Run(const TSFunBase & input, int idx, double valPrev) const
{
    return Run(VecD(1, valPrev));
}
double TSXformAdd::Run(const EnjoLib::VecD & vals) const
{
    return vals.at(0) + m_add;
}
double TSXformAdd::Invert(const EnjoLib::VecD & vals) const
{
    return vals.at(0) - m_add;
}

TSXformMul::TSXformMul(const VecStr & params)
: m_mul(CharManipulations().ToDouble(params.at(0)))
{
    Assertions::IsNonZero(m_mul, "TSXformMul::TSXformMul()");
}
double TSXformMul::Run(const TSFunBase & input, int idx, double valPrev) const
{
    return Run(VecD(1, valPrev));
}
double TSXformMul::Run(const EnjoLib::VecD & vals) const
{
    return vals.at(0) * m_mul;
}
double TSXformMul::Invert(const EnjoLib::VecD & vals) const
{
    return vals.at(0) / m_mul;
}

TSXformDiv::TSXformDiv(const VecStr & params)
: m_div(CharManipulations().ToDouble(params.at(0)))
{
    Assertions::IsNonZero(m_div, "TSXformDiv::TSXformDiv()");
}
double TSXformDiv::Run(const TSFunBase & input, int idx, double valPrev) const
{
    return Run(VecD(1, valPrev));
}
double TSXformDiv::Run(const EnjoLib::VecD & vals) const
{
    return vals.at(0) / m_div;
}
double TSXformDiv::Invert(const EnjoLib::VecD & vals) const
{
    return vals.at(0) * m_div;
}
