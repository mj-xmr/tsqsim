#include "PredictorBaseline.h"


PredictorBaseline::PredictorBaseline(){}
PredictorBaseline::~PredictorBaseline(){}

EnjoLib::VecD PredictorBaseline::Predict(const EnjoLib::VecD & data, size_t idx, int horizon) const
{
    EnjoLib::VecD ret;
    ret.reserve(horizon);
    if (idx == 0)
    {
        ret.Add(data.at(idx));
    }
    else
    {
        ret.Add(data.at(idx - 1));
    }
    return ret;
}