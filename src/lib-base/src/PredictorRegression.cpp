#include "PredictorRegression.h"

#include "PredictorBaseline.h" /// TODO: Remove and replace with something serious

#include "Regression.hpp"
#include <Util/CoutBuf.hpp>

using namespace EnjoLib;

PredictorRegression::PredictorRegression(){}
PredictorRegression::~PredictorRegression(){}

EnjoLib::VecD PredictorRegression::Predict(const EnjoLib::VecD & data, size_t idx, int horizon) const
{
    EnjoLib::Regression reg;
    const int degree = 2;
    const int numSamples = 3;
    EnjoLib::VecD vdx;
    EnjoLib::VecD vdy;

    for (int i = int(idx) - numSamples; i < int(idx); ++i)
    {
        if (i < 0)
        {
            return Erratic(data, idx, horizon);
        }
        vdx.Add(i);
        vdy.Add(data.at(i));
    }

    const RegressionRes & res = reg.polynomialfitRMS(degree, vdx, vdy);
    if (! res.IsValid())
    {
        return Erratic(data, idx, horizon);
    }
    EnjoLib::VecD vxx;
    for (int i = idx - horizon; i < int(idx); ++i)
    {
        vxx.Add(i); /// TODO: Check if indices are OK. Ideally limit the access to the information, just like the XForm has.
    }
    //{LOGL << "res.coeffs = " << res.coeffs.Print() << " vxx = " << vxx.Print() << Nl;}
    const EnjoLib::VecD & rets = reg.GetValuesForCoeffs(vxx, res.coeffs);
    return rets;
}

EnjoLib::VecD PredictorRegression::Erratic(const EnjoLib::VecD & data, size_t idx, int horizon) const
{
    return PredictorBaseline().Predict(data, idx, horizon);
}
