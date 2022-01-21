#include "ITSFun.h"
#include "TSRes.h"

ITSFun::ITSFun()
{
    //ctor
}

ITSFun::~ITSFun()
{
    //dtor
}

/*
EnjoLib::VecD ITSFun::ReconstructVec(const EnjoLib::VecD & input, const EnjoLib::Matrix & lost) const
{
    EnjoLib::VecD reconstr;
    for (int i = 0; i < int(input.size()); ++i)
    {
        const TSRes rec = Reconstruct(i, input, lost.at(i));
        reconstr.Add(rec.val);
    }
    return reconstr;
}
*/