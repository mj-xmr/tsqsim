#ifndef REGOPTIRMS2LENRES_H
#define REGOPTIRMS2LENRES_H

#include "RegOptiBase.h"

namespace boost {namespace serialization
{
    class access;
}}

struct RegOptiRMS2LenRes : public RegOptiBase
{
    RegOptiRMS2LenRes(){}
    RegOptiRMS2LenRes(int diffPastFuture, int degree, float rms, float rmsRel, bool bullish)
    : diffPastFuture(diffPastFuture), degree(degree), rmsRel(rmsRel), bullish(bullish) {}
    int diffPastFuture = 0;
    int degree = 2;
    float rms = 0;
    float rmsRel = 0;
    bool bullish = false;

    int GetDiffPastFuture() const override { return diffPastFuture; }

    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & diffPastFuture;
        ar & degree;
        ar & rms;
        ar & rmsRel;
        ar & bullish;
    }
};

#endif // REGOPTIRMS2LENRES_H
