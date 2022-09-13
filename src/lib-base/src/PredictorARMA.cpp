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

/*
EnjoLib::VecD PredictorARMA::PredictVec(const EnjoLib::VecD & data) const
{
    const int numSamplesMA  = GetLag1().GetVal();  // ParQ
    const PredictorUtil util;
    const EnjoLib::VecD & predAR = m_predAR.Predict(data);
    const EnjoLib::VecD & errors = util.GetErrorsCorrected(predAR, data);
    const EnjoLib::VecD & predMA = util.Regression(numSamplesMA, errors);
    const EnjoLib::VecD & predARMA = predAR + predMA;

    return predARMA;
}
*/
double PredictorARMA::PredictNext(const BufferDouble & datExpanding) const
{
    const int lags = GetLags();
    if (datExpanding.Len() < lags + 1)
    {
        return 0;
    }
    const PredictorUtil util;
    VecD ret;
    for (int lag = 0; lag < lags; ++lag)
    {
        const EnjoLib::VecD & predAR = m_predAR.Predict(datExpanding.GetData());
        const EnjoLib::VecD & errors = util.GetErrorsCorrected(predAR, datExpanding.GetData());
        //const EnjoLib::VecD & predVec = PredictorUtil().RegressionProt(lag, datExpanding.GetData(), datExpanding.Len(), false);
        //const double pred = predVec.Last();
        const double pred = PredictorUtil().RegressionProt(lag, datExpanding.GetData(), datExpanding.Len(), false);
        ret.Add(pred);
        //LOGL << "Pred lag " << lag << " = " << pred << ", ret = " << ret.Mean() << Nl;
    }
    return ret.Mean();
    
    //const VecD & vec = PredictVec(datExpanding.GetData());
    //return vec.Last();
    
    //const VecD & vec = PredictVec(datExpanding.GetData());
    //return vec.Last();
}

unsigned PredictorARMA::GetLags() const
{
    return AlgoSTDThin().Max(m_predAR.GetLags(), unsigned(GetLag1().GetVal()));
}