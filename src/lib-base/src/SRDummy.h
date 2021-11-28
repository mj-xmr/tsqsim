#ifndef ISRDUMMY_H
#define ISRDUMMY_H

#include "ISR.h"
#include "SRFinal.h"
#include <Template/SafePtr.hpp>

class SRDummy : public ISR
{
    public:
        SRDummy();
        virtual ~SRDummy();

        EnjoLib::Array<SRFinal> GetLevels(const State & st, float bound1, float bound2, const SRFilterHolder * filter = nullptr) const override;
        EnjoLib::Array<SRFinal> GetLowerThan(const State & st, float lowerBound, const SRFilterHolder * filter = nullptr) const override;
        EnjoLib::Array<SRFinal> GetHigherThan(const State & st, float higherBound, const SRFilterHolder * filter = nullptr) const override;
        EnjoLib::Array<SRFinal> FilterBrokenOnly(const EnjoLib::Array<SRFinal> & levels) const override;
        EnjoLib::Array<SRFinal> SortClosestFurthest(Direction dir, const EnjoLib::Array<SRFinal> & levels) const override;
        EnjoLib::Array<SRFinal> Reverse(const EnjoLib::Array<SRFinal> & levels) const override;
        EnjoLib::Array<SRFinal> Fewer(const EnjoLib::Array<SRFinal> & levels, int maxNumElements) const override;

        const SRFinal::SrFinType & GetLevels(const State & st) const override { return *m_sup; };
        const SRFinal::SrFinType & GetSupport()  const override { return *m_sup; };
        const SRFinal::SrFinType & GetResistance()  const override { return *m_res; };

    protected:

    private:
        EnjoLib::SafePtr<STDFWD::multimap<float, SRFinal>> m_sup, m_res;
};

#endif // ISRDUMMY_H
