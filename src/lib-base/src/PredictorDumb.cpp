#include "PredictorDumb.h"

#include "PredictorBaseline.h"

PredictorDumb::PredictorDumb(const IDataProvider & dat)
: PredictorBase(dat, "Dumb")
{
}

PredictorDumb::~PredictorDumb()
{
}

EnjoLib::VecD PredictorDumb::Predict(const EnjoLib::VecD & data) const
{
    return PredictorBaseline(GetDat()).Predict(data) * 1.2;
}

unsigned PredictorDumb::GetLags() const
{
    return PredictorBaseline(GetDat()).GetLags();
}