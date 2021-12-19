#include "PredictorStats.h"
#include "PredictorFactory.h"
#include "PredictorType.h"

#include <Statistical/Statistical.hpp>
#include <Ios/Osstream.hpp>
#include <Ios/IoManip.hpp>

using namespace EnjoLib;

PredictorStats::PredictorStats(){}
PredictorStats::~PredictorStats(){}

EnjoLib::Str PredictorStats::GenRepNext(const EnjoLib::VecD & truth, const EnjoLib::VecD & pred) const
{
    const Statistical stat;
    CorPtr<IPredictor> algoBaseline = PredictorFactory().Create(PredictorType::PRED_BASELINE);
    const EnjoLib::VecD & predBaseline = algoBaseline->PredictNextVec(truth);

    const double rmsBase2Truth  = stat.RMSTwo(predBaseline, truth);
    const double rmsPred2Base   = stat.RMSTwo(pred, predBaseline);
    const double rmsPred2Truth  = stat.RMSTwo(pred, truth);

    double ratioPred2Base = 0;
    if (rmsBase2Truth != 0)
    {
        ratioPred2Base = rmsPred2Truth / rmsBase2Truth;
    }

    Osstream oss;
    oss << IoManip::SetPrecision(oss, 3);
    oss << "Prediction scores:";
    oss << "\nRMS Base 2 True\t = "  << rmsBase2Truth;
    oss << "\nRMS Pred 2 True\t = "  << rmsPred2Truth << " -> ";
    oss << (rmsPred2Truth > rmsBase2Truth ? "Worse :(" : "Better! ^_^") << " than the baseline.";
    //oss << "\nRMS Pred 2 Base\t = " << rmsPred2Base;
    oss << "\nRatio Pred2Base\t = " << ratioPred2Base << Nl;
    return oss.str();
}
