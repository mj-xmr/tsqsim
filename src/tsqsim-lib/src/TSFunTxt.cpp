#include "TSFunTxt.h"

#include "Candle.h"
#include "TSXformFactory.h"
#include "TSInput.h"
#include "ConfigTS.h"

#include <Ios/Ifstream.hpp>
//#include <Math/GeneralMath.hpp>
#include <Math/MaxMinFindF.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Tokenizer.hpp>
//#include <Util/CharManipulations.hpp>
#include <Template/CorradePointer.h>

using namespace EnjoLib;

TSFunTxt::TSFunTxt(const TSInput & tsin)
: TSFunBase(tsin)
{
    ELO
    //const CharManipulations cman;
    const Tokenizer tok;
    const TSXformFactory fact;

    const Str & fname = tsin.m_cfgTS.m_scriptPathTxt;

    { Ifstream file(fname); } /// TODO: Move functionality to tok.GetLine
    LOG << "Reading script file: '" << fname << "'" << Nl;
    const VecStr & lines = tok.GetLines(fname);
    for (const Str & line : tok.FilterLines(lines))
    {
        LOG << "Script line: '" << line << "'" << Nl;
        m_xforms.push_back(fact.Create(line));
    }
}

TSFunTxt::~TSFunTxt(){}

TSRes TSFunTxt::OnDataPointProt(int idx) const
{
    double val = 0;
    for (const auto & pxform : m_xforms)
    {
        val = pxform->Run(*this, idx, val);
    }

    TSRes res(true);
    res.val = val;

    return res;
}

TSRes TSFunTxt::Reconstruct(int idx, const EnjoLib::VecD & input, double prev) const
{
    bool verbose = true;
    verbose = false;

    double val = input.at(idx);
    for (int i = int(m_xforms.size() - 1); i >= 0; --i)
    {   // Iterate the transformations in the reverse order w.r.t. as they were applied
        const auto & pxform = m_xforms.at(i);
        VecD inVec;
        inVec.push_back(val);
        inVec.push_back(prev);
        val = pxform->Invert(inVec);
        if (verbose)
        {
            LOGL << idx << ":\txf = " << i << ", in = " << inVec.Print() << ", out = " << val << Nl;
        }
    }
    if (verbose)
    {
        LOGL << Nl;
    }

    TSRes res(true);
    res.val = val;
    return res;
}

unsigned TSFunTxt::LenProt() const
{
    MaxMinFindF mmf;
    unsigned shift = 0;
    for (const auto & pxform : m_xforms)
    {
        const unsigned maxShift = pxform->MaxShift();
        mmf.UpdateMax(maxShift);
    }
    if (mmf.IsMaxValid())
    {
        shift = mmf.GetMax();
    }
    return LenData() - shift;
}
