#include "ConfigBase.h"

#include <Ios/Osstream.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/CharManipulations.hpp>

using namespace std;
using namespace EnjoLib;

ConfigBase::ConfigBase(){}
ConfigBase::~ConfigBase(){}

void ConfigBase::Clear()
{
    m_registeredVarsStr.clear();
    m_registeredVarsFloat.clear();
    m_registeredVarsInt.clear();
    m_registeredVarsBool.clear();
}

EnjoLib::Str ConfigBase::GetConfigString() const
{
    EnjoLib::Osstream oss;
    for (const auto * var : m_registeredVarsStr)    oss << *var << " ";
    for (const auto * var : m_registeredVarsFloat)  oss << *var << " ";
    for (const auto * var : m_registeredVarsInt)    oss << *var << " ";
    for (const auto * var : m_registeredVarsBool)   oss << *var << " ";
    return oss.str();
}

void ConfigBase::RegisterAndReadBool(EnjoLib::Istream & ifs, bool & var, const bool & def, const EnjoLib::Str & descr, const EnjoLib::Str & tooltip)
{
    RegisterAndRead(ifs, m_registeredVarsBool, var, def);
    const EnjoLib::Str toolTipUsed = tooltip.empty() ? CharManipulations().UpperCase2Sentence(descr) : tooltip;
    const EnjoLib::Str descrUsed = tooltip.empty() ? descr : descr + " .";
    m_registeredVarsBoolDescr.push_back(descrUsed);
    m_registeredVarsBoolToolTip.push_back(tooltip); // Allows empty tooltips
    //m_registeredVarsBoolToolTip.push_back(toolTipUsed); // Always use some tooltip
}

void ConfigBase::RegisterAndReadInt(EnjoLib::Istream & ifs, long int & var, const long int & def)
{
    RegisterAndRead(ifs, m_registeredVarsInt, var, def);
}

void ConfigBase::RegisterAndReadFloat(EnjoLib::Istream & ifs, float & var, const float & def)
{
    RegisterAndRead(ifs, m_registeredVarsFloat, var, def);
}

void ConfigBase::RegisterAndReadStr  (EnjoLib::Istream & ifs, EnjoLib::Str & var, const EnjoLib::Str & def)
{
    RegisterAndRead(ifs, m_registeredVarsStr, var, def);
}

EnjoLib::Str ConfigBase::GetRelDebDirBase(bool isRelease) const
{
    return isRelease ? "rel" : "deb";
}

const EnjoLib::VecT<bool*> & ConfigBase::GetBools() const
{
    return m_registeredVarsBool;
}
const EnjoLib::VecT<EnjoLib::Str> & ConfigBase::GetBoolsDescr() const
{
    return m_registeredVarsBoolDescr;
}
const EnjoLib::VecT<EnjoLib::Str> & ConfigBase::GetBoolsToolTip() const
{
    return m_registeredVarsBoolToolTip;
}

template <class T>
bool ConfigBase::RegisterAndRead(EnjoLib::Istream & ifs, EnjoLib::IVecT<T*> & regist, T & var, const T & defaultVal)
{
    const bool varWasAvailable = (ifs >> var);
    if (not varWasAvailable)
    {
        var = defaultVal;
    }
    regist.push_back(&var);
    return varWasAvailable;
}
