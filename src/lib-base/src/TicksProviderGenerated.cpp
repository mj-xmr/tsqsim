#include "TicksProviderGenerated.h"
#include "ConfigMan.h"
#include "ConfigTS.h"
#include "OrderedSeries.h"
#include "SymbolFactoryClean.h"
#include "Ticks.h"

#include <Ios/Osstream.hpp>
#include <Ios/Ifstream.hpp>
#include <Math/RandomMath.hpp>
#include <Math/GeneralMath.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Except.hpp>
#include <Util/Tokenizer.hpp>
#include <Util/CharManipulations.hpp>

#include <STD/VectorCpp.hpp>

using namespace EnjoLib;

TicksProviderGenerated::TicksProviderGenerated()
{
    LOGL << "TicksProviderGenerated::TicksProviderGenerated()\n";
}

TicksProviderGenerated::~TicksProviderGenerated()
{
    //dtor
}

CorPtr<ITicks> TicksProviderGenerated::GetPeriod(const Str & symbolName, const Str & periodName) const
{
    const SymbolFactoryClean symFact;
    CorPtr<ITicks> ticks = GetTicks(symbolName);
    CorPtr<ISymbol> isym = symFact.Create(symbolName, VecStr { periodName } );
    const auto ticksView = ticks->GetTicksView();
    for (const Tick & tic : ticksView)
    {
        isym->Feed(tic);
    }
    const IPeriod & per = isym->GetPeriod(periodName);
    
    return CorPtr<ITicks>(new Ticks(*per.GetCandles().ToTicks()));
}

CorPtr<ITicks> TicksProviderGenerated::GetTicks(const Str & symbolName, const ConfigSym * confSym) const
{
    const ConfigTS & cfgTS = *gcfgMan.cfgTS;
    
    const Tokenizer tok;
    const Str & fname = cfgTS.m_scriptPathTxtGen;
    Str line1st;
    { Ifstream file(fname); } /// TODO: Move functionality to tok.GetLine
    //LOG << "Reading script file: '" << fname << "'" << Nl;
    const VecStr & lines = tok.GetLines(fname);
    for (const Str & line : tok.FilterLines(lines))
    {
        //LOG << "Script line: '" << line << "'" << Nl;
        //m_xformMan.AddXForm(line);
        line1st = line;
        break; // only use the 1st line for now
    }
    
    const VecStr & pars = tok.Tokenize(line1st);
    if (pars.at(0) != "constant")
    {
        throw ExceptGeneral("Wrong type = " + pars.at(0));
    }
    const CharManipulations cman;
    const int    len    = cman.ToDouble(pars.at(1));
    const double mean   = cman.ToDouble(pars.at(2));
    const double stdDev = cman.ToDouble(pars.at(3));

    const SymbolFactoryClean symFact;
    const auto isym = symFact.Create(symbolName);
    OrderedSeries oser(*isym);
    
    const RandomMath rand;
    const GeneralMath gmat;
    double open = 0;
    for (int i = 0; i < len; ++i)
    {
        const double close = rand.Rand(mean - stdDev, mean + stdDev);
        const double stretch = 1.5;
        const double high1  = rand.Rand(0, stdDev);
        const double low1   = rand.Rand(0, stdDev);
        const double high = close + high1;
        const double low = close - low1;
        if (i == 0)
        {
            open = close;
        }
        //oser.FeedVal(open, close, high, low);
        oser.FeedVal(close);
        
        open = close;
    }
    return CorPtr<ITicks>(new Ticks(*oser.GetCandles().ToTicks()));
}
