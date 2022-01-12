#include "ConfigOpti.h"
#include "OptiType.h"
#include "OptiGoalType.h"
#include "TradeUtilThin.h"
#include "IPeriod.h"

#include <Util/Except.hpp>

using namespace std;

ConfigOpti::ConfigOpti()
{
}

EnjoLib::Str ConfigOpti::GetFileNameProt() const
{
    return "configOpti.txt";
}

void ConfigOpti::FromOptsNumeric(const OptionsNumeric & optsNum)
{
}

int ConfigOpti::GetOPTI_CROSS_VALID_BARS_OPTI(const IPeriod & per) const
{
    return OPTI_CROSS_VALID_BARS_OPTI_H1 * TradeUtilThin().CalcPeriodTicksRelToHour(per.GetNumTicks());
}
float ConfigOpti::GetOPTI_CROSS_VALID_BARS_XVAL(const IPeriod & per) const
{
    //cout << "ConfigOpti::GetOPTI_CROSS_VALID_BARS_XVAL = " << OPTI_CROSS_VALID_BARS_XVAL << endl;
    return OPTI_CROSS_VALID_BARS_XVAL / 100.0;
}

OptiType ConfigOpti::GetOptimizer() const
{
    return static_cast<OptiType>(OPTIMIZER);
}
OptiMethod ConfigOpti::GetOptimizerMethod() const
{
    return static_cast<OptiMethod>(OPTIMIZER_METHOD);
}
OptiGoalType ConfigOpti::GetOptimizerGoalType() const
{
    return static_cast<OptiGoalType>(OPTIMIZER_GOAL);
}

void ConfigOpti::SetOptimizer(const OptiType & optiType)
{
    OPTIMIZER = static_cast<long int>(optiType);
}
void ConfigOpti::SetOptimizerMethod(const OptiMethod & optiMethod)
{
    OPTIMIZER_METHOD = static_cast<long int>(optiMethod);
}
void ConfigOpti::SetOptimizerGoal(const OptiGoalType & optiGoal)
{
    OPTIMIZER_GOAL = static_cast<long int>(optiGoal);
}

        
bool ConfigOpti::IsSearchFloatingPoint() const
{
    return not IsSearchGrid();
}
bool ConfigOpti::IsSearchGrid() const
{
    return GetOptimizerMethod() == OptiMethod::OPTI_METHOD_GRID || IsSearchRandom();
}
bool ConfigOpti::IsSearchRandom() const
{
    return GetOptimizerMethod() == OptiMethod::OPTI_METHOD_MONTECARLO;
}

ConfigOpti::~ConfigOpti(){}

void ConfigOpti::RegisterAndReadBools(EnjoLib::Istream & f)
{
    RegisterAndReadBool(f, OPTI_VERBOSE, true,              "VERBOSE",          "Show plots and stats");
    RegisterAndReadBool(f, OPTI_USE_RELEASE, false,         "USE_RELEASE",      "Use parameters stored as 'release'");
    RegisterAndReadBool(f, OPTI_GLOBAL, false,              "GLOBAL",           "Find parameters, which optimize all series at the same time");
    RegisterAndReadBool(f, OPTI_CROSS_VALID, false,         "W.F. Validation",  "Walk forward optimization / validation");
    RegisterAndReadBool(f, OPTI_LAST, false,                "LAST",             "Use only the last window (iteration) of the W.F. Validation");
    RegisterAndReadBool(f, OPTI_RANDOM_EARLY_STOP, false,   "Early stop",       "Stop Monte Carlo if the change of variance of the optimized var is below threshold");
    RegisterAndReadBool(f, OPTI_SERVER_DENSE, false,        "SERVER_DENSE",     "Use dense sampling of the variables in production (on server).");
    RegisterAndReadBool(f, OPTI_XVAL_EXTENDABLE, false,     "XVAL_EXTENDABLE"); /// TODO: Explain
}
void ConfigOpti::RegisterAndReadInts(EnjoLib::Istream & f)
{
    RegisterAndReadInt (f, OPTIMIZER,           (long int)OptiType::OPTI_TYPE_NONE);
    RegisterAndReadInt (f, OPTIMIZER_METHOD,    (long int)OptiMethod::OPTI_METHOD_GRID);
    RegisterAndReadInt (f, OPTIMIZER_GOAL,      (long int)OptiGoalType::SUM);
    
    RegisterAndReadInt (f, OPTI_CROSS_VALID_BARS_OPTI_H1,   2000);
    RegisterAndReadInt (f, OPTI_CROSS_VALID_BARS_XVAL,      20);
    RegisterAndReadInt (f, OPTI_RANDOM_SAMPLES_NUM,         100);
    RegisterAndReadInt (f, OPTI_RANDOM_MIN_DIFF_PROMILE,    500);    
}
void ConfigOpti::RegisterAndReadFloats(EnjoLib::Istream & f)
{

}
void ConfigOpti::RegisterAndReadStrs(EnjoLib::Istream & f)
{
}

EnjoLib::Str ConfigOpti::GetRelDebDir() const
{
    return GetRelDebDirBase(OPTI_USE_RELEASE);
}
