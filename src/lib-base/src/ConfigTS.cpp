#include "ConfigTS.h"

#include "Consts.h"

//#include <Util/Except.hpp>
#include <Ios/Osstream.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/Pair.hpp>

using namespace std;
using namespace EnjoLib;

const char * ConfigTS::DEFAULT_SCRIPT_FILE_NAME = "helloworld.txt";

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
    RegisterAndReadBool(f, crashOnRecoverableErrors, 0, "Crash on err", "Crash on recoverable errors");
    RegisterAndReadBool(f, PLOT_SERIES,              1, "Plot series",  "Plot output series after evaluation");
    RegisterAndReadBool(f, MT_XFORM,                 1, "MT xform",     "Perform the transformations in a multithreaded way (still unstable)");
    RegisterAndReadBool(f, MT_REPORT,                0, "MT report",    "Generate report in multithreaded way (still unstable)");
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
    RegisterAndReadStr(f, m_scriptPathTxt, DEFAULT_SCRIPT_FILE_NAME);
}
