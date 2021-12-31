#include "PredictorExperimental.h"

#include "PredictorBaseline.h"

PredictorExperimental:: PredictorExperimental(){}
PredictorExperimental::~PredictorExperimental(){}


EnjoLib::VecD PredictorExperimental::Predict(const EnjoLib::VecD & data) const
{
    return PredictorBaseline().Predict(data);
}


unsigned PredictorExperimental::GetLags() const
{
    return PredictorBaseline().GetLags();
}