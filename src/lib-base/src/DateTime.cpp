#include "DateTime.h"
#include <Ios/Osstream.hpp>
#include <Util/Str.hpp>
#include <Ios/Isstream.hpp>

#include <STD/String.hpp>

using namespace std;

DateTime::DateTime(DateInt date)
: m_date(date)
{}

DateTime::~DateTime()
{}

int DateTime::ShiftExtract2(DateInt date, uint64_t divisor) const
{
    uint64_t yearMonth = date / divisor;
    EnjoLib::Osstream oss;
    oss << yearMonth;
    EnjoLib::Str yearMonthStr = oss.str();
    EnjoLib::Str monthStr = yearMonthStr.str().erase(0, yearMonthStr.size() - 2);
    EnjoLib::Isstream iss;
    iss.str(monthStr);
    int month;
    iss >> month;
    return month;
}

int DateTime::GetYear() const
{
    int year = m_date / 10000000000;
    return year;
}

int DateTime::GetMonth() const
{
    int ret = ShiftExtract2(m_date, 100000000);
    return ret;
}

int DateTime::GetDay() const
{
    int ret = ShiftExtract2(m_date, 1000000);
    return ret;
}

int DateTime::GetHour() const
{
    int ret = ShiftExtract2(m_date, 10000);
    return ret;
}

int DateTime::GetMinute() const
{
    int ret = ShiftExtract2(m_date, 100);
    return ret;
}

int DateTime::GetSecond() const
{
    int ret = ShiftExtract2(m_date, 1);
    return ret;
}

DateInt DateTime::GetDateOnly(bool addTrailingZeroes) const
{
    DateInt dateShifted = 0;

    EnjoLib::Osstream oss;
    oss << m_date;
    EnjoLib::Str date = oss.str();
    EnjoLib::Str dateOnly = date.str().erase(date.size() - 6, 6);
    if (addTrailingZeroes)
        dateOnly += "000000";
    EnjoLib::Isstream iss;
    iss.str(dateOnly.str());
    iss >> dateShifted;
    return dateShifted;
}

int DateTime::GetTimeOnly() const
{
    int time = 0;

    EnjoLib::Osstream oss;
    oss << m_date;
    EnjoLib::Str date = oss.str();
    EnjoLib::Str timeOnly = date.str().erase(0, 8);
    EnjoLib::Isstream iss;
    iss.str(timeOnly.str());
    iss >> time;
    return time;
}
