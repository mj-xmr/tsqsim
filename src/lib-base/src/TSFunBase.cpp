#include "TSFunBase.h"
#include "IPeriod.h"
#include "IBufferCandles.h"
#include "Candle.h"
#include "ConfigTS.h"
#include "OptiVarVec.h"

#include <Ios/Osstream.hpp>
#include <Util/Str.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/StrColour.hpp>
#include <Util/Except.hpp>
#include <Template/Array.hpp>

#include <STD/VectorCpp.hpp>

using namespace EnjoLib;

TSFunBase::~TSFunBase(){}
TSFunBase:: TSFunBase(const TSInput & tsin)
: m_tsin(tsin)
, m_per(tsin.m_per)
, m_bufCan(tsin.m_per.GetCandles())
, m_optiFloats(new OptiVarVec())
{
}

TSRes TSFunBase::OnDataPoint(int idx) const
{
    try
    {
        return OnDataPointProt(idx);
    }
    catch (std::exception & exc)
    {
        Osstream oss;
        oss << "TSFunBase::OnDataPoint: idx " << idx << Nl << exc.what();
        oss << "Is Len() overriden and adjusted?\n";
        oss << GetName() << Nl;
        const Str msg = oss.str();
        if (CrashOnWarning())
        {
            throw ExceptLengthError(msg); /// TODO: Rethrow
        }
        LOGL << EnjoLib::StrColour::GenWarn(msg) << EnjoLib::Nl;
        return TSRes(true);
    }
}

const TSInput & TSFunBase::GetTSIn() const
{
    return m_tsin;
}

const IPeriod & TSFunBase::GetPer() const
{
    return m_per;
}

const IDataProvider & TSFunBase::GetData() const
{
    return m_per;
}

const IBufferCandles & TSFunBase::GetCandles() const
{
    return m_bufCan;
}

Candle TSFunBase::GetCandleTS(int idx, int shift) const
{
    return m_bufCan[idx + shift];
}

Candle TSFunBase::GetCandle0Based(int idx) const
{
    return m_bufCan.GetDataVec()[idx];
}

unsigned TSFunBase::Len() const
{
    return LenProt();
}

unsigned TSFunBase::LenData() const
{
    return GetData().Len();
}

unsigned TSFunBase::LenProt() const
{
    return LenData();
}

bool TSFunBase::CrashOnWarning() const
{
    return m_tsin.m_cfgTS.crashOnRecoverableErrors;
    //return false;
}

OptiVarVec & TSFunBase::GetOptiFloatRW()
{
    return *m_optiFloats;
    //return m_optiFloats;
}

OptiVarVec TSFunBase::GetOptiFloat()
{
    return *m_optiFloats;
    //return m_optiFloats;
}


void TSFunBase::AddOptiVars(IOptimizable & iopt)
{
    for (auto v : iopt.GetOptiFloat().Vec())
        AddOptiVar(*v);
}

void TSFunBase::AddOptiVar(OptiVarF & var)
{
    GetOptiFloatRW().VecRW().push_back(&var);
    //m_optiFloats.push_back(&var);
}

void TSFunBase::SetSilent()
{
    m_silent = true;
}
bool TSFunBase::IsVerbose() const
{
    return not m_silent;
}
