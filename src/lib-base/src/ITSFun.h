#ifndef ITSFUN_H
#define ITSFUN_H

#include "IHasCandles.h"
#include "IOptimizable.h"

#include <Util/VecFwd.hpp>
#include <Statistical/MatrixFwd.hpp>

class TSRes;
class ITSFun : public IHasCandles, public IOptimizable
{
    public:
        ITSFun();
        virtual ~ITSFun();

        virtual TSRes OnDataPoint(int idx) const = 0;
        //virtual TSRes Reconstruct(int idx, const EnjoLib::VecD & input, const EnjoLib::VecD & lost) const = 0;
        virtual EnjoLib::VecD ReconstructVec(const EnjoLib::VecD & input, const EnjoLib::Matrix & lost) const = 0;
        virtual const char * GetName() const = 0;
        virtual void SetSilent() = 0;

    protected:

    private:
};

#endif // ITSFUN_H
