#include "TicksProviderOrderedSeries.h"
#include "Ticks.h"
#include "TradeUtil.h"
#include "OrderedSeries.h"
#include "SymbolFactoryClean.h"

#include <Ios/Osstream.hpp>
#include <Util/Str.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Tokenizer.hpp>
#include <Util/CharManipulations.hpp>

using namespace EnjoLib;

TicksProviderOrderedSeries::TicksProviderOrderedSeries(){}
TicksProviderOrderedSeries::~TicksProviderOrderedSeries(){}

VecStr TicksProviderOrderedSeries::ConvertStat(const VecStr & raw)
{
    VecStr lines;
    CorPtr<ISymbol> sym = SymbolFactoryClean().Create("Ordered");
    OrderedSeries oser(*sym);

    const CharManipulations cman;
    for (const Str & line : raw)
    {
        oser.FeedVal(cman.ToDouble(line));
    }
    const auto & icandles = oser.GetCandles();
    const auto & candles = icandles.GetDataIter();
    for (const Candle & can : candles)
    {
        const Str & conv = ConvertStatSingle(can);
        lines.push_back(conv);
    }
    return lines;
}

EnjoLib::Str TicksProviderOrderedSeries::ConvertStatSingle(const Candle & line) /// TODO: Unit test and optimize
{
    const CharManipulations cman;
    const TradeUtil tut;
    const DateInt dateTime = line.GetDate();
    const Str & txnumbStr = cman.ToStr(line.GetClose());

    return tut.GetLineFXfromSeries(dateTime, txnumbStr);
}

VecStr TicksProviderOrderedSeries::Convert(const VecStr & raw) const
{
    return ConvertStat(raw);
}
