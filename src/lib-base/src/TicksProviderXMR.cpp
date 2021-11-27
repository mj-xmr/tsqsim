#include "TicksProviderXMR.h"
#include "Ticks.h"
#include "TradeUtil.h"

#include <Util/Str.hpp>
#include <Util/Tokenizer.hpp>

using namespace std;
using namespace EnjoLib;

TicksProviderXMR::TicksProviderXMR(){}
TicksProviderXMR::~TicksProviderXMR(){}

VecStr TicksProviderXMR::ConvertStat(const VecStr & raw)
{
    /// TODO: It is acceptable but suboptimal to convert to a special format first, although all the data are already available.
    /// TODO: Eventually use: #include <Template/LoopThreadedTpl.hpp>
    /// TODO: Use a textual format descriptor with system-known columns (like the header of a CSV file) and a pre-defined separator. No custom C++ Providers have to be written then.
    /// ^ The system ultimately only needs closing values, not even the timestamps.
    VecStr lines;
    const Tokenizer tok;
    const TradeUtil tut;
    for (const Str & line : raw)
    {
        const VecStr & toks = tok.Tokenize(line, ',');
        const Str & tstampStr = toks.at(0);
        const Str & txnumbStr = toks.at(1);

        const DateInt dateTime = tut.Timestamp2DateInt(tstampStr);
        const Str & date = tut.Date2DateRawStr(dateTime);
        const Str & time = tut.Date2TimeRawStr(dateTime);

        Str res = "MONERO," + date + "," + time;
        for (int i = 0; i < 4; ++i)
        {
            res += "," + txnumbStr;
        }
        res += ",0";

        lines.push_back(res);
    }

    return lines;
}

VecStr TicksProviderXMR::Convert(const VecStr & raw) const
{
    return ConvertStat(raw);
}
