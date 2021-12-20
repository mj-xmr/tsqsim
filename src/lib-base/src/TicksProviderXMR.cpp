#include "TicksProviderXMR.h"
#include "Ticks.h"
#include "TradeUtil.h"

#include <Ios/Osstream.hpp>
#include <Util/Str.hpp>
#include <Util/Tokenizer.hpp>
//#include <Template/LoopThreadedTpl.hpp>

using namespace std;
using namespace EnjoLib;

TicksProviderXMR::TicksProviderXMR(){}
TicksProviderXMR::~TicksProviderXMR(){}

VecStr TicksProviderXMR::ConvertStat(const VecStr & raw)
{
    /// TODO: It is acceptable but suboptimal to convert to a special format first, although all the data are already available.
    /// TODO: Eventually use: #include <Template/LoopThreadedTpl.hpp>
    /// TODO: Use a textual format descriptor with system-known columns (like the header of a CSV file) and a pre-defined separator. No custom C++ Providers have to be written then.
    /// TODO: Create a DataInputFormat class
    /// TODO: Give a possibility to guess the format without the descriptor - test throuroughly
    /// ^ The system ultimately only needs closing values, not even the timestamps (a.k.a. "Ordered series").
    
    VecStr lines;
    lines.DataRW().reserve(raw.size());
    for (const Str & line : raw)
    {
        lines.push_back(ConvertStatSingle(line));
    }
    //std::function<decltype(ConvertStatSingle)> f_conv = &ConvertStatSingle;
    //const std::vector<Str> & lines = ConvertVectorThreaded(raw.Data(), f_conv); // Causes a dead loop later at storing.
    
    return lines;
}

EnjoLib::Str TicksProviderXMR::ConvertStatSingle(const EnjoLib::Str & line)
{
    const Tokenizer tok;
    const TradeUtil tut;
    const VecStr & toks = tok.Tokenize(line, ',');
    const Str & tstampStr = toks.at(0);
    const Str & txnumbStr = toks.at(1);

    const DateInt dateTime = tut.Timestamp2DateInt(tstampStr);
    const Str & date = tut.Date2DateRawStr(dateTime);
    const Str & time = tut.Date2TimeRawStr(dateTime);

    Osstream ostr;
    ostr << "MONERO,"  << date  << ","  << time;
    const Str txNumbStrLine = "," + txnumbStr;
    for (int i = 0; i < 4; ++i)
    {
        ostr << txNumbStrLine;
    }
    ostr << ",0";

    return ostr.str();
}

VecStr TicksProviderXMR::Convert(const VecStr & raw) const
{
    return ConvertStat(raw);
}
