#include "PredictorARMA.h"

#include "PredictorAR.h"
#include "PredictorUtil.h"
#include "ITSFun.h"

#include <Util/CoutBuf.hpp>

using namespace EnjoLib;

PredictorARMA::PredictorARMA(){}
PredictorARMA::~PredictorARMA(){}

EnjoLib::VecD PredictorARMA::Predict(const EnjoLib::VecD & data) const
{
    const int numSamplesMA  = GetLags();  // ParQ
    const PredictorUtil util;
    const EnjoLib::VecD & predAR = PredictorAR().Predict(data);
    const EnjoLib::VecD & errors = util.GetErrorsCorrected(predAR, data);
    const EnjoLib::VecD & predMA = util.Regression(numSamplesMA, errors);
    const EnjoLib::VecD & predARMA = predAR + predMA;

    return predARMA;
}

unsigned PredictorARMA::GetLags() const
{
    return 10;
}