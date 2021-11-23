#ifndef REGRESSIONRES_H
#define REGRESSIONRES_H

#include "typesVec.h"

namespace boost
{
    namespace serialization
    {
        class access;
    }
}

struct RegressionRes
{
    RegressionRes();
    virtual ~RegressionRes();

    EnjoLib::VecD coeffs;
    //std::vector<double> coeffs;
    double rms = 0;
    double merr = 0;
    bool IsValid() const { return not coeffs.empty(); }
    bool IsBullish() const;

    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & coeffs;
        ar & rms;
        ar & merr;
    }
};

#endif // REGRESSIONRES_H
