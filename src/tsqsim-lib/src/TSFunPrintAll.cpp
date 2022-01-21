#include "TSFunPrintAll.h"

#include <Util/CoutBuf.hpp>

using namespace EnjoLib;

TSFunPrintAll::TSFunPrintAll(const TSInput & tsin)
: TSFunBase(tsin)
{
    //ctor
}

TSFunPrintAll::~TSFunPrintAll()
{
    //dtor
}

TSRes TSFunPrintAll::OnDataPointProt(int idx) const
{
    LOGL << idx << Nl;
    TSRes res(true);
    return res;
}

EnjoLib::VecD TSFunPrintAll::ReconstructVec(const EnjoLib::VecD & input, const EnjoLib::Matrix & lost) const
{
    return EnjoLib::VecD();
}
/*
TSRes TSFunPrintAll::Reconstruct(int idx, const EnjoLib::VecD & input, const EnjoLib::VecD & lost) const
{
    TSRes res(true);
    return res;
}
*/