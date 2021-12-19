#include "PredictorStats.h"
#include "PredictorFactory.h"
#include "PredictorType.h"

#include <Ios/Osstream.hpp>
#include <Ios/IoManip.hpp>
#include <Math/GeneralMath.hpp>
#include <Util/ToolsMixed.hpp>
#include <Statistical/Statistical.hpp>

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

    double ratioPred2Base = 0, points = 0;
    if (rmsBase2Truth != 0)
    {
        ratioPred2Base = rmsPred2Truth / rmsBase2Truth;
        points = GMat().round((1 - ratioPred2Base) * 100);
    }

    Osstream oss;
    oss << IoManip::SetPrecision(oss, 3);
    oss << "Prediction scores:";
    oss << "\nRMS Base 2 True\t = "  << rmsBase2Truth;
    oss << "\nRMS Pred 2 True\t = "  << rmsPred2Truth << " -> ";
    oss << (rmsPred2Truth > rmsBase2Truth ? ":( Worse" : "^_^ Better!") << " than the baseline.";
    //oss << "\nRMS Pred 2 Base\t = " << rmsPred2Base;
    oss << "\nRatio Pred2Base\t = " << ratioPred2Base << " " << ToolsMixed().GenBars10(points) << Nl;
    return oss.str();
}
