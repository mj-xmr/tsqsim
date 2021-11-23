#include "ConfigQT.h"

#include <Util/Except.hpp>

using namespace std;

ConfigQT::ConfigQT(){}
ConfigQT::~ConfigQT(){}

EnjoLib::Str ConfigQT::GetFileNameProt() const
{
    return "configQT.txt";
}

void ConfigQT::FromOptsNumeric(const OptionsNumeric & optsNum)
{
}

void ConfigQT::RegisterAndReadBools(EnjoLib::Istream & f)
{
    RegisterAndReadBool(f, BIG_SCREEN, true,    "BIG_SCREEN");
    RegisterAndReadBool(f, DIRECTION, true,     "DIRECTION");
    RegisterAndReadBool(f, PLOT_SIG_LAB, false, "PLOT_SIG_LAB");
    RegisterAndReadBool(f, USE_CACHE, false,    "USE_CACHE");
}
void ConfigQT::RegisterAndReadInts(EnjoLib::Istream & f)
{
    RegisterAndReadInt (f, buf1, 0);
    RegisterAndReadInt (f, buf2, 0);
    RegisterAndReadInt (f, buf3, 0);
    RegisterAndReadInt (f, bufRainbow, 0);
}
void ConfigQT::RegisterAndReadFloats(EnjoLib::Istream & f)
{
}
void ConfigQT::RegisterAndReadStrs(EnjoLib::Istream & f)
{
    RegisterAndReadStr(f, dateTime, "");
}
