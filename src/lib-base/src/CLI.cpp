#include "CLI.h"
#include "CLIResult.h"
#include "ConfigTS.h"
//#include "TSXformTypeString.h"
#include <Util/CoutBuf.hpp>

#include <EnjoLibBoost/ProgramOptions.hpp>

using namespace EnjoLib;

CLI::CLI(){}
CLI::~CLI(){}

/// TODO: Fill all the possible options
EnjoLib::Result<CLIResult> CLI::GetConfigs(int argc, char ** argv) const
{
    //const char * OPT_PLUGIN  = "plugin";

    const char * OPT_MIN_MONTH = "min-month";
    const char * OPT_MIN_YEAR  = "min-year";
    const char * OPT_MAX_MONTH = "max-month";
    const char * OPT_MAX_YEAR  = "max-year";
    const char * OPT_LATEST_DATE = "latest-date";
    const char * OPT_SYMBOL = "sym";
    const char * OPT_PERIOD  = "per";
    const char * OPT_DATA_FILE  = "data";
    const char * OPT_OUT_DIR   = "out";
    const char * OPT_LAGS  = "lags";
    const char * OPT_PER_SEASONAL  = "per-seasonal";
    const char * OPT_BENCHMARK  = "benchmark";
    const char * OPT_PLOT  = "plot";


    EnjoLib::ProgramOptionsState popState;
    ////popState.AddStr(OPT_PLUGIN,    "Plugin name");
    popState.AddInt(OPT_MIN_MONTH,  "Start month"); /// TODO: Option Add(char*, char*, int & refVal);. A new class beside the old one or replace the old one?
    popState.AddInt(OPT_MIN_YEAR,   "Start year");
    popState.AddInt(OPT_MAX_MONTH,  "End month");
    popState.AddInt(OPT_MAX_YEAR,   "End year");
    popState.AddBool(OPT_LATEST_DATE, "Select latest date");
    popState.AddStr(OPT_SYMBOL,     "Symbol name");
    popState.AddStr(OPT_PERIOD,     "Period name");
    popState.AddStr(OPT_DATA_FILE,  "Data file");
    popState.AddStr(OPT_OUT_DIR,    "Output directory");
    
    popState.AddInt(OPT_LAGS,           ConfigTS::DESCR_PLOT_LAGS_NUM);
    popState.AddInt(OPT_PER_SEASONAL,   ConfigTS::DESCR_PLOT_PERIOD_NUM);
    
    popState.AddBool(OPT_BENCHMARK,     ConfigTS::DESCR_BENCHMARK);
    popState.AddBool(OPT_PLOT,          ConfigTS::DESCR_PLOT_PYTHON);


    popState.ReadArgs(argc, argv);
    const EnjoLib::ProgramOptions pops(popState);

    ConfigSym confSym;
    ConfigTS  confTS;

    if (pops.IsHelpRequested())
    {
        /// TODO: Try also to react also on -h by adding here:
        /**
        bool ProgramOptions::IsHelpRequested() const
        {
            return GetBoolFromMap(ProgramOptionsState::OPT_HELP);
        }
        return GetBoolFromMap(ProgramOptionsState::OPT_HELP || return GetBoolFromMap(ProgramOptionsState::OPT_HELP_MIN););
        const char * OPT_HELP_MIN = "h";
        */
        ELO
        LOG << pops.GetHelp() << Nl;

        LOG << GetAdditionalHelp();
        LOG << Nl;
        LOG << "The default path of the script is: " << ConfigTS::DEFAULT_SCRIPT_FILE_NAME << Nl;
        LOG << "\n(C) 2012-2022 mj-xmr. Licensed under AGPLv3.\n";
        LOG << "https://github.com/mj-xmr/tsqsim\n";
        LOG << "\nRemember to be happy.\n\n";
        return EnjoLib::Result<CLIResult>(CLIResult(confSym, confTS), false);
    }

    confSym.dates.Set0();

    confSym.dates.monthStart 	= pops.GetIntFromMap(OPT_MIN_MONTH);
    confSym.dates.yearStart  	= pops.GetIntFromMap(OPT_MIN_YEAR);
    confSym.dates.monthEnd   	= pops.GetIntFromMap(OPT_MAX_MONTH);
    confSym.dates.yearEnd    	= pops.GetIntFromMap(OPT_MAX_YEAR);
    if (pops.GetBoolFromMap(OPT_LATEST_DATE))
    {
        confSym.dates.SetNoEnd();
    }
    confSym.symbol     		    = pops.GetStrFromMap(OPT_SYMBOL);
    confSym.period     		    = pops.GetStrFromMap(OPT_PERIOD);
    confSym.dataFile  		    = pops.GetStrFromMap(OPT_DATA_FILE);

    confTS.PLOT_LAGS_NUM        = pops.GetIntFromMap(OPT_LAGS);
    confTS.PLOT_PERIOD_NUM      = pops.GetIntFromMap(OPT_PER_SEASONAL);
    confTS.m_outDir             = pops.GetStrFromMap(OPT_OUT_DIR);
    confTS.BENCHMARK            = pops.GetBoolFromMap(OPT_BENCHMARK);
    confTS.PLOT_PYTHON          = pops.GetBoolFromMap(OPT_PLOT);

    //auto pluginName = pops.GetStrFromMap (OPT_PLUGIN);

    CLIResult res(confSym, confTS);

    return EnjoLib::Result<CLIResult>(CLIResult(confSym, confTS), true);
}
