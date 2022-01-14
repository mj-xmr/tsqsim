#include "PredictorRCustom.h"

#ifdef USE_R
#include <Rinternals.h>
#include <Rembedded.h>
#endif //USE_R

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
