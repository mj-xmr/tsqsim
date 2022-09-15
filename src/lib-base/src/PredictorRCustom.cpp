#include "PredictorRCustom.h"

#include "ConfigMan.h"
#include "ConfigTS.h"
#include "RWrapper.h"

PredictorRCustom::PredictorRCustom(const IDataProvider & dat)
: PredictorBase(dat, "RCustom")
{
    //ctor
}

PredictorRCustom::~PredictorRCustom()
{
    //dtor
}


bool PredictorRCustom::IsCustomScript() const
{
    return true;
}

EnjoLib::VecD PredictorRCustom::PredictVec(const EnjoLib::VecD & data) const
{
    // Invoke a function in R
    RWrapper::source(gcfgMan.cfgTS->m_scriptPathTxtR);
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
    //return 1;
    return GetLag1().GetVal();
}
