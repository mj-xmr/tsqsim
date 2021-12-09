#include "CacheDynamicNonTpl.h"
#include "IDataProvider.h"

#include "ConfigDirs.h"
#include "ConfigMan.h"
#include "ConfigTF2.h"

#include <EnjoLibBoost/Filesystem.hpp>

#include <Util/FileUtils.hpp>
#include <Util/Str.hpp>
#include <Util/Except.hpp>

#include <Ios/Osstream.hpp>
#include <Util/CoutBuf.hpp>


using namespace EnjoLib;
using namespace std;

CacheDynamicNonTpl::~CacheDynamicNonTpl(){}
CacheDynamicNonTpl::CacheDynamicNonTpl(const EnjoLib::Str & name, const IDataProvider & data)
: m_name(name)
, m_sym(data.GetSymbolName())
, m_per(data.GetName())
, m_isBinary(true)
, m_isMT(data.IsMetaTrader())
, m_isRandomBars(gcfgMan.cfgTF2->RANDOM_BARS)
, m_isTicks(gcfgMan.cfgTF2->FILTER_PRICE)
{
    //ctor
}

EnjoLib::Str CacheDynamicNonTpl::GetFilename() const
{
    const ConfigDirs cfgDirs;
    const EnjoLib::Str dirFinal = cfgDirs.DIR_CACHE + '/' + m_name + '/';
    Filesystem().CreateDirIfNotExists(cfgDirs.DIR_CACHE);
    Filesystem().CreateDirIfNotExists(dirFinal);
    const char d = '_';
    EnjoLib::Osstream ossMT;
    if (m_isMT)
        ossMT << "MT" << d;

    const EnjoLib::Str extension = ".bin" + cfgDirs.EXT_ARCHIVE;
    //const string extension = ".txt";
    return dirFinal + ossMT.str() + m_sym + d + m_per + extension;
}

bool CacheDynamicNonTpl::ShouldRestore() const
{
    if (not ShouldWorkSettings())
    {
        return false;
    }
    if (FileExists())
    {
        return true;
    }
    else
    {
        //cout << "Doesn't exist: " << fname << endl;
    }
    return false;
}

bool CacheDynamicNonTpl::ShouldStore() const
{
    if (not ShouldWorkSettings())
    {
        return false;
    }
    //CharManipulations cmp;
    //if (not m_isMT || cmp.StartsWith(m_sym, "TEST"))
    {
        const bool isDirty = m_storeCount > 0;
        const EnjoLib::Str & fname = GetFilename();
        if (isDirty)
        {
            if (not m_isMT)
            {
                ELO
                LOG << "\nStoring cache - " << m_storeCount << " '" << fname << "' " << Nl;
            }
            return true;
        }
        else
        {
            if (not m_isMT)
            {
                //cout << "Not dirty - " + fname << endl;
            }
        }
    }
    return false;
}

bool CacheDynamicNonTpl::ShouldWorkSettings() const
{
    if (m_isRandomBars)
    {
        return false;
    }
    if (m_isTicks)
    {
        return false;
    }
    return true;
}

void CacheDynamicNonTpl::Stored()
{
    m_storeCount = 0;
}

void CacheDynamicNonTpl::Add()
{
    ++m_storeCount;
}

void CacheDynamicNonTpl::LogNotFound(const EnjoLib::Str & key) const
{
    if (not m_isMT)
    {
        if (++m_counterCout % 50 == 0)
        {
            LOGL << "Not found res '" << m_name << "' = " << key << Nl;
        }
    }
}

void CacheDynamicNonTpl::Cout(const char * idd, const std::exception & ex) const
{
    const Str msg = Str(idd) + " '" + m_name + "' " + ex.what();
    LOGL << msg << Nl;
    throw EnjoLib::ExceptRuntimeError(msg);
}

bool CacheDynamicNonTpl::FileExists() const
{
    const EnjoLib::Str & fname = GetFilename();
    return FileUtils().FileExists(fname);
}
