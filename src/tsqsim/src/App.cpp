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
#include <STD/Iostream.hpp> /// TODO: Remove


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

        confSym.UpdateFromOther(confSymCmdLine);

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
        const TSFunType tsFunType = TSFunType::TXT; /// TODO: make user's choice
        const TSInput tsin(per, confTS);

        auto fun = tsFunFact.Create(tsin, tsFunType);
        CorPtr<ISimulatorTS> sim = simFact.CreateTS(tsin, *fun);

        sim->RunRaw();

        {LOGL << confSym.GetDateFromToStr(false);}

        if (confTF.REPEAT)
        {
            /// TODO: Log::WriteLine("q to quit"); in CoutBuf
            cout << "q to quit" << endl;
            EnjoLib::Str line;
            /// TODO: GetLine in Ios wrapper
            getline(cin, line.strRW());
            line = EnjoLib::Trim().trim(line);
            if (line == "q")
                break;
        }

    } while (confTF.REPEAT);
    //LOGL << "Plugin name = " << plugin << Nl;
}
