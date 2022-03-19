#include "PredictorUtil.h"

#include "PredictorBaseline.h"

#include "Regression.hpp"
#include <Util/CoutBuf.hpp>

using namespace EnjoLib;

PredictorUtil::PredictorUtil(){}
PredictorUtil::~PredictorUtil(){}

EnjoLib::VecD PredictorUtil::Regression(int numSamples, const EnjoLib::VecD & data, bool erratic0) const
{
    EnjoLib::VecD ret;
    for (size_t i = 0; i < data.size(); ++i)
    {
        ret.Add(RegressionProt(numSamples, data, i, erratic0));
    }
    return ret;
}

EnjoLib::VecD PredictorUtil::SimpleMA  (int numSamples, const EnjoLib::VecD & data, bool erratic0) const
{
    EnjoLib::VecD ret;
    for (size_t i = 0; i < data.size(); ++i)
    {
        ret.Add(SimpleMAProt(numSamples, data, i, erratic0));
        //ret.Add(RegressionProt(numSamples, data, i, erratic0));
    }
    return ret;
}

double PredictorUtil::SimpleMAProt  (int numSamples, const EnjoLib::VecD & data, size_t idx, bool erratic0) const
{
    EnjoLib::VecD vdx;
    EnjoLib::VecD vdy;

    for (int i = int(idx) - numSamples; i < int(idx); ++i)
    {
        if (i < 0)
        {
            return Erratic(data, idx, erratic0);
        }
        vdx.Add(i);
        vdy.Add(data.at(i));
    }
    const double mean = vdy.Mean();
    //return vdy.back();
    return mean;
}

double  PredictorUtil::RegressionProt(int lag, const EnjoLib::VecD & data, size_t idx,  bool erratic0) const
{
    EnjoLib::Regression reg;
    const int degree = 2;
    EnjoLib::VecD vdx;
    EnjoLib::VecD vdy;

    //for (int i = int(idx) - numSamples; i < int(idx); ++i)
    for (int i = 0; i < int(idx) - lag; ++i)
    {
        if (i < 0)
        {
            return Erratic(data, idx, erratic0);
        }
        vdx.Add(i);
        vdy.Add(data.at(i));
    }
    if (vdx.empty())
    {
        //return Erratic(data, idx, erratic0); /// TODO: Is OK.
    }

    const RegressionRes & res = reg.polynomialfitRMS(degree, vdx, vdy);
    if (! res.IsValid())
    {
        return Erratic(data, idx, erratic0);
    }
    EnjoLib::VecD vxx;
    //for (int i = idx - horizon; i < int(idx); ++i)
    {
        /// TODO: Check if indices are OK. Ideally limit the access to the information, just like the XForm has.
        //vxx.Add(i);
    }
    vxx.Add(idx + 1);
    //{LOGL << "res.coeffs = " << res.coeffs.Print() << " vxx = " << vxx.Print() << Nl;}
    //const EnjoLib::VecD & rets = reg.GetValuesForCoeffs(vxx, res.coeffs);
    //return rets.at(0);
    const double ret = reg.GetValueForCoeffs(idx + 1, res.coeffs);
    return ret;
}

double PredictorUtil::Erratic(const EnjoLib::VecD & data, size_t idx, bool erratic0) const
{
    return 0; /// TODO: Decide it it's OK. So far everything would suggest so.
    
    if (true)
    //if (erratic0)
    {
        //return 0; /// TODO: Decide it it's OK. So far everything would suggest so.
    }
    else
    {
        //return PredictorBaseline().Predict(data).at(idx);
    }
}

EnjoLib::VecD PredictorUtil::GetErrorsCorrected(const EnjoLib::VecD & pred, const EnjoLib::VecD & data) const
{
    EnjoLib::VecD errorsCorrected = pred - data;
    for (size_t i = 0; i < errorsCorrected.size(); ++i)
    {
        if (pred.at(i) == 0)
        {
            errorsCorrected.at(i) = 0;
        }
        //break;
    }
    return errorsCorrected;
}
