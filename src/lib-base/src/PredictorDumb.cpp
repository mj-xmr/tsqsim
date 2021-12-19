#include "PredictorDumb.h"

#include "PredictorBaseline.h"

PredictorDumb::PredictorDumb()
{
}

PredictorDumb::~PredictorDumb()
{
}

EnjoLib::VecD PredictorDumb::Predict(const EnjoLib::VecD & data, size_t idx, int horizon) const
{
    return PredictorBaseline().Predict(data, idx, horizon) * 1.2;
}
