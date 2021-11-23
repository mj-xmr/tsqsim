#include "Err.h"
#include "LabelML.h"

#include <Util/VecD.hpp>
#include <Statistical/Statistical.hpp>

#include <Math/GeneralMath.hpp>

using namespace EnjoLib;

Err::~Err(){}
Err::Err(const LabelML & laba, const VecD & targets)
{
    const VecD & vdiff = laba.targets - targets;
    diffSq = vdiff.SumSquares(); /// ?
    diff = vdiff.Sum(); /// ?
    rms = Statistical().RMS(vdiff);

    const VecD & diffPenalized = PenalizeOverestimation(vdiff);
    rmsPenalized = Statistical().RMS(diffPenalized);

    vecDiff = diffPenalized;
}

//double DTWWrap::Err::diffSq() const { return diff * diff;};
double Err::absol() const { return EnjoLib::GeneralMath().Fabs(diff);};
double Err::GetDefault() const
{
    //return 0;
    //return absol();
    //return diffSq;
    return rmsPenalized;
    return rms;
}

EnjoLib::VecD Err::PenalizeOverestimation(const EnjoLib::VecD & diff1) const
{
    EnjoLib::VecD ret;
    for (const double dou: diff1)
        ret.Add(PenalizeOverestimation(dou));
    return ret;
}

double Err::PenalizeOverestimation(double diff1) const
{
    const double MUL = 1.5;
    if (diff1 < 0)
    {
        return diff1 * MUL;
    }
    return diff1;
}
