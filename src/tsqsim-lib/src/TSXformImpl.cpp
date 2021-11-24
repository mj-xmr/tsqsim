#include "TSXformImpl.h"

#include "TSFunBase.h"
#include "Candle.h"

#include <Math/GeneralMath.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/CharManipulations.hpp>

using namespace EnjoLib;

double TSXformDiff::Run(const TSFunBase & input, int idx, double valPrev) const
{
    const Candle & canCurr = input.GetCandle(idx);
    const Candle & canPrev = input.GetCandle(idx, 1);

    const double diff = canCurr.GetClose() - canPrev.GetClose();
    return diff;
}
unsigned TSXformDiff::MaxShift() const
{
    return 1;
}

double TSXformFabs::Run(const TSFunBase & input, int idx, double valPrev) const
{
    return GeneralMath().Fabs(valPrev);
}

double TSXformSqrt::Run(const TSFunBase & input, int idx, double valPrev) const
{
    return GeneralMath().Sqrt(valPrev);
}

double TSXformSqrtSafe::Run(const TSFunBase & input, int idx, double valPrev) const
{
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

double TSXformLogSafe::Run(const TSFunBase & input, int idx, double valPrev) const
{
    const GMat gmat;
    if (valPrev > 0)
    {
        return gmat.Log10(valPrev);
    }
    else if (valPrev == 0)
    {
        return 0;
    }
    else
    {
        return -gmat.Log10(-valPrev);
    }
}


TSXformAdd::TSXformAdd(const VecStr & params)
: m_add(CharManipulations().ToDouble(params.at(0)))
{
}
double TSXformAdd::Run(const TSFunBase & input, int idx, double valPrev) const
{
    return valPrev + m_add;
}
