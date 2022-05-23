#include "TicksProviderTxtAdHoc.h"
#include "ConfigMan.h"
#include "ConfigSym.h"
#include "TicksFormatGuesser.h"
#include "TicksProviderXMR.h"
#include "ITicks.h"
#include "Tick.h"

#include <Ios/Osstream.hpp>
#include <Ios/Ifstream.hpp>
#include <Util/Str.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Tokenizer.hpp>
#include <Util/CharManipulations.hpp>
#include <Statistical/Assertions.hpp>

using namespace EnjoLib;

TicksProviderTxtAdHoc::TicksProviderTxtAdHoc(){}
TicksProviderTxtAdHoc::~TicksProviderTxtAdHoc(){}

CorPtr<ITicks> TicksProviderTxtAdHoc::GetTicks(const Str & symbolName, const ConfigSym * confSym) const
{
    const ConfigSym & cfgSym = *gcfgMan.cfgSym;
    
    Ifstream file(cfgSym.dataFile);
    const Tokenizer tok;
    Str line1st;
    const VecStr & lines = tok.GetLines(file, true);
    const TicksFormat fmt = TicksFormatGuesser().Run(lines);
    if (fmt != TicksFormat::FMT_TIMESTAMP_VALUE)
    {
        Assertions::Throw(("Unhandled format:\n" + lines.at(0)).c_str(), "TicksProviderTxtAdHoc::GetTicks");
    }
    const VecStr & linesConv = TicksProviderXMR().ConvertStat(lines);
    
    CorPtr<ITicks> ticks = ITicks::Create();
    for (const Str & line : linesConv)
    {
        ticks->Add(Tick(line));
    }
    return CorPtr<ITicks>(ticks.release());
}
