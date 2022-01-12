#include "PredictorExperimental.h"

#include "PredictorBaseline.h"

PredictorExperimental:: PredictorExperimental(const IDataProvider & dat) : PredictorBase(dat, "EXP") {}
PredictorExperimental::~PredictorExperimental(){}


EnjoLib::VecD PredictorExperimental::Predict(const EnjoLib::VecD & data) const
{
    return PredictorBaseline(GetDat()).Predict(data);
}


unsigned PredictorExperimental::GetLags() const
{
    return PredictorBaseline(GetDat()).GetLags();
}