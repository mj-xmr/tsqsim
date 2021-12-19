#include "IPredictor.h"

using namespace EnjoLib;

IPredictor::IPredictor(){}
IPredictor::~IPredictor(){}

double IPredictor::PredictNext(const EnjoLib::VecD & data, size_t idx) const
{
    if (idx >= data.size())
    {
        return 0;
    }
    const VecD & ret = Predict(data, idx, 1);
    return ret.at(0);
}

EnjoLib::VecD IPredictor::PredictNextVec(const EnjoLib::VecD & data) const
{
    VecD ret;
    for (size_t i = 0; i < data.size(); ++i)
    {
        const double pred = PredictNext(data, i);
        ret.Add(pred);
    }
    return ret;
}
