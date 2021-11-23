#ifndef ERR_HPP
#define ERR_HPP

#include <Util/VecD.hpp>

class LabelML;

struct Err
{
    Err(const LabelML & laba, const EnjoLib::VecD & targets);
    virtual ~Err();

    double diff = 0;
    double diffSq = 0;
    double rms = 0;
    double rmsPenalized = 0;
    double huber = 0;
    double logcos = 0;
    EnjoLib::VecD vecDiff;
    double absol() const;

    double GetDefault() const;
    double PenalizeOverestimation(double diff1) const;
    EnjoLib::VecD PenalizeOverestimation(const EnjoLib::VecD & diff1) const;
};




#endif // ERR_HPP
