#include "ConfigMan.h"

#include "ConfigOpti.h"
#include "ConfigTF.h"
#include "ConfigTF2.h"
#include "ConfigTS.h"
#include "ConfigSym.h"
#include "ConfigOpti.h"
#include "ConfigQT.h"
#include "ConfigQTPlot.h"
#include "ConfigML.h"
#include "ConfigTxt.h"

#include <Util/ProtocolCreator.h>
#include <Util/Tokenizer.hpp>
#include <Util/StrColour.hpp>
#include <Util/VecF.hpp>
#include <Util/Except.hpp>
#include <Util/PimplDeleter.hpp>
#include <Util/CharManipulations.hpp>
#include <Statistical/Assertions.hpp>

#include <STD/VectorCpp.hpp>
#include <Util/CoutBuf.hpp>
#include <cassert>

using namespace std;
using namespace EnjoLib;

ConfigMan gcfgMan;

struct ConfigMan::Impl
{
    std::vector<IConfig*> m_configsReg;
};
PIMPL_DELETER(ConfigMan)

ConfigMan::~ConfigMan(){}
ConfigMan::ConfigMan()
: m_impl(new Impl())
{
    InitReset();
    //Read(); // wont work anymore due to serialization
}

void ConfigMan::InitReset()
{
    GetImplRW().m_configsReg.clear();

    InitCfg(new ConfigOpti(),   &cfgOpti);
    InitCfg(new ConfigQT(),     &cfgQT);
    InitCfg(new ConfigQTPlot(), &cfgQTPlot);
    InitCfg(new ConfigTF(),     &cfgTF);
    InitCfg(new ConfigTF2(),    &cfgTF2);
    InitCfg(new ConfigTS(),     &cfgTS);
    InitCfg(new ConfigSym(),    &cfgSym);
    InitCfg(new ConfigML(),     &cfgML);
    InitCfg(new ConfigTxt(),    &cfgTxt);
}

void ConfigMan::FromOptsNumeric(const OptionsNumeric & opts)
{
    if (not m_configRead)
    {
        //throw EnjoLib::ExceptLogicError("ConfigMan::Read() Read() first.");
    }
    for (IConfig * cfg : GetImplRW().m_configsReg)
    {
        cfg->FromOptsNumeric(opts);
    }
}

void ConfigMan::Read()
{
    if (m_configRead)
    {
        //throw EnjoLib::ExceptLogicError("ConfigMan::Read() already read.");
        //std::cout << "ConfigMan::Read() already read.\n";
    }
    m_configRead = true;

    for (IConfig * cfg : GetImplRW().m_configsReg)
    {
        cfg->Read();
    }
}

void ConfigMan::Read(const EnjoLib::Str & str)
{
    const EnjoLib::Tokenizer tok;
    const VecStr & configs = tok.Tokenize(str, m_sep);
    if (configs.size() != GetImpl().m_configsReg.size())
    {
        LOGL << StrColour::GenWarn(str) << Nl;
    }
    Assertions().SizesEqual(configs.size(), GetImpl().m_configsReg.size(), "ConfigMan::Read configs");

    for (size_t i = 0; i < configs.size(); ++i)
    {
        const Str & cfgStr = configs.at(i);
        IConfig * cfg = GetImplRW().m_configsReg.at(i);
        cfg->Read(cfgStr);
    }
}

EnjoLib::Str ConfigMan::GetConfigString() const
{
    ProtocolCreator prc(m_sep);
    for (const IConfig * cfg : GetImpl().m_configsReg)
    {
        const EnjoLib::Str & gcfStr = cfg->GetConfigString();
        prc.AddStr(gcfStr);
        //cout << "ConfigMan: " << gcfStr << endl;
    }
    return prc.Get();
}

float ConfigMan::Get(const EnjoLib::Str & idd, float valDefault) const
{
    const auto & cache = cfgTxt->Get();
    if (not cache.Has(idd))
    {
        LOGL << StrColour::GenWarn("Missing key = " + idd + ". Using default " + CharManipulations().ToStr(valDefault)) << Nl;
        cfgTxt->GetRW().Add(idd, valDefault);
        cfgTxt->AddToMissing(idd, valDefault);
        //throw EnjoLib::ExceptRuntimeError("ConfigMan::Get(): Missing key = " + idd);
    }
    else
    {
        LOGL << "Found key = " + idd + ". Using " << cache.Get(idd) << Nl;
    }
    return cache.Get(idd);
}
EnjoLib::VecF ConfigMan::GetV(const EnjoLib::Str & idd, const EnjoLib::VecF & valDefault) const
{
    const auto & cache = cfgTxt->GetV();
    if (not cache.Has(idd))
    {
        LOGL << StrColour::GenWarn("Missing key = " + idd + ". Using default " + valDefault.Print()) << Nl;
        cfgTxt->GetVRW().Add(idd, valDefault);
        cfgTxt->AddToMissing(idd, valDefault);
        //throw EnjoLib::ExceptRuntimeError("ConfigMan::GetV(): Missing key = " + idd);
    }
    return cache.Get(idd);
}

bool ConfigMan::IsMT(bool additionalCondition) const
{
    if (not additionalCondition)
    {
        return false;
    }
    if (cfgTF2->SINGLE_THREADED_ALL)
    {
        return false;
    }
    return true;
}

template <class CFG>
void ConfigMan::InitCfg(CFG * cfg, Corrade::Containers::Pointer<CFG> * ptrVar)
{
    (*ptrVar) = Corrade::Containers::Pointer<CFG>(cfg);
    GetImplRW().m_configsReg.push_back(ptrVar->get());
}
