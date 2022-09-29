#include "Tick.h"
//#include "DateTime.h"
#include "Candle.h"
#include <Util/CharManipulations.hpp>
#include <Math/GeneralMath.hpp>
#include <Util/Except.hpp>
#include <cstdio>

#include <Ios/Osstream.hpp>
#include <Ios/Isstream.hpp>

using namespace std;
using namespace EnjoLib;

Tick::~Tick(){}
Tick::Tick(){}

Tick::Tick(const Str & line)
{
    ParseFromStream(line);
    return;

    CharManipulations cm;
    const int sz = 256;
    char symbol[sz], dateStr[sz], timeStr[sz];
    if (sscanf(line.c_str(), "%6s,%8s,%6s,%f,%f,%f,%f,%d",
           symbol, dateStr, timeStr, &open, &hi, &lo, &close, &vol) <= 0)
    {
        //throw EnjoLib::ExceptInvalidArg("Wrong line format: " + line);
        ParseFromStream(line);
        return;
    }

    short monthLoc, dayLoc, hourLoc, minuteLoc;
    if (sscanf(dateStr, "%4hd%2hd%2hd", &year, &monthLoc, &dayLoc) <= 0)
    {
        //throw EnjoLib::ExceptInvalidArg("Wrong date format: " + string(dateStr));
        ParseFromStream(line);
        return;
    }

    if (sscanf(timeStr, "%2hd%2hd", &hourLoc, &minuteLoc) <= 0)
    {
        //throw EnjoLib::ExceptInvalidArg("Wrong time format: " + string(timeStr));
        ParseFromStream(line);
        return;
    }

    month = monthLoc;
    day = dayLoc;
    hour = hourLoc;
    minute = minuteLoc;
    //YYYYMMDDhhmmss = cm.ToNumber<DateInt>(string(dateStr) + timeStr);
//    YYYYMMDDhhmmss = cm.ToNumber<DateInt>(string(dateStr) + timeStr);
    //cout << YYYYMMDDhhmmss << endl;
}

void Tick::ParseFromStream(const EnjoLib::Str & line)
{
    CharManipulations cm;
    // Fall back to less restrictive, yet slower C++ parsing
    const EnjoLib::Str & lineNoSpaces = cm.Replace(line, ",", " ");
    EnjoLib::Isstream ss(lineNoSpaces);
    EnjoLib::Str symbolStr, dateStr, timeStr;
    if (!(ss >> symbolStr >> dateStr >> timeStr >> open >> hi >> lo >> close >> vol))
    {
        throw EnjoLib::ExceptInvalidArg("Problem with parsing line = " + ss.str());
    }

    short monthLoc, dayLoc, hourLoc, minuteLoc;
    if (sscanf(dateStr.c_str(), "%4hd%2hd%2hd", &year, &monthLoc, &dayLoc) <= 0)
        throw EnjoLib::ExceptInvalidArg("Wrong date format: " + EnjoLib::Str(dateStr));
    if (sscanf(timeStr.c_str(), "%2hd%2hd", &hourLoc, &minuteLoc) <= 0)
        throw EnjoLib::ExceptInvalidArg("Wrong time format: " + EnjoLib::Str(timeStr));
    month = monthLoc;
    day = dayLoc;
    hour = hourLoc;
    minute = minuteLoc;
    //YYYYMMDDhhmmss = cm.ToNumber<DateInt>(dateStr + timeStr);
}

int Tick::GetDayMinute() const
{
    const int monthMinutes = 0; /// Probably needed?
    const int dayMinutes = day * 24 * 60;
    const int hourMinutes = hour * 60;
    int totalMinutes = monthMinutes + dayMinutes + hourMinutes + minute;
    if (totalMinutes == 0)
        totalMinutes = 24 * 60; // A daily bar
    return totalMinutes;
}

Candle Tick::ToCandle() const
{
    Candle can;
    can.UpdateHighLow(*this);
    can.SetClose(*this);
    can.SetOpen(*this);
    return can;
}

bool Tick::IsValid() const
{
    return (open + close) != 0;
}

uint64_t Tick::YYYYMMDDhhmmss() const
{
    const GeneralMath gmat;
    uint64_t date = 0;
    const uint8_t second = 0;
    const int leading0 = 1;
    date = gmat.Concatenate(date, year);
    date = gmat.Concatenate(date, month, leading0);
    date = gmat.Concatenate(date, day, leading0);
    date = gmat.Concatenate(date, hour, leading0);
    date = gmat.Concatenate(date, minute, leading0);
    date = gmat.Concatenate(date, second, leading0);
    //cout << date << endl;
    return date;
}
/*
float Tick::GetOpen() const
{
    return open;
}
float Tick::GetClose() const
{
    return close;
}
float Tick::GetHigh() const
{
    return hi;
}
float Tick::GetLow() const
{
    return lo;
}

int Tick::GetYear() const
{
    return year;
}

int Tick::GetMonth() const
{
    return month;
}

int Tick::GetDay() const
{
    return day;
}

int Tick::GetHour() const
{
    return hour;
}

int Tick::GetMinute() const
{
    return minute;
}
*/
