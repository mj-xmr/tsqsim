#include <STD/MapPch.hpp>

#include "ConfigTxt.h"
#include "ConfigDirs.h"

#include <Util/Tokenizer.hpp>
#include <Util/CharManipulationsTplVec.hpp>
#include <Ios/Ofstream.hpp>
#include <Util/FileUtils.hpp>
#include <Util/StrColour.hpp>
#include <Util/VecF.hpp>
#include <Template/CacheRAM.hpp>

#include <Util/CoutBuf.hpp>


using namespace std;
using namespace EnjoLib;

const char ConfigTxt::m_comment= '#';
const char ConfigTxt::m_delim = '=';

ConfigTxt::ConfigTxt()
: m_map(new CacheRAM<Key, Val>)
, m_mapVec(new CacheRAM<Key, ValVec>)
, m_mapMissing(new CacheRAM<Key, Val>)
, m_mapVecMissing(new CacheRAM<Key, ValVec>)
{

}

ConfigTxt::~ConfigTxt()
{
    const EnjoLib::Str delim = EnjoLib::Str(" ") + m_delim + ' ';
    const EnjoLib::Str outFile = GetFileName() + ".out";
    EnjoLib::FileUtils().CreateDirIfNotExistsLinux(ConfigDirs().DIR_CFG);
    EnjoLib::Ofstream f(outFile);

    bool hadMissing = false;

    f << GenCommentLine();
    f << m_comment << " SINGLE  " << m_comment << "\n";
    f << GenCommentLine();
    for (const auto it : m_mapMissing->GetMap())
    {
        f << it.first << delim << it.second << '\n';
        hadMissing = true;
    }
    f << '\n';
    f << GenCommentLine();
    f << m_comment << " VECTORS " << m_comment << "\n";
    f << GenCommentLine();
    for (const auto it : m_mapVecMissing->GetMap())
    {
        f << it.first << delim << it.second.Print() << '\n';
        hadMissing = true;
    }
    if (hadMissing)
    {
        LOGL << "Stored missing configuration values to: " << outFile << '\n';
    }
}

EnjoLib::Str ConfigTxt::GenCommentLine() const
{
    EnjoLib::Osstream oss;
    const int commentNum = 11;
    for (int i = 0; i < commentNum; ++i)
    {
        oss << m_comment;
    }
    oss << '\n';
    return oss.str();
}

void ConfigTxt::FromOptsNumeric(const OptionsNumeric & optsNum)
{
}

EnjoLib::Str ConfigTxt::GetFileNameProt() const
{
    return "configTxt.txt";
}

const ConfigTxt::MapF & ConfigTxt::Get() const
{
    return *m_map;
}

const ConfigTxt::MapV & ConfigTxt::GetV() const
{
    return *m_mapVec;
}

ConfigTxt::MapF & ConfigTxt::GetRW()
{
    return *m_map;
}
ConfigTxt::MapV & ConfigTxt::GetVRW()
{
    return *m_mapVec;
}

void ConfigTxt::RegisterAndReadFloatMap(EnjoLib::Istream & ifs)
{
    const Tokenizer tok;
    const CharManipulationsTplVec cmanTpl;
    const CharManipulations cman;
    const VecStr & lines = tok.GetLines(ifs);
    for (Str line : lines)
    {
        line = cman.Trim(line);
        try
        {
            if (line.empty())
            {
                continue;
            }
            if (line.at(0) == m_comment)
            {
                continue;
            }
            const VecStr & keyPair = tok.Tokenize(line, '=');
            const Str & key = cman.Trim(keyPair.at(0));
            const Str & valsStr = cman.Trim(keyPair.at(1));
            const VecStr & vals = tok.Tokenize(valsStr);
            if (vals.size() > 1)
            {
                LOGL << "Adding " << key << ", vector of " << vals.size() << EnjoLib::Nl;
                m_mapVec->Add(key, cmanTpl.ToNumbersVec<float>(vals));
            }
            else // == 1
            {
                const Str & val = vals.at(0);
                LOGL << "Adding " << key << " " << val << EnjoLib::Nl;
                m_map->Add(key, cman.ToDouble(val));
            }
        }
        catch (std::exception & ex)
        {
            LOGL << StrColour::GenWarn("ConfigTxt::RegisterAndReadFloatMap() wrong format at: ") << line << '\n' << ex.what() << '\n';
        }
    }
}

EnjoLib::Str ConfigTxt::GetConfigString() const
{
    EnjoLib::Osstream oss;
    for (auto it = m_map->GetMap().cbegin(); it != m_map->GetMap().cend(); ++it)
    {
        oss << it->first << " = " << it->second << '\n';
    }
    return oss.str();
}

void ConfigTxt::AddToMissing(const Key & key, const Val & val)
{
    m_mapMissing->Add(key, val);
}
void ConfigTxt::AddToMissing(const Key & key, const ValVec & val)
{
    m_mapVecMissing->Add(key, val);
}

void ConfigTxt::RegisterAndReadBools   (EnjoLib::Istream & ifs){}
void ConfigTxt::RegisterAndReadInts    (EnjoLib::Istream & ifs){}
void ConfigTxt::RegisterAndReadFloats  (EnjoLib::Istream & ifs){}
void ConfigTxt::RegisterAndReadStrs    (EnjoLib::Istream & ifs){}
