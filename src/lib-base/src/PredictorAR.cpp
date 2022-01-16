#include "PredictorAR.h"
#include "PredictorUtil.h"
#include "ITSFun.h"

//#include <Util/CoutBuf.hpp>

using namespace EnjoLib;

PredictorAR::PredictorAR(const IDataProvider & dat, const EnjoLib::Str & name)
: PredictorBase(dat, name)
{}

PredictorAR::~PredictorAR(){}

EnjoLib::VecD PredictorAR::PredictVec(const EnjoLib::VecD & data) const
{
    const int numSamples = GetLags();
    const EnjoLib::VecD & predAR = PredictorUtil().Regression(numSamples, data, false);
    return predAR;
}

double PredictorAR::PredictNext(const BufferDouble & datExpanding) const
{
    const VecD & vec = PredictVec(datExpanding.GetData());
    return vec.Last();
}

unsigned PredictorAR::GetLags() const
{
    //return 11;
    return GetLag1().GetVal();
}
