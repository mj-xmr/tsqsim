#include "TSFunBase.h"
#include "IPeriod.h"
#include "IBufferCandles.h"
#include "Candle.h"
#include "ConfigTS.h"

#include <Ios/Osstream.hpp>
#include <Util/Str.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/StrColour.hpp>

using namespace EnjoLib;

TSFunBase::~TSFunBase(){}
TSFunBase:: TSFunBase(const TSInput & tsin)
: m_tsin(tsin)
, m_per(tsin.m_per)
, m_bufCan(tsin.m_per.GetCandles())
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
        if (CrashOnWarning())
        {
            throw; /// TODO: Rethrow
        }
        Osstream oss;
        oss << "TSFunBase::OnDataPoint: idx " << idx << Nl << exc.what();
        oss << "Is Len() overriden and adjusted?\n";
        LOGL << EnjoLib::StrColour::GenWarn(oss.str()) << EnjoLib::Nl;
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

Candle TSFunBase::GetCandle(int idx, int shift) const
{
    return m_bufCan[idx + shift];
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
