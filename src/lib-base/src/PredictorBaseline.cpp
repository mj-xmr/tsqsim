#include "PredictorBaseline.h"

PredictorBaseline::PredictorBaseline(const IDataProvider & dat) : PredictorBase(dat, "Baseline") {}
PredictorBaseline::~PredictorBaseline(){}

/*
EnjoLib::VecD PredictorBaseline::PredictVec(const EnjoLib::VecD & data) const
{
    const int lags = GetLags();
    EnjoLib::VecD ret;
    //ret.reserve(horizon);
    for (int i = 0; i < lags; ++i)
    {
        //ret.Add(data.at(0));
        ret.Add(0);
        //ret.Add(data.at(i));
        
    }
    
    for (size_t i = lags; i < data.size(); ++i)
    {
        ret.Add(data.at(i - lags));
    }
    return ret;
}
*/
double PredictorBaseline::PredictNext(const BufferDouble & datExpanding) const
{
    return datExpanding[GetLags()];
}

unsigned PredictorBaseline::GetLags() const
{
    return 1;
}

PredictorBaseline2::PredictorBaseline2(const IDataProvider & dat) : PredictorBaseline(dat) {}
PredictorBaseline2::~PredictorBaseline2(){}
unsigned PredictorBaseline2::GetLags() const
{
    return 5;
}