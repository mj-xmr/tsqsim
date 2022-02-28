#include "PredictorStats.h"
#include "PredictorFactory.h"
#include "PredictorType.h"

#include <Ios/Osstream.hpp>
#include <Ios/IoManip.hpp>
#include <Math/GeneralMath.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/ToolsMixed.hpp>
#include <Statistical/Statistical.hpp>

using namespace EnjoLib;

PredictorStats::PredictorStats(){}
PredictorStats::~PredictorStats(){}

EnjoLib::Str PredictorStats::GenRepNext(const EnjoLib::VecD & orig, const EnjoLib::VecD & predBaseline, const EnjoLib::VecD & pred, int offset) const
{
    const PredictorStatsRes & res = GenPoints(orig, predBaseline, pred, offset);
    return GenRepNext(res);
}

EnjoLib::Str PredictorStats::GenRepNext(const PredictorStatsRes & res) const
{

    Osstream oss;
    oss << IoManip::SetPrecision(oss, 3);
    oss << "Prediction scores:";
    oss << "\nRMS Base 2 True\t = "  << res.rmsBase2Truth;
    oss << "\nRMS Pred 2 True\t = "  << res.rmsPred2Truth << " -> ";
    oss << (res.rmsPred2Truth >= res.rmsBase2Truth ? ":( not better" : "^_^ Better!") << " than the baseline.";
    //oss << "\nRMS Pred 2 Base\t = " << rmsPred2Base;
    oss << "\nRatio Pred2Base\t = " << res.ratioPred2Base << " " << ToolsMixed().GenBars10(res.points) << Nl;
    return oss.str();
}

PredictorStatsRes PredictorStats::GenPoints(const EnjoLib::VecD & orig, const EnjoLib::VecD & predBaseline, const EnjoLib::VecD & pred, int offset) const
{
    const Statistical stat;
    PredictorStatsRes res{};

    EnjoLib::VecD predCorrected;
    //LOGL << "Offset " << offset << Nl;
    if (offset > 0)
    {
        predCorrected = pred;
        for (int i = 0; i < offset; ++i)
        {
            LOGL << "PredictorStats Correcting " << i+1 << Nl;
            predCorrected.pop_back();
            predCorrected.push_front(0);
            //predCorrected.pop_front();
            //predCorrected.push_back(0);
        }
    }
    else
    {
        predCorrected = pred;
    }

    res.rmsBase2Truth  = stat.RMSTwo(predBaseline,  orig); /// TODO: different readouts with diffs and without
    res.rmsPred2Base   = stat.RMSTwo(predCorrected, predBaseline);
    res.rmsPred2Truth  = stat.RMSTwo(predCorrected, orig);

    if (res.rmsBase2Truth != 0)
    {
        res.ratioPred2Base = res.rmsPred2Truth / res.rmsBase2Truth;
        res.points = GMat().round((1 - res.ratioPred2Base) * 100);
    }
    return res;
}
