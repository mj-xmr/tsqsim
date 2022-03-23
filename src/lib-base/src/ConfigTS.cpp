#include "ConfigTS.h"

#include "ConfigDirs.h"
#include "Consts.h"
#include "PriceType.h"

//#include <Util/Except.hpp>
#include <Ios/Osstream.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/Pair.hpp>

using namespace std;
using namespace EnjoLib;

const char * ConfigTS::DEFAULT_SCRIPT_FILE_NAME     = "ts-xform-script.txt";
const char * ConfigTS::DEFAULT_SCRIPT_FILE_NAME_R   = "r-custom.R";
const char * ConfigTS::DEFAULT_SCRIPT_FILE_NAME_PY  = "py_statsmodels.py";
const char * ConfigTS::DEFAULT_SCRIPT_FILE_NAME_GEN = "data-generation.txt";


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
    RegisterAndReadBool(f, crashOnRecoverableErrors, 0, "Crash on err",     "Crash on recoverable errors");
    RegisterAndReadBool(f, PLOT_SERIES,              1, "Plot series",      "Plot output series after evaluation");
    RegisterAndReadBool(f, PLOT_BASELINE,            1, "Plot baseline",    "Plot baseline prediction in QT app");
    RegisterAndReadBool(f, PLOT_PYTHON,              0, "Plot with Python", DESCR_PLOT_PYTHON);
    RegisterAndReadBool(f, PLOT_PYTHON_ACF,          0, "Plot ACF with Python", "Plot the Auto Correlation Function in Python backend");
    RegisterAndReadBool(f, MT_XFORM,                 1, "MT xform",         "Perform the transformations in a multithreaded way (still unstable)");
    RegisterAndReadBool(f, MT_REPORT,                0, "MT report",        "Generate report in multithreaded way (still unstable)");
    RegisterAndReadBool(f, USE_VECTOR_PRED,          1, "Opti vec pred",    "Use optimized vectored prediction");
    RegisterAndReadBool(f, BENCHMARK,                0, "Benchmark",    DESCR_BENCHMARK);
    
}

void ConfigTS::RegisterAndReadInts(EnjoLib::Istream & f)
{
    RegisterAndReadInt (f, PRED_TYPE, 0);
    RegisterAndReadInt (f, PRICE_TYPE, static_cast<long int>(PriceType::HIGH));
    RegisterAndReadInt (f, PLOT_LAGS_NUM, 30);
    RegisterAndReadInt (f, PLOT_PERIOD_NUM, 30);
}
void ConfigTS::RegisterAndReadFloats(EnjoLib::Istream & f)
{
}
void ConfigTS::RegisterAndReadStrs(EnjoLib::Istream & f)
{
    const ConfigDirs dirs;
    RegisterAndReadStr(f, m_scriptPathTxt,      dirs.DIR_SCRIPTS2 + DEFAULT_SCRIPT_FILE_NAME);
    RegisterAndReadStr(f, m_scriptPathTxtR,     dirs.DIR_SCRIPTS2 + DEFAULT_SCRIPT_FILE_NAME_R);
    RegisterAndReadStr(f, m_scriptPathTxtGen,   dirs.DIR_SCRIPTS2 + DEFAULT_SCRIPT_FILE_NAME_GEN);
    RegisterAndReadStr(f, m_scriptPathTxtPy,    dirs.DIR_SCRIPTS2 + DEFAULT_SCRIPT_FILE_NAME_PY);
    //RegisterAndReadStr(f, m_outDir,   "");
}

void ConfigTS::SetScriptNamePy(const EnjoLib::Str & name)
{
    const ConfigDirs dirs;
    m_scriptPathTxtPy = dirs.DIR_SCRIPTS2 + name;
}

PredictorType ConfigTS::GetPredType() const
{
    return static_cast<PredictorType>(PRED_TYPE);
}

void ConfigTS::SetPredType(const PredictorType & type)
{
    PRED_TYPE = static_cast<long int>(type);
}

PriceType ConfigTS::GetPriceType() const
{
    return static_cast<PriceType>(PRICE_TYPE);
}
void ConfigTS::SetPriceType(const PriceType & type)
{
    PRICE_TYPE = static_cast<long int>(type);
}

void ConfigTS::UpdateFromOther(const ConfigTS & cfgTSCmdLine)
{
    if (cfgTSCmdLine.m_outDir.size()) m_outDir = cfgTSCmdLine.m_outDir;
    
    if (cfgTSCmdLine.PLOT_LAGS_NUM > 0)
    {
        PLOT_LAGS_NUM = cfgTSCmdLine.PLOT_LAGS_NUM;
    }
    if (cfgTSCmdLine.PLOT_PERIOD_NUM > 0)
    {
        PLOT_PERIOD_NUM = cfgTSCmdLine.PLOT_PERIOD_NUM;
    }
    if (cfgTSCmdLine.PRED_TYPE >= 0)
    {
        PRED_TYPE = cfgTSCmdLine.PRED_TYPE;
    }
    if (cfgTSCmdLine.BENCHMARK)
    {
        BENCHMARK = cfgTSCmdLine.BENCHMARK;
    }
    if (cfgTSCmdLine.PLOT_PYTHON)
    {
        PLOT_PYTHON = cfgTSCmdLine.PLOT_PYTHON;
    }
}
