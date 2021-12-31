#include "PredictorDumb.h"

#include "PredictorBaseline.h"

PredictorDumb::PredictorDumb()
{
}

PredictorDumb::~PredictorDumb()
{
}

EnjoLib::VecD PredictorDumb::Predict(const EnjoLib::VecD & data) const
{
    return PredictorBaseline().Predict(data) * 1.2;
}

unsigned PredictorDumb::GetLags() const
{
    return PredictorBaseline().GetLags();
}