#include "IParams.h"
#include "ISymbol.h"
#include "IPeriod.h"

#include "StrategyType.h"
#include "StrategyFactoryName.h"
//#include "ISimulatorAccum.h"
#include "ConfigMan.h"

#include <Util/ProtocolCreator.h>
#include <Util/Str.hpp>



IParams::IParams()
{
    //ctor
}

IParams::~IParams()
{
    //dtor
}

EnjoLib::Str IParams::ToStr() const
{
    EnjoLib::ProtocolCreator pcc('|');
    //const char sepLoc = ';';

    //cout << "DUPA1: " << gcfgMan.cfgSym->GetDateFromToStr();
    pcc.AddStr(GetSymbol().GetName());
    pcc.AddStr(GetPeriod().GetNumTicks());
    pcc.AddStr(1); // Tick count
    pcc.AddStr(GetName() + "+" + StrategyFactoryName().Create(GetStrategy()));
    pcc.AddStr(gcfgMan.GetConfigString()); // Tick
    pcc.AddStr("0;0;"); // Data

    return pcc.Get();
}
