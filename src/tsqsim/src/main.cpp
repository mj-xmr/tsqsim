#include "App.h"

#include "TSXformTypeString.h"

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
    const char * OPT_PLUGIN  = "plugin";
    try
    {
        ProgramOptionsState popState;
        popState.AddStr(OPT_PLUGIN,    "Plugin name");
        popState.ReadArgs(argc, argv);
        const ProgramOptions pops(popState);

        if (pops.IsHelpRequested())
        {
            const TSXformTypeString types;
            ELO
            LOG << pops.GetHelp() << Nl;
            LOG << "Available transformations for text-based scripting:\n";
            for (const Str & name : types.GetNames())
            {
                LOG << name << " ";
            }
            LOG << Nl;
            return 0;
        }
        auto pluginName = pops.GetStrFromMap (OPT_PLUGIN);
        App().Run(pluginName);
    }
    catch (exception & ex)
    {
        LOGL << StrColour::GenErr(ex.what()) << Nl;
        return 1;
    }
    return 0;
}
