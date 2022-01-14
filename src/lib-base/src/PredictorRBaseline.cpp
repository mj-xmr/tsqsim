#include "PredictorRBaseline.h"

#ifdef USE_R
#include <Rinternals.h>
#include <Rembedded.h>
#endif //USE_R

PredictorRBaseline::PredictorRBaseline(const IDataProvider & dat)
: PredictorBase(dat, "RBaseline")
{
    //ctor
}

PredictorRBaseline::~PredictorRBaseline()
{
    //dtor
}

EnjoLib::VecD PredictorRBaseline::Predict(const EnjoLib::VecD & data) const
{
    return data;
}

unsigned PredictorRBaseline::GetLags() const
{
    return 1;
}
