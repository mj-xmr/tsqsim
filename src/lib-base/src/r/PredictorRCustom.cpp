#include "PredictorRCustom.h"

PredictorRCustom::PredictorRCustom(const IDataProvider & dat)
: PredictorBase(dat, "RCustom")
{
    //ctor
}

PredictorRCustom::~PredictorRCustom()
{
    //dtor
}

EnjoLib::VecD PredictorRCustom::Predict(const EnjoLib::VecD & data) const
{
    return data;
}

unsigned PredictorRCustom::GetLags() const
{
    return 1;
}
