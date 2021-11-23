#ifndef VECFILTERS_H
#define VECFILTERS_H

#include <typesVec.h>

namespace EnjoLib
{
    class VecD;
}

class VecFilters
{
    public:
        VecFilters();
        virtual ~VecFilters(){}

        EnjoLib::VecF Smooth(const EnjoLib::VecF & inp, int smoothPer) const;
        EnjoLib::VecD Smooth(const EnjoLib::VecD & inp, int smoothPer) const;
        EnjoLib::VecD Changes(const EnjoLib::VecD & inp) const;
        EnjoLib::VecF VectorDToVec(const EnjoLib::VecD & evec) const;

    protected:

    private:
};

#endif // VECFILTERS_H
