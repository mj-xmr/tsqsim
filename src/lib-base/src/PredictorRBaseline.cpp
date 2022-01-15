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

EnjoLib::VecD PredictorRBaseline::Predict(const EnjoLib::VecD & data) const
{
    // Invoke a function in R
    RWrapper::source(ConfigDirs().DIR_SCRIPTS2 + SCRIPT_NAME);
    const EnjoLib::VecD & ret = RWrapper::R_predictVec(data);
    
    return ret;
}

unsigned PredictorRBaseline::GetLags() const
{
    return 1;
}
