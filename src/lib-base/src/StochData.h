#ifndef STOCHDATA_H
#define STOCHDATA_H

#include <Util/VecF.hpp>
//#include <deque>

class StochData
{
    public:
        EnjoLib::VecF slowK, slowD;
        //std::deque<float> slowK, slowD;
};

#endif // STOCHDATA_H
