#include "PredictorTrue.h"

PredictorTrue::PredictorTrue(const IDataProvider & dat)
 : PredictorBase(dat, "True")
{}
PredictorTrue::~PredictorTrue(){}

/*
EnjoLib::VecD PredictorTrue::PredictVec(const EnjoLib::VecD & data) const
{
    EnjoLib::VecD ret;
    //ret.reserve(horizon);
    //ret.Add(data.at(idx));
    return data;
}
*/
double PredictorTrue::PredictNext(const BufferDouble & datExpanding) const
{
    return datExpanding[0];
}

unsigned PredictorTrue::GetLags() const
{
    return 0;
}