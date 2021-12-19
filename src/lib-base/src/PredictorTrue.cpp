#include "PredictorTrue.h"

PredictorTrue::PredictorTrue(){}
PredictorTrue::~PredictorTrue(){}

EnjoLib::VecD PredictorTrue::Predict(const EnjoLib::VecD & data, size_t idx, int horizon) const
{
    EnjoLib::VecD ret;
    ret.reserve(horizon);
    ret.Add(data.at(idx));
    return ret;
}