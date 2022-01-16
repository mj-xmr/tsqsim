#include "PredictorRCustom.h"

#include "ConfigDirs.h"
#include "RWrapper.h"

const char * PredictorRCustom::SCRIPT_NAME = "r-custom.R";

PredictorRCustom::PredictorRCustom(const IDataProvider & dat)
: PredictorBase(dat, "RCustom")
{
    //ctor
}

PredictorRCustom::~PredictorRCustom()
{
    //dtor
}

EnjoLib::VecD PredictorRCustom::PredictVec(const EnjoLib::VecD & data) const
{
    // Invoke a function in R
    RWrapper::source(ConfigDirs().DIR_SCRIPTS2 + SCRIPT_NAME);
    const EnjoLib::VecD & ret = RWrapper::R_predictVec(data);
    
    return ret;
}

double PredictorRCustom::PredictNext(const BufferDouble & datExpanding) const
{
    const EnjoLib::VecD & vec = PredictVec(datExpanding.GetData());
    return vec.Last();
}

unsigned PredictorRCustom::GetLags() const
{
    return 1;
}
