#include "DateParser.h"
#include <cstdio>
#include <Util/Except.hpp>

DateParser::DateParser()
{
    day = month = year = 0;
}

DateParser::~DateParser()
{
    //dtor
}

void DateParser::Parse(const EnjoLib::Str & dateStr)
{
    if (sscanf(dateStr.c_str(), "%4d%2d%2d", &year, &month, &day) <= 0)
        throw EnjoLib::ExceptInvalidArg("Wrong date format: " + dateStr);

}
