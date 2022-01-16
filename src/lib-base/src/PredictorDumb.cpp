#include "PredictorDumb.h"

#include "PredictorBaseline.h"

PredictorDumb::PredictorDumb(const IDataProvider & dat)
: PredictorBase(dat, "Dumb")
{
}

PredictorDumb::~PredictorDumb()
{
}

EnjoLib::VecD PredictorDumb::PredictVec(const EnjoLib::VecD & data) const
{
    return PredictorBaseline(GetDat()).Predict(data) * 1.2;
}

double PredictorDumb::PredictNext(const BufferDouble & datExpanding) const
{
    return PredictorBaseline(GetDat()).PredictNext(datExpanding) * 1.2;
}

unsigned PredictorDumb::GetLags() const
{
    return PredictorBaseline(GetDat()).GetLags();
}