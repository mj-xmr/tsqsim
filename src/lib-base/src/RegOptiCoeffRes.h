#ifndef REGOPTICOEFFRES_H
#define REGOPTICOEFFRES_H

#include "RegOptiBase.h"
#include <Util/VecF.hpp>

namespace boost
{
    namespace serialization
    {
        class access;
    }
}

struct RegOptiCoeffRes// : public RegOptiBase
{
    RegOptiCoeffRes(){}
    RegOptiCoeffRes(EnjoLib::VecF changes)
    : m_changes(changes){}

    bool IsValid() const { return m_changes.size(); }

    EnjoLib::VecF m_changes;


    friend class boost::serialization::access;
    // When the class Archive corresponds to an output archive, the
    // & operator is defined similar to <<.  Likewise, when the class Archive
    // is a type of input archive the & operator is defined similar to >>.
    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & m_changes.DataRW();
    }
};

#endif // REGOPTICOEFFRES_H
