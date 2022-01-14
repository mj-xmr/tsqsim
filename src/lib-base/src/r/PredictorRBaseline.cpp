#include "PredictorRBaseline.h"

#include <Rinternals.h>
#include <Rembedded.h>

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
