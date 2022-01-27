#include "TicksProviderAdaptive.h"

#include "TicksFormat.h"
#include "TicksProviderFake.h"
#include "TicksProviderXMR.h"
#include "TicksProviderOrderedSeries.h"
#include "Ticks.h"
#include "TradeUtil.h"
#include "TicksFormatGuesser.h"

#include <Ios/Osstream.hpp>
#include <Util/Str.hpp>
#include <Util/Tokenizer.hpp>
//#include <Template/LoopThreadedT

#include <Util/Str.hpp>
#include <Util/Except.hpp>

using namespace EnjoLib;

TicksProviderAdaptive:: TicksProviderAdaptive(){}
TicksProviderAdaptive::~TicksProviderAdaptive(){}

CorPtr<TicksProviderBinary> TicksProviderAdaptive::Create(const TicksFormat & format) const
{
    switch (format)
    {
    case TicksFormat::FMT_FX:
        return CorPtr<TicksProviderBinary>(new TicksProviderBinary());
    case TicksFormat::FMT_ORDERED_SERIES:
        return CorPtr<TicksProviderBinary>(new TicksProviderOrderedSeries());
    case TicksFormat::FMT_TIMESTAMP_VALUE:
        return CorPtr<TicksProviderBinary>(new TicksProviderXMR());
    case TicksFormat::FMT_UNKNOWN:
        break;
    }
    throw EnjoLib::ExceptNotImpl("TicksProviderAdaptive::Create(): Not implemented type");
}

VecStr TicksProviderAdaptive::Convert(const VecStr & raw) const
{
    const TicksFormatGuesser guesser;
    const TicksFormat & format = guesser.Run(raw);
    const CorPtr<TicksProviderBinary> provider = Create(format);

    return provider->Convert(raw);
}
