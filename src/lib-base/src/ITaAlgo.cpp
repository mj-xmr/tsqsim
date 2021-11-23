#include "ITaAlgo.h"

#include <Util/VecD.hpp>
#include <Util/VecF.hpp>

using namespace EnjoLib;

ITaAlgo::ITaAlgo(){}
ITaAlgo::~ITaAlgo(){}

EnjoLib::VecF ITaAlgo::Update(const DataOCHL & data) const 
{ return EnjoLib::VecF(); };

void ITaAlgo::UpdateVecLeading0(EnjoLib::VecF * vec)
{
    EnjoLib::VecF & ret = *vec;
    float firstNon0 = 0;
    int firstNon0i = 0;
    for (unsigned i = 0; i < ret.size(); ++i)
    {
        const float val = ret.at(i);
        if (val != 0)
        {
            firstNon0 = val;
            firstNon0i = i;
            break;
        }
    }
    if (firstNon0 == 0)
    {
        return;
    }
    for (int i = 0; i < firstNon0i; ++i)
    {
        ret.atw(i) = firstNon0;
    }
}

VecD ITaAlgo::Vec2VecD(const EnjoLib::VecF & vec)
{
    VecD ret;
    ret.reserve(vec.size());
    for (float d : vec)
        ret.push_back(d);
    return ret;
}

EnjoLib::VecF  ITaAlgo::VecD2Vec(const VecD & vec)
{
    EnjoLib::VecF ret;
    ret.reserve(vec.size());
    for (double d : vec)
        ret.push_back(d);
    return ret;
}

VecD ITaAlgo::VecDDiffs(const VecD & vec)
{
    return VecD(vec).Diffs();  
}

EnjoLib::VecF  ITaAlgo::VecDiffs (const EnjoLib::VecF & vec)
{
    return VecF(vec).Diffs();  
}

EnjoLib::VecF  ITaAlgo::VecLogSigned (const EnjoLib::VecF & vec)
{
    return VecF(vec).LogSigned();  
}
