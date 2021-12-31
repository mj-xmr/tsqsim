#include "PredictorSMAMA.h"

#include "PredictorUtil.h"
#include "ITSFun.h"

//#include <Util/CoutBuf.hpp>

using namespace EnjoLib;

PredictorSMAMA::PredictorSMAMA(){}
PredictorSMAMA::~PredictorSMAMA(){}

EnjoLib::VecD PredictorSMAMA::Predict(const EnjoLib::VecD & data) const
{
    const int numSamplesSma = GetLags(); // 
    const int numSamplesMA  = GetLags();  // ParQ
    const PredictorUtil util;
    const EnjoLib::VecD & predSma = util.SimpleMA(numSamplesSma, data);
    const EnjoLib::VecD & errors = util.GetErrorsCorrected(predSma, data);
    const EnjoLib::VecD & predMA = util.Regression(numSamplesMA, errors);
    const EnjoLib::VecD & SMAMA = predSma + predMA;

    return SMAMA;
}

unsigned PredictorSMAMA::GetLags() const
{
    return 10;
}