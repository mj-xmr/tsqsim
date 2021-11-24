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
    res.val = val;// - 0.035;

    return res;
}

/// TODO: Inverse the transformation by applying m_xforms in a reverse order and calling Inverse();

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
