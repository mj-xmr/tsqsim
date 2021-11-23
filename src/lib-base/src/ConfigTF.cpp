#include "ConfigTF.h"
#include "OptionsNumeric.h"

#include <Util/Except.hpp>



using namespace std;

const char * ConfigTF::OPT_INDIVIDUAL_PERIOD = "indiv-per";
const char * ConfigTF::OPT_INDIVIDUAL_SYMBOL = "indiv-sym";
const char * ConfigTF::OPT_INDIVIDUAL_STRAT  = "indiv-strat";
const char * ConfigTF::OPT_PLOT_TYPE = "plot-type";
const char * ConfigTF::OPT_REPEAT = "repeat";
const char * ConfigTF::OPT_SIMUL_MULTITHREAD = "sim-mt";

ConfigTF::ConfigTF(){}
ConfigTF::~ConfigTF(){}

EnjoLib::Str ConfigTF::GetFileNameProt() const
{
    return "configTF.txt";
}

void ConfigTF::FromOptsNumeric(const OptionsNumeric & optsNum)
{
    UpdateVarIfConfigured(optsNum, INDIVIDUAL_PERIOD,   OPT_INDIVIDUAL_PERIOD);
    UpdateVarIfConfigured(optsNum, INDIVIDUAL_SYMBOL,   OPT_INDIVIDUAL_SYMBOL);
    UpdateVarIfConfigured(optsNum, INDIVIDUAL_STRAT,    OPT_INDIVIDUAL_STRAT);
    UpdateVarIfConfigured(optsNum, SIMUL_MULTITHREAD,   OPT_SIMUL_MULTITHREAD);

    UpdateVarIfConfigured(optsNum, PLOT_TYPE,   OPT_PLOT_TYPE);
    UpdateVarIfConfigured(optsNum, REPEAT,      OPT_REPEAT);
}

void ConfigTF::RegisterAndReadBools(EnjoLib::Istream & f)
{
    RegisterAndReadBool(f, REPEAT, 0,               "REPEAT");
    RegisterAndReadBool(f, SIMUL_MULTITHREAD, true, "SIMUL_MULTITHREAD");
}
void ConfigTF::RegisterAndReadInts(EnjoLib::Istream & f)
{
    RegisterAndReadInt (f, INDIVIDUAL_PERIOD, 0);
    RegisterAndReadInt (f, INDIVIDUAL_SYMBOL, 0);
    RegisterAndReadInt (f, INDIVIDUAL_STRAT, 0);
    RegisterAndReadInt (f, PLOT_TYPE, 0);
}
void ConfigTF::RegisterAndReadFloats(EnjoLib::Istream & f)
{
}
void ConfigTF::RegisterAndReadStrs(EnjoLib::Istream & f)
{
}
