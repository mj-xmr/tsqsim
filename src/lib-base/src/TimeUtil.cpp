#include "TimeUtil.h"

#include <Ios/Osstream.hpp>
#include <Util/CharManipulations.hpp>

#include <ostream>
#include <iomanip>
#include <chrono>
#include <ctime>

TimeUtil::TimeUtil(){}
TimeUtil::~TimeUtil(){}

int TimeUtil::GetCurrentHour() const
{
    return GetCurrentTimeComponent('H');
}

int TimeUtil::GetCurrentYear() const
{
    return GetCurrentTimeComponent('Y');
}

int TimeUtil::GetCurrentMonth() const
{
    return GetCurrentTimeComponent('m');
}

int TimeUtil::GetCurrentTimeComponent(const char fmt) const
{
    std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::tm ltime;
    localtime_r(&t, &ltime);
    EnjoLib::Osstream oss;
    const EnjoLib::Str fmtStr = EnjoLib::Str("%") + fmt;
    oss.OStr() << std::put_time(&ltime, fmtStr.c_str());
    return EnjoLib::CharManipulations().ToInt(oss.str());
}
