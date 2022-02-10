#include "ConfigTF2.h"
#include "SimulatorType.h"

#include <Util/ThreadWrap.hpp>
//int EnjoLib::ThreadWrap::GetConcurrency()

using namespace std;

ConfigTF2::ConfigTF2(){}
const char * ConfigTF2::OPT_TRAIN = "train";
const char * ConfigTF2::OPT_SIM_TYPE = "sim-type";
const char * ConfigTF2::OPT_FILTER_PRICE = "filter-price";

EnjoLib::Str ConfigTF2::GetFileNameProt() const
{
    return "configTF2.txt";
}

void ConfigTF2::FromOptsNumeric(const OptionsNumeric & optsNum)
{
    UpdateVarIfConfigured(optsNum, TRAIN,        OPT_TRAIN);
    UpdateVarIfConfigured(optsNum, MT_SIM_TYPE,  OPT_SIM_TYPE);
    UpdateVarIfConfigured(optsNum, FILTER_PRICE, OPT_FILTER_PRICE);
}

void ConfigTF2::RegisterAndReadBools(EnjoLib::Istream & f)
{
    RegisterAndReadBool(f, CUSTOM_DATE, true,           "CUSTOM_DATE");
    RegisterAndReadBool(f, SINGLE_THREADED_ALL, false,  "Single threaded");
    RegisterAndReadBool(f, EXPERIMENTAL, false,         "EXPERIMENTAL");
#ifdef WX_FULL
    RegisterAndReadBool(f, RANDOM_BARS, false,          "RANDOM_BARS");
    RegisterAndReadBool(f, FILTER_PRICE, false,         "FILTER_BARS");
    RegisterAndReadBool(f, NETWORKED, false,            "NETWORKED");
    RegisterAndReadBool(f, NETWORKED_CV, false,         "NETWORKED_CV");
    RegisterAndReadBool(f, MT_SIM_UPDATE_TECH, false,   "MT_SIM_UPDATE_TECH");
    RegisterAndReadBool(f, SIM_USE_TICKS, false,        "SIM_USE_TICKS");
    RegisterAndReadBool(f, TRAIN, false,                "TRAIN");
    RegisterAndReadBool(f, FULL_DATA, false,            "FULL_DATA");
    RegisterAndReadBool(f, PYTHON_SERVER, false,        "PYTHON_SERVER");
    RegisterAndReadBool(f, BLACKLIST, true,             "BLACKLIST");
    RegisterAndReadBool(f, OPTIM_COSTLY, false,         "OPTIM_COSTLY");
    RegisterAndReadBool(f, CORREL_CALC, false,          "CORREL_CALC");
    RegisterAndReadBool(f, CORREL_USE, false,           "CORREL_USE");
    RegisterAndReadBool(f, CORREL_ADAPT, false,         "CORREL_ADAPT");
    RegisterAndReadBool(f, POTENTIAL_PROFIT, false,     "POTENTIAL_PROFIT");
    RegisterAndReadBool(f, PLOT_COUMPOUNDED, false,     "PLOT_COUMPOUNDED");
    RegisterAndReadBool(f, STATS_SUMMARY, false,        "Stats summary");
    RegisterAndReadBool(f, CAP_CORREL_ADJ, false,       "Adj. cap. corr.");
    RegisterAndReadBool(f, CAP_CORREL_ADJ_WINDOW, false,"Adj. cap. corr. win.");
#endif // WX_FULL

    //RegisterAndReadBool(f, NO_AT_ACCESS, false);
}

void ConfigTF2::RegisterAndReadInts(EnjoLib::Istream & f)
{
    RegisterAndReadInt (f, dates.yearStart, 2016);
    RegisterAndReadInt (f, dates.yearEnd, 2019);
    RegisterAndReadInt (f, dates.monthStart, 1);
    RegisterAndReadInt (f, dates.monthEnd, 1);
    RegisterAndReadInt (f, PLOTS, 0);
    RegisterAndReadInt (f, THREADS, 0);
    RegisterAndReadInt (f, RANDOM_BARS_PERCENT, 0);
    RegisterAndReadInt (f, RANDOM_BARS_SEED, 0);
    RegisterAndReadInt (f, MT_SIM_TYPE, (long int)SimulatorType::SIMUL_STANDARD);
    RegisterAndReadInt (f, SPREAD_MUL_FILTER, 0);
    RegisterAndReadInt (f, EXPERIM_INT_1, 0);
    RegisterAndReadInt (f, EXPERIM_INT_2, 0);
}
void ConfigTF2::RegisterAndReadFloats(EnjoLib::Istream & f)
{
    //RegisterAndReadFloat(f, SPREAD_MUL_FILTER, 0); // Wont work for long int
}
void ConfigTF2::RegisterAndReadStrs(EnjoLib::Istream & f)
{
}

int ConfigTF2::GetNumThreads() const
{
    if (THREADS == 0)
    {
        if (NETWORKED)
        {
            return 20;
        }
        return EnjoLib::ThreadWrap::GetConcurrency() * 2;
    }
    return THREADS;
}

bool ConfigTF2::ClearBlacklist() const
{
    return (not BLACKLIST || CORREL_CALC || CORREL_USE || CORREL_ADAPT);
}

bool ConfigTF2::UsesNetwork() const
{
    return NETWORKED || NETWORKED_CV;
}

SimulatorType ConfigTF2::GetSimType() const
{
    return SimulatorType(MT_SIM_TYPE);
}

float ConfigTF2::GetRandomBarsPercent() const
{
    return RANDOM_BARS_PERCENT / 100.0;
}
