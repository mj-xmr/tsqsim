#include "ConfigQTPlot.h"

using namespace std;

ConfigQTPlot::ConfigQTPlot(){}
ConfigQTPlot::~ConfigQTPlot(){}

EnjoLib::Str ConfigQTPlot::GetFileNameProt() const
{
    return "configQTPlot.txt";
}

void ConfigQTPlot::FromOptsNumeric(const OptionsNumeric & optsNum)
{
}

void ConfigQTPlot::RegisterAndReadBools(EnjoLib::Istream & f)
{
    RegisterAndReadBool(f, DARK, true,          "DARK");
    RegisterAndReadBool(f, CANDLES, true,       "CANDLES");
    RegisterAndReadBool(f, TECHS, true,         "TECHS");
    RegisterAndReadBool(f, PROFIT, true,        "PROFIT");
    RegisterAndReadBool(f, SIMUL, true,         "SIMUL");
    RegisterAndReadBool(f, SIGNAL_TRADE, true,  "SIGNAL_TRADE");
    RegisterAndReadBool(f, SIGNAL_SPECIAL, false, "SIGNAL_SPECIAL");
    RegisterAndReadBool(f, SR, false,           "SR");
    RegisterAndReadBool(f, SR_GROUPS, false,    "SR_GROUPS");
    RegisterAndReadBool(f, SL, true,            "SL");
    RegisterAndReadBool(f, TPS, true,           "TPS");
    RegisterAndReadBool(f, MA, true,            "MA");
    RegisterAndReadBool(f, STD_DEV, false,      "STD_DEV");
    RegisterAndReadBool(f, ZIG_ZAG, false,      "ZIG_ZAG");
    RegisterAndReadBool(f, ZIG_ZAG_INDEXES, false, "ZIG_ZAG_IDX");
    RegisterAndReadBool(f, DAY_WEEK, false,     "DAY_WEEK");
    RegisterAndReadBool(f, BET, false,          "BET");
}
void ConfigQTPlot::RegisterAndReadInts(EnjoLib::Istream & ifs)
{
}
void ConfigQTPlot::RegisterAndReadFloats(EnjoLib::Istream & ifs)
{
}
void ConfigQTPlot::RegisterAndReadStrs(EnjoLib::Istream & ifs)
{
}
