#include "PredictorSMAMA.h"

#include "PredictorUtil.h"
#include "ITSFun.h"

//#include <Util/CoutBuf.hpp>
#include <Template/AlgoSTDThin.hpp>

using namespace EnjoLib;

PredictorSMAMA::PredictorSMAMA(const IDataProvider & dat) 
: PredictorBase(dat, "SMAMA_MA") 
, m_lagMine(dat, "LAG_SMAMA", true, 10, 1, 20, 1)
{
    AddOptiVar(m_lagMine);
}
PredictorSMAMA::~PredictorSMAMA(){}

EnjoLib::VecD PredictorSMAMA::Predict(const EnjoLib::VecD & data) const
{
    const int numSamplesSma = m_lagMine.GetVal(); // 
    const int numSamplesMA  = GetLag1().GetVal();  // ParQ
    const PredictorUtil util;
    const EnjoLib::VecD & predSma = util.SimpleMA(numSamplesSma, data);
    const EnjoLib::VecD & errors = util.GetErrorsCorrected(predSma, data);
    const EnjoLib::VecD & predMA = util.Regression(numSamplesMA, errors);
    const EnjoLib::VecD & SMAMA = predSma + predMA;

    return SMAMA;
}

unsigned PredictorSMAMA::GetLags() const
{
    return AlgoSTDThin().Max(m_lagMine.GetVal(), GetLag1().GetVal());
}