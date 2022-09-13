#include "PredictorSMAMA.h"

#include "PredictorUtil.h"
#include "ITSFun.h"

//#include <Util/CoutBuf.hpp>
#include <Template/AlgoSTDThin.hpp>

using namespace EnjoLib;

PredictorSMAMA::PredictorSMAMA(const IDataProvider & dat)
: PredictorBase(dat, "SMAMA_MA")
, m_lagMine(dat, "LAG_SMAMA", true, 10, 1, 150, 1)
{
    AddOptiVar(m_lagMine);
}
PredictorSMAMA::~PredictorSMAMA(){}

/*
EnjoLib::VecD PredictorSMAMA::PredictVec(const EnjoLib::VecD & data) const
{
    const int numSamplesSma = m_lagMine.GetVal(); //
    const int numSamplesMA  = GetLag1().GetVal(); // ParQ
    const PredictorUtil util;
    const EnjoLib::VecD & predSma = util.SimpleMA(numSamplesSma, data);
    const EnjoLib::VecD & errors = util.GetErrorsCorrected(predSma, data);
    const EnjoLib::VecD & predMA = util.Regression(numSamplesMA, errors);
    const EnjoLib::VecD & SMAMA = predSma;// + predMA;

    return SMAMA;
}
*/

double PredictorSMAMA::PredictNext(const BufferDouble & datExpanding) const
{
    const int numSamplesSma = m_lagMine.GetVal(); //
    const int numSamplesMA  = GetLag1().GetVal(); // ParQ
    const int lags = GetLags();
    if (datExpanding.Len() < lags + numSamplesSma)
    {
        return IPredictor::ERROR;
    }
    const PredictorUtil util;

    
    VecD ret;
    for (int lag = 0; lag < lags; ++lag)
    {
        const EnjoLib::VecD & predSma = util.SimpleMA(numSamplesSma, datExpanding.GetData());
        const EnjoLib::VecD & errors = util.GetErrorsCorrected(predSma, datExpanding.GetData());
        //const EnjoLib::VecD & predVec = PredictorUtil().RegressionProt(lag, datExpanding.GetData(), datExpanding.Len(), false);
        //const double pred = predVec.Last();
        const double pred = PredictorUtil().RegressionProt(lag, errors, errors.size(), false);
        ret.Add(pred);
        //LOGL << "Pred lag " << lag << " = " << pred << ", ret = " << ret.Mean() << Nl;
    }
    return ret.Mean();
    
    //const VecD & vec = PredictVec(datExpanding.GetData());
    //return vec.Last();
}

unsigned PredictorSMAMA::GetLags() const
{
    return AlgoSTDThin().Max(m_lagMine.GetVal(), GetLag1().GetVal());
}
