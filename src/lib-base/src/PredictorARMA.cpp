#include "PredictorARMA.h"

#include "PredictorUtil.h"
#include "ITSFun.h"

#include <Util/CoutBuf.hpp>
#include <Template/AlgoSTDThin.hpp>

using namespace EnjoLib;

PredictorARMA::PredictorARMA(const IDataProvider & dat)
: PredictorBase(dat, "ARMA")
, m_predAR(dat, "ARMA_AR")
{
    AddOptiVars(m_predAR);
}
PredictorARMA::~PredictorARMA(){}

EnjoLib::VecD PredictorARMA::Predict(const EnjoLib::VecD & data) const
{
    const int numSamplesMA  = GetLag1().GetVal();  // ParQ
    const PredictorUtil util;
    const EnjoLib::VecD & predAR = m_predAR.Predict(data);
    const EnjoLib::VecD & errors = util.GetErrorsCorrected(predAR, data);
    const EnjoLib::VecD & predMA = util.Regression(numSamplesMA, errors);
    const EnjoLib::VecD & predARMA = predAR + predMA;

    return predARMA;
}

unsigned PredictorARMA::GetLags() const
{
    return AlgoSTDThin().Max(m_predAR.GetLags(), unsigned(GetLag1().GetVal()));
}