#include "App.h"
#include <ConfigMan.h>
#include <ISymbol.h>
#include <IMainTester.h>
#include <SymbolFactoryClean.h>
#include "SimulatorTSFactory.h"
//#include "SymbolFactory.h"
#include "IMainTester.h"
#include "TSFunType.h"
#include "TSFunFactory.h"
#include "TSInput.h"
#include "ConfigTS.h"
#include "ConfigTF.h"
#include "ConfigTF2.h"
#include "ConfigSym.h"

#include <Template/UniquePtrVecFwd.hpp>
#include <Template/UniquePtr.hpp>
#include <Util/CoutBuf.hpp>

#include <Util/Trim.hpp>
#include <STD/Iostream.hpp>

#include <STD/VectorCpp.hpp>

using namespace std;
using namespace EnjoLib;

App::App(){}

void App::Run(const ConfigSym & confSymCmdLine) const
{
    const ConfigTF  & confTF    = *gcfgMan.cfgTF.get();
    do
    {
        gcfgMan.Read();

        const ConfigTS & confTS     = *gcfgMan.cfgTS.get();
        const ConfigTF2 & confTF2   = *gcfgMan.cfgTF2.get();
        ConfigSym & confSym         = *gcfgMan.cfgSym.get();

        UpdateCfgSym(confSymCmdLine, confSym);

        VecStr symbols = {confSym.symbol};
        VecStr periods = {confSym.period};

        const SymbolFactoryClean symFact;
        //VecUPtr<ISymbol> symbolsVec = IMainTester::Create(symFact, &confTF2, &confSym)->GetSymbolMT(symbols, periods);
        //const IPeriod & per = symbolsVec.at(0)->GetPeriod(periods.at(0));
        CorPtr<ISymbol> symbol = IMainTester::Create(symFact, &confTF2, &confSym)->GetSymbol(confSym.symbol, periods);
        const IPeriod & per = symbol->GetPeriod(periods.at(0));

        const SimulatorTSFactory simFact;
        const TSFunFactory tsFunFact;

        //const TSFunType tsFunType = TSFunType::PRINT_ALL;
        //const TSFunType tsFunType = TSFunType::PRINT_CUMUL;
        //const TSFunType tsFunType = TSFunType::XFORM;
        //const TSFunType tsFunType = TSFunType::LUA;
        const TSFunType tsFunType = TSFunType::TXT;
        const TSInput tsin(per, confTS);

        auto fun = tsFunFact.Create(tsin, tsFunType);
        auto sim = simFact.CreateTS(tsin, *fun);

        sim->RunRaw();

        {LOGL << confSym.GetDateFromToStr(false);}

        if (confTF.REPEAT)
        {
            cout << "q to quit" << endl;
            EnjoLib::Str line;
            getline(cin, line.strRW());
            line = EnjoLib::Trim().trim(line);
            if (line == "q")
                break;
        }

    } while (confTF.REPEAT);
    //LOGL << "Plugin name = " << plugin << Nl;
}

void App::UpdateCfgSym(const ConfigSym & cfgSymCmdLine, ConfigSym & cfgFile) const
{
    cfgFile.dates.UpdateIfNot0(cfgSymCmdLine.dates);
    if (cfgSymCmdLine.symbol.size()) cfgFile.symbol = cfgSymCmdLine.symbol;
    if (cfgSymCmdLine.period.size()) cfgFile.period = cfgSymCmdLine.period;
}
