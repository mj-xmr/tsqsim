#include "TicksProviderFake.h"
#include "Ticks.h"
#include "TradeUtil.h"
#include "TicksProviderXMR.h"

#include <Util/Str.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Tokenizer.hpp>

using namespace std;
using namespace EnjoLib;

CorPtr<ITicks> TicksProviderFake::GetTicks(const Str & symbolName, const ConfigSym * confSym) const
{
    const VecStr & lines = Generate();
    return CorPtr<ITicks>(new Ticks(symbolName, lines));
}

CorPtr<ITicks> TicksProviderFake::GetPeriod(const Str & symbolName, const Str & periodName) const
{
    return GetTicks(symbolName);
}

VecStr TicksProviderFake::Generate() const
{
    VecStr lines;
    lines.push_back("EURCAD,20140831,235300,1.4269,1.4269,1.4269,1.4269,4");
    lines.push_back("EURCAD,20140831,235400,1.4269,1.4270,1.4269,1.4270,4");
    lines.push_back("EURCAD,20140831,235500,1.4269,1.4271,1.4269,1.4271,4");
    lines.push_back("EURCAD,20140831,235600,1.4272,1.4276,1.4272,1.4276,4");
    lines.push_back("EURCAD,20140831,235700,1.4275,1.4276,1.4275,1.4276,4");
    lines.push_back("EURCAD,20140831,235800,1.4275,1.4276,1.4275,1.4275,4");
    lines.push_back("EURCAD,20140831,235900,1.4276,1.4276,1.4275,1.4275,4");
    return lines;
}


CorPtr<ITicks> TicksProviderXMRFake::GetTicks(const Str & symbolName, const ConfigSym * confSym) const
{
    const VecStr & lines = Generate();
    const VecStr & linesConv = TicksProviderXMR::ConvertStat(lines);
    /// TODO: Analyze the linesConv, if the format is still OK, because they don't seem to scale up very well.

    CorPtr<ITicks> ret(new Ticks(symbolName, linesConv));
    //LOGL << "TicksProviderXMRFake: Got ticks of: " << ret->size() << Nl;
    return ret;
}

CorPtr<ITicks> TicksProviderXMRFake::GetPeriod(const Str & symbolName, const Str & periodName) const
{
    return GetTicks(symbolName);
}

VecStr TicksProviderXMRFake::Generate() const
{
    VecStr lines;
    //block_timestamp,tx_num
    lines.push_back("1397823189,6");
    lines.push_back("1397836652,5");
    lines.push_back("1397858361,30");
    lines.push_back("1397860444,18");
    lines.push_back("1397884755,6");
    lines.push_back("1397884994,2");
    lines.push_back("1397886290,8");
    lines.push_back("1397919961,27");
    lines.push_back("1397940297,282");
    lines.push_back("1397944148,22");
    lines.push_back("1397944160,396");
    return lines;
}


CorPtr<ITicks> TicksProviderOrderedSeriesFake::GetTicks(const Str & symbolName, const ConfigSym * confSym) const
{
    const VecStr & lines = Generate();
    return CorPtr<ITicks>(new Ticks(symbolName, lines));
}

CorPtr<ITicks> TicksProviderOrderedSeriesFake::GetPeriod(const Str & symbolName, const Str & periodName) const
{
    return GetTicks(symbolName);
}

VecStr TicksProviderOrderedSeriesFake::Generate() const
{
    VecStr lines;
    lines.push_back("6");
    lines.push_back("5");
    lines.push_back("30");
    lines.push_back("18");
    lines.push_back("6");
    lines.push_back("2");
    lines.push_back("8");
    lines.push_back("27");
    lines.push_back("282");
    lines.push_back("22");
    lines.push_back("396");
    return lines;
}

