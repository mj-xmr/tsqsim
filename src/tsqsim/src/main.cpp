#include "App.h"

#include "TSXformTypeString.h"
#include "ConfigSym.h"
#include "ConfigTS.h"

#include <EnjoLibBoost/ProgramOptions.hpp>

#include <Math/GeneralMath.hpp>
#include <Util/Str.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/StrColour.hpp>
#include <Template/Array.hpp>

#include <exception>

using namespace std;
using namespace EnjoLib;

int main(int argc, char ** argv)
{
    //const char * OPT_PLUGIN  = "plugin";

    const char * OPT_MIN_MONTH = "min-month";
    const char * OPT_MIN_YEAR  = "min-year";
    const char * OPT_MAX_MONTH = "max-month";
    const char * OPT_MAX_YEAR  = "max-year";
	//const char * OPT_LATEST_DATE = "latest-date";
	const char * OPT_SYMBOL = "sym";
    const char * OPT_PERIOD  = "per";

    try
    {
        ProgramOptionsState popState;
        ////popState.AddStr(OPT_PLUGIN,    "Plugin name");
        popState.AddInt(OPT_MIN_MONTH,  "Start month"); /// TODO: Option Add(char*, char*, int & refVal);. A new class beside the old one or replace the old one?
        popState.AddInt(OPT_MIN_YEAR,   "Start year");
        popState.AddInt(OPT_MAX_MONTH,  "End month");
        popState.AddInt(OPT_MAX_YEAR,   "End year");
        popState.AddStr(OPT_SYMBOL,     "Symbol name");
        popState.AddStr(OPT_PERIOD,     "Period name");

        popState.ReadArgs(argc, argv);
        const ProgramOptions pops(popState);

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

            const TSXformTypeString types;
            ELO
            LOG << pops.GetHelp() << Nl;
            LOG << "Available transformations for text-based scripting:\n";
            for (const Str & name : types.GetNames())
            {
                LOG << name << " ";
            }
            LOG << Nl;
            LOG << "The default path of the script is: " << ConfigTS::DEFAULT_SCRIPT_FILE_NAME << Nl;
            LOG << "\n(C) 2012-2022 mj-xmr. Licensed under AGPLv3.\n";
            LOG << "https://github.com/mj-xmr/tsqsim\n";
            LOG << "\nRemember to be happy.\n\n";
            return 0;
        }

        ConfigSym confSym;
        confSym.dates.Set0();

        confSym.dates.monthStart 	= pops.GetIntFromMap(OPT_MIN_MONTH);
        confSym.dates.yearStart  	= pops.GetIntFromMap(OPT_MIN_YEAR);
        confSym.dates.monthEnd   	= pops.GetIntFromMap(OPT_MAX_MONTH);
        confSym.dates.yearEnd    	= pops.GetIntFromMap(OPT_MAX_YEAR);
        confSym.symbol     		    = pops.GetStrFromMap(OPT_SYMBOL);
        confSym.period     		    = pops.GetStrFromMap(OPT_PERIOD);


        //auto pluginName = pops.GetStrFromMap (OPT_PLUGIN);
        App().Run(confSym);
    }
    catch (exception & ex)
    {
        LOGL << StrColour::GenErr(ex.what()) << Nl;
        return 1;
    }
    return 0;
}
