#ifndef REGOPTIZZRES_H
#define REGOPTIZZRES_H

#include "RegOptiBase.h"
#include "RegressionPars.h"
#include <Template/Array.hpp>

namespace boost { namespace serialization
{
    class access; }
}

struct RegOptiZZRes : public RegOptiBase
{
    ~RegOptiZZRes(){}
    RegOptiZZRes(){}
    RegOptiZZRes(const RegressionPars & regPars, int pastOpti)
    : diffPastFuture(pastOpti - regPars.future) /// TODO: library code!
    , degree(0), rmsRel(0), bullish(0) {}
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

struct RegOptiZZResVec
{
    ~RegOptiZZResVec(){}
    RegOptiZZResVec(){}
    RegOptiZZResVec(const STDFWD::vector<RegOptiZZRes> & res);

    //std::vector<RegOptiZZRes> vres;
    EnjoLib::Array<RegOptiZZRes> vres;

    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & vres;
    }
};

#endif // REGOPTIZZRES_H
