#ifndef REGOPTIPREDICTABILITYRES_H
#define REGOPTIPREDICTABILITYRES_H

#include "RegOptiBase.h"

namespace boost
{
    namespace serialization
    {
        class access;
    }
}

class RegOptiPredictabilityRes : public RegOptiBase
{
    public:
        RegOptiPredictabilityRes() {}
        RegOptiPredictabilityRes(int diffPastFuture);
        virtual ~RegOptiPredictabilityRes(){}

        float a = 0;

    protected:
        int GetDiffPastFuture() const override { return m_diffPastFuture; }

    private:

        int m_diffPastFuture = 0;

        friend class boost::serialization::access;
        // When the class Archive corresponds to an output archive, the
        // & operator is defined similar to <<.  Likewise, when the class Archive
        // is a type of input archive the & operator is defined similar to >>.
        template<class Archive>
        void serialize(Archive & ar, const unsigned int version)
        {
            ar & m_diffPastFuture;
        }
};

#endif // REGOPTIPREDICTABILITYRES_H
