#ifndef DTWWRAP_H
#define DTWWRAP_H

#include "LabelML.h"
#include "types.h"

#include <Util/VecD.hpp>
#include <Math/MaxMinFindF.hpp>
#include <Template/ArrayFwd.hpp>

namespace EnjoLib
{
    class ScalingOpStandardize;
}

enum class DTWDistType;
class Err;
class State;
class IBufferCandles;
class IModel;

class DTWWrap
{
    public:
        DTWWrap();
        virtual ~DTWWrap();

        EnjoLib::VecD GetMinDist(int i, const DateInt & date, const DTWDistType & type, const EnjoLib::VecD & obsNew, const IModel & mod, 
                                    const IBufferCandles & bufCan, const EnjoLib::Array<LabelML> & knnLabs, const Mask & mask) const;
        //EnjoLib::MaxMinFindF GetMinDistKNN(const EnjoLib::VecD & obsNew, const stdfwd::vector<LabelML> & knnLabs, const VecB & mask) const;
        Err GetError(const LabelML & laba, const EnjoLib::VecD & targets) const;

    protected:

    private:
};

#endif // DTWWRAP_H
