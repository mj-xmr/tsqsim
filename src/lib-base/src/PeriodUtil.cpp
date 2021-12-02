#include "PeriodUtil.h"
#include "Candle.h"
#include "IDataProvider.h"
#include "IBufferCandles.h"
#include "TradeUtil.h"
#include "SymbolFactoryAbstract.h"
#include "Ticks.h"
#include "IPeriod.h"
#include "ISymbol.h"
#include "MessageParser.h"
#include <Template/CorradePointer.h>
#include <Template/Array.hpp>
#include <Ios/Ifstream.hpp>
#include <Ios/Osstream.hpp>
#include <Util/CoutBuf.hpp>

using namespace std;

PeriodUtil::PeriodUtil(){}

EnjoLib::Str PeriodUtil::Data2Str(const IDataProvider & data) const
{
    EnjoLib::Osstream oss;
    const EnjoLib::Str symName = data.GetSymbolName();
    const char d = ',';
    const TradeUtil tut;
    //cout << "Data2Str size = " << data.GetCandles().GetData().size() << endl;
    for (const Candle & can : data.GetCandles().GetDataIter())
    {
        const DateInt dateCandle = can.GetDateOpen();
        //const DateInt dateCandle = can.GetDate();
        if (dateCandle == 0)
            continue;
        const EnjoLib::Str date = tut.Date2DateRawStr(dateCandle);
        const EnjoLib::Str time = tut.Date2TimeRawStr(dateCandle);
        const float o = can.GetOpen();
        const float h = can.GetHigh();
        const float l = can.GetLow();
        const float c = can.GetClose();
        const float v = can.GetVol();
        oss << symName << d << date << d << time << d;
        oss << o << d << h << d << l << d << c << d << v << '\n';
    }
    return oss.str();
}

Corrade::Containers::Pointer<ISymbol> PeriodUtil::LoadSymbolFromFile(const SymbolFactoryAbstract & symFact, const EnjoLib::Str & symName, const VecStr & periods, const EnjoLib::Str & fileName, bool calcTech) const
{
    return LoadSymbolFromFileSetCan(symFact, symName, periods, fileName, calcTech);
    //return LoadSymbolFromFileFeed(symName, periods, fileName, calcTech);
}

Corrade::Containers::Pointer<ISymbol> PeriodUtil::LoadSymbolFromFileFeed(const SymbolFactoryAbstract & symFact, const EnjoLib::Str & symName, const VecStr & periods, const EnjoLib::Str & fileName, bool calcTech) const
{
    return LoadSymbolFromFileCommon(symFact, true, symName, periods, fileName, calcTech);
}

Corrade::Containers::Pointer<ISymbol> PeriodUtil::LoadSymbolFromFileSetCan(const SymbolFactoryAbstract & symFact, const EnjoLib::Str & symName, const VecStr & periods, const EnjoLib::Str & fileName, bool calcTech) const
{

    return LoadSymbolFromFileCommon(symFact, false, symName, periods, fileName, calcTech);
}

Corrade::Containers::Pointer<ISymbol> PeriodUtil::LoadSymbolFromFileMT(const SymbolFactoryAbstract & symFact, const EnjoLib::Str & symName, const VecStr & periods, const EnjoLib::Str & fileName, bool calcTech) const
{
    CorPtr<ITicks> ticks = ITicks::Create();
    EnjoLib::Ifstream is(fileName);
    EnjoLib::Str line;
    while (GetLine(is, line))
    {
        try
        {
            //cout << line << endl;
            MessageParser mpLoc;
            mpLoc.Parse(line);
            const Tick & tick = mpLoc.GetTick();
            if (tick.IsValid())
                ticks->Add(tick);
        }
        catch (exception & e)
        {
            EnjoLib::Osstream oss;
            oss << "PeriodUtil::LoadSymbolFromFileMT(): fileName = " << fileName << "\nLine = " << line << EnjoLib::Nl;
            //throw EnjoLib::ExceptInvalidArg(STRACE_RETHROW(e, oss.str()) );
            LOGL << e.what() << "\n" << oss.str();
        }
    }
    return LoadSymbolFromFileCommon(symFact, true, symName, periods, fileName, *ticks, calcTech);
}

Corrade::Containers::Pointer<ISymbol> PeriodUtil::LoadSymbolFromFileCommon(const SymbolFactoryAbstract & symFact, bool feed, const EnjoLib::Str & symName, const VecStr & periods, const EnjoLib::Str & fileName, bool calcTech) const
{
    const bool skipHeader = false;
    const Ticks ticks(symName, fileName, 0, skipHeader);

    return LoadSymbolFromFileCommon(symFact, feed, symName, periods, fileName, ticks, calcTech);
}

Corrade::Containers::Pointer<ISymbol> PeriodUtil::LoadSymbolFromFileCommon(const SymbolFactoryAbstract & symFact, bool feed, const EnjoLib::Str & symName, const VecStr & periods, const EnjoLib::Str & fileName, const ITicks & ticks, bool calcTech) const
{
    Corrade::Containers::Pointer<ISymbol> psym = symFact.Create(symName, periods);

    //cout << "Ticks len = " << ticks.GetTicks().size() << endl;
    if (feed)
        for (const Tick & t : ticks) psym ->Feed(t);
    else
        for (IPeriod * per : psym->GetPeriodsRW()) per->SetCandles(ticks.ToCandles());
    LOGL << "\n";
    if (calcTech)
    {
        psym->CalcTech();
    }
    return psym;
}
