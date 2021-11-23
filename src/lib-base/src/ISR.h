#ifndef ISR_H
#define ISR_H

#include "SRFinal.h"
#include "State.h"
#include <Template/ArrayFwd.hpp>
#include <3rdParty/stdfwd.hh>

class SRFilterHolder;

class ISR
{
    public:
        ISR();
        virtual ~ISR(){}

        virtual EnjoLib::Array<SRFinal> GetLevels(const State & st, float bound1, float bound2, const SRFilterHolder * filter = nullptr) const = 0;
        virtual EnjoLib::Array<SRFinal> GetLowerThan(const State & st, float higherBound, const SRFilterHolder * filter = nullptr) const = 0;
        virtual EnjoLib::Array<SRFinal> GetHigherThan(const State & st, float lowerBound, const SRFilterHolder * filter = nullptr) const = 0;
        virtual EnjoLib::Array<SRFinal> FilterBrokenOnly(const EnjoLib::Array<SRFinal> & levels) const = 0;
        virtual EnjoLib::Array<SRFinal> SortClosestFurthest(Direction dir, const EnjoLib::Array<SRFinal> & levels) const = 0;
        virtual EnjoLib::Array<SRFinal> Reverse(const EnjoLib::Array<SRFinal> & levels) const = 0;
        virtual EnjoLib::Array<SRFinal> Fewer(const EnjoLib::Array<SRFinal> & levels, int maxNumElements) const = 0;

        virtual const SRFinal::SrFinType & GetLevels(const State & st) const = 0;
        virtual const SRFinal::SrFinType & GetSupport() const = 0;
        virtual const SRFinal::SrFinType & GetResistance() const = 0;

    protected:

    private:
};

#endif // ISR_H
