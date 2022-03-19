#include "PredictorAR.h"
#include "PredictorUtil.h"
#include "ITSFun.h"

#include <Util/CoutBuf.hpp>

using namespace EnjoLib;

PredictorAR::PredictorAR(const IDataProvider & dat, const EnjoLib::Str & name)
: PredictorBase(dat, name)
{}

PredictorAR::~PredictorAR(){}

/*
EnjoLib::VecD PredictorAR::PredictVec(const EnjoLib::VecD & data) const
{
    const int numSamples = GetLags();
    const EnjoLib::VecD & predAR = PredictorUtil().Regression(numSamples, data, false);
    return predAR;
}
*/
double PredictorAR::PredictNext(const BufferDouble & datExpanding) const
{
    const int lags = GetLags();
    if (datExpanding.Len() < lags + 1)
    {
        return 0;
    }
    VecD ret;
    for (int lag = 0; lag < lags; ++lag)
    {
        //const EnjoLib::VecD & predVec = PredictorUtil().RegressionProt(lag, datExpanding.GetData(), datExpanding.Len(), false);
        //const double pred = predVec.Last();
        const double pred = PredictorUtil().RegressionProt(lag, datExpanding.GetData(), datExpanding.Len(), false);
        ret.Add(pred);
        //LOGL << "Pred lag " << lag << " = " << pred << ", ret = " << ret.Mean() << Nl;
    }
    return ret.Mean();
    
    //const VecD & vec = PredictVec(datExpanding.GetData());
    //return vec.Last();
}

unsigned PredictorAR::GetLags() const
{
    return 2;
    return GetLag1().GetVal();
}
