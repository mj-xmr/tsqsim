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
