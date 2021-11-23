#include "StartEnd.h"
#include "TradeUtilThin.h"
#include "IStrategy.h"
#include "IDataProvider.h"

#include <Util/Tokenizer.hpp>
#include <Util/CharManipulations.hpp>

#include <Util/Except.hpp>
#include <Util/Str.hpp>

#include <Util/CharManipulations.hpp>

using namespace std;
using namespace EnjoLib;

StartEnd::StartEnd(int start, int end)
: start(start), end(end) {}

bool StartEnd::IsValid() const
{
    if (start == 0 && end == 0)
    {
        return false;
    }
    if (start > end)
    {
        return false;
    }
    if (start < 0)
    {
        return false;
    }
    return true;
}

EnjoLib::Str StartEnd::ToStr() const
{
    //return "(" + EnjoLib::CharManipulations().ToStr(start) + ", " + EnjoLib::CharManipulations().ToStr(end) + ")";
    return EnjoLib::CharManipulations().ToStr(start) + " " + EnjoLib::CharManipulations().ToStr(end);
}

void StartEnd::FromStr(const EnjoLib::Str & str)
{
    const Tokenizer tok;
    const CharManipulations cman;
    const auto & vals2 = tok.Tokenize(str);
    start = cman.ToInt(vals2.at(0));
    end   = cman.ToInt(vals2.at(1));
}

bool StartEnd::operator== (const StartEnd & other) const
{
    return start == other.start && end == other.end;
}

//StartEnd StartEnd::ConvertIndexes(const IDataProvider & hasLen) const
StartEnd StartEnd::ConvertIndexes(const IStrategy & hasLen) const
{
    StartEnd converted;
    const unsigned len = hasLen.Len();
    const TradeUtilThin tut;
    converted.start = tut.ConvertIndex(start, len);
    converted.end   = tut.ConvertIndex(end  , len);
    
    if (converted.end < 0)
    {
        throw EnjoLib::ExceptRuntimeError("StartEnd::ConvertIndexes(): negative end = " + EnjoLib::CharManipulations().ToStr(converted.end)
                                  + " len = " + EnjoLib::CharManipulations().ToStr(len) + " " + ToStr());
    }
    
    if (converted.start < 0)
    {
        throw EnjoLib::ExceptRuntimeError("StartEnd::ConvertIndexes(): negative start = " + EnjoLib::CharManipulations().ToStr(converted.start)
                                  + " len = " + EnjoLib::CharManipulations().ToStr(len) + " " + ToStr());
    }

    return converted;
}
