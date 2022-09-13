#ifndef VECFILTERSTPL_H
#define VECFILTERSTPL_H

#include <Util/VecFwd.hpp>

class VecFiltersTpl
{
    public:
        VecFiltersTpl();
        virtual ~VecFiltersTpl();

        EnjoLib::VecD Smooth(const EnjoLib::VecD & inp, int smoothPer) const;

    protected:

    private:
};

#endif // VECFILTERSTPL_H
