#include "PredictorTrue.h"

PredictorTrue::PredictorTrue(){}
PredictorTrue::~PredictorTrue(){}

EnjoLib::VecD PredictorTrue::Predict(const EnjoLib::VecD & data) const
{
    EnjoLib::VecD ret;
    //ret.reserve(horizon);
    //ret.Add(data.at(idx));
    return data;
}

unsigned PredictorTrue::GetLags() const
{
    return 0;
}