#include "IConfig.h"

#include "ConfigDirs.h"

#include <Util/FileUtils.hpp>
#include <Ios/Ofstream.hpp>
#include <Ios/Ifstream.hpp>
#include <Ios/Osstream.hpp>
#include <Util/Except.hpp>
#include <Ios/Isstream.hpp>
#include <Util/CoutBuf.hpp>

using namespace std;
using namespace EnjoLib;

IConfig::IConfig(){}
IConfig::~IConfig(){}

EnjoLib::Str IConfig::GetFileName() const
{
    return ConfigDirs().DIR_CFG + GetFileNameProt();
}

bool IConfig::PrepareReadStream(EnjoLib::Istream & ifs) const
{
    if (!ifs.good())
    {
        LOGL << "Couldn't open config file: " << GetFileName() << Nl;
        return false;
    }
    return true;
}

void IConfig::Write() const
{
    EnjoLib::FileUtils().CreateDirIfNotExistsLinux(ConfigDirs().DIR_CFG);
    EnjoLib::Ofstream f(GetFileName());
    f << GetConfigString();
    //cout << GetConfigString() << endl;
}

bool IConfig::Read()
{
    //cout << GetFileName() + ": Read from file!!!\n";
    EnjoLib::Ifstream ifs(GetFileName(), false);
    return Read(ifs);
}

bool IConfig::Read(const EnjoLib::Str & data)
{
    //cout << GetFileName() + ": Read from string\n";
    EnjoLib::Isstream ifs(data);
    //ifs << data;
    return Read(ifs);
}

bool IConfig::Read(EnjoLib::Istream & f)
{
    Clear();
    const bool couldRead = PrepareReadStream(f);
    RegisterAndReadStrs(f);
    RegisterAndReadFloats(f);
    RegisterAndReadInts(f);
    RegisterAndReadBools(f);
    RegisterAndReadFloatMap(f);
    if (not couldRead) {
        //cout << GetFileName() + ": Could not read from stream\n";
        // Writes default values
        Write();
        return false;
    }
    return true;
}


EnjoLib::Str IConfig::GetFileNameProtBackup() const
{
    return GetFileNameProt();
}

void IConfig::RegisterAndReadFloatMap(EnjoLib::Istream & ifs) {}

