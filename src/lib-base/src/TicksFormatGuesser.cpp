#include "TicksFormatGuesser.h"

#include <Util/Str.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Tokenizer.hpp>

using namespace EnjoLib;

TicksFormatGuesser::TicksFormatGuesser(){}
TicksFormatGuesser::~TicksFormatGuesser(){}

TicksFormat TicksFormatGuesser::Run(const VecStr & lines) const
{
    const Str & line = lines.at(1); // It's safer to assume that the 1st (index = 0) line is the header

    const Str delims = ",";  // Possibility to extend by other delims
    const char delim = delims.at(0);
    return Run(line, delim);
}

TicksFormat TicksFormatGuesser::Run(const EnjoLib::Str & line, const char delim) const
{
    const Tokenizer tok;
    const VecStr & tokens = tok.Tokenize(line, delim);
    const int len = tokens.size();
    ELO
    LOG << "TicksFormatGuesser: size = " << len << ", line = " << line << " ";
    if (len == 1)
    {
        LOG << "Ordered series\n";
        return TicksFormat::FMT_ORDERED_SERIES;
    }
    if (len == 2)
    {
        LOG << "Timestamp value\n";
        return TicksFormat::FMT_TIMESTAMP_VALUE;
    }
    if (len == 8)
    {
        LOG << "Timestamp OHLC\n";
        return TicksFormat::FMT_FX;
    }

    LOG << "Unknown!\n";
    return TicksFormat::FMT_UNKNOWN;
}
