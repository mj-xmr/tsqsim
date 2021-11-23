#include "ConfigTS.h"

#include "Consts.h"

//#include <Util/Except.hpp>
#include <Ios/Osstream.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/Pair.hpp>

using namespace std;
using namespace EnjoLib;

ConfigTS::~ConfigTS(){}
ConfigTS::ConfigTS()
{
}

EnjoLib::Str ConfigTS::GetFileNameProt() const
{
    return "configTS.txt";
}

void ConfigTS::FromOptsNumeric(const OptionsNumeric & optsNum)
{
}

void ConfigTS::RegisterAndReadBools(EnjoLib::Istream & f)
{
    RegisterAndReadBool(f, crashOnRecoverableErrors, 0,  "Crash on err", "Crash on recoverable errors");
    RegisterAndReadBool(f, PLOT_SERIES, 0,               "Plot series",  "Plot output series after evaluation");

}
void ConfigTS::RegisterAndReadInts(EnjoLib::Istream & f)
{
    //RegisterAndReadInt (f, percentBars, 100);
}
void ConfigTS::RegisterAndReadFloats(EnjoLib::Istream & f)
{
}
void ConfigTS::RegisterAndReadStrs(EnjoLib::Istream & f)
{
    RegisterAndReadStr(f, m_scriptPathTxt, "helloworld.txt");
}
