#include "PredictorAR.h"
#include "PredictorUtil.h"
#include "ITSFun.h"

//#include <Util/CoutBuf.hpp>

using namespace EnjoLib;

PredictorAR::PredictorAR(){}
PredictorAR::~PredictorAR(){}

EnjoLib::VecD PredictorAR::Predict(const EnjoLib::VecD & data) const
{
    const int numSamples = GetLags();
    const EnjoLib::VecD & predAR = PredictorUtil().Regression(numSamples, data, false);
    return predAR;
}

unsigned PredictorAR::GetLags() const
{
    return 10;
}