#include "TSFunTxt.h"

#include "Candle.h"
#include "TSInput.h"
#include "ConfigTS.h"

#include <Ios/Ifstream.hpp>
//#include <Math/GeneralMath.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Tokenizer.hpp>
//#include <Util/CharManipulations.hpp>
#include <Template/CorradePointer.h>
#include <Statistical/Assertions.hpp>

using namespace EnjoLib;

TSFunTxt::TSFunTxt(const TSInput & tsin)
: TSFunBase(tsin)
{
    ELO
       
    //const CharManipulations cman;
    const Tokenizer tok;
    const Str & fname = tsin.m_cfgTS.m_scriptPathTxt;

    { Ifstream file(fname); } /// TODO: Move functionality to tok.GetLine
    LOG << "Reading script file: '" << fname << "'" << Nl;
    const VecStr & lines = tok.GetLines(fname);
    for (const Str & line : tok.FilterLines(lines))
    {
        LOG << "Script line: '" << line << "'" << Nl;
        m_xformMan.AddXForm(line);
    }
}

TSFunTxt::~TSFunTxt(){}

TSRes TSFunTxt::OnDataPointProt(int idx) const
{
    return m_xformMan.OnDataPointProt(*this, idx);
}

TSRes TSFunTxt::Reconstruct(int idx, const EnjoLib::VecD & input, const EnjoLib::VecD & lost) const
{
    return m_xformMan.Reconstruct(input.at(idx), lost);
}

unsigned TSFunTxt::LenProt() const
{
    const unsigned shiftXForms = m_xformMan.MaxShift();
    return LenData() - shiftXForms;
}
