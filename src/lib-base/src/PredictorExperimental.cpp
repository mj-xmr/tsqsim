#include "PredictorExperimental.h"

#include "PredictorBaseline.h"

PredictorExperimental:: PredictorExperimental(const IDataProvider & dat) : PredictorBase(dat, "EXP") {}
PredictorExperimental::~PredictorExperimental(){}


EnjoLib::VecD PredictorExperimental::PredictVec(const EnjoLib::VecD & data) const
{
    return PredictorBaseline(GetDat()).Predict(data);
}

double PredictorExperimental::PredictNext(const BufferDouble & datExpanding) const
{
    return PredictorBaseline(GetDat()).PredictNext(datExpanding);
}

unsigned PredictorExperimental::GetLags() const
{
    return PredictorBaseline(GetDat()).GetLags();
}
