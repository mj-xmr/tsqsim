#include "PredictorRBaseline.h"

#include "ConfigDirs.h"
#include "RWrapper.h"

const char * PredictorRBaseline::SCRIPT_NAME = "r-baseline.R";

PredictorRBaseline::PredictorRBaseline(const IDataProvider & dat)
: PredictorBase(dat, "RBaseline")
{
}

PredictorRBaseline::~PredictorRBaseline()
{
}

EnjoLib::VecD PredictorRBaseline::PredictVec(const EnjoLib::VecD & data) const
{
    // Invoke a function in R
    RWrapper::source(ConfigDirs().DIR_SCRIPTS2 + SCRIPT_NAME);
    const EnjoLib::VecD & ret = RWrapper::R_predictVec(data);
    
    return ret;
}

double PredictorRBaseline::PredictNext(const BufferDouble & datExpanding) const
{
    const EnjoLib::VecD & vec = PredictVec(datExpanding.GetData());
    return vec.Last();
}

unsigned PredictorRBaseline::GetLags() const
{
    return 1;
}
