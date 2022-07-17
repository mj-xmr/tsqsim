#include "TimeUtil.h"

#include <Ios/Osstream.hpp>
#include <Util/CharManipulations.hpp>

#include <ostream>
#include <iomanip>
#include <chrono>
#include <ctime>

//#if defined(_MSC_VER)
//#   define localtime_r(T,Tm) (localtime_s(Tm,T) ? NULL : Tm)
//#endif

#ifdef WIN32
    #define LOCALTIME(time, localTime) localtime_s(localTime, time)
#else
    #define LOCALTIME(time, localTime) localtime_r(time, localTime)
#endif
    
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
    LOCALTIME(&t, &ltime);
    EnjoLib::Osstream oss;
    const EnjoLib::Str fmtStr = EnjoLib::Str("%") + fmt;
    oss.OStr() << std::put_time(&ltime, fmtStr.c_str());
    return EnjoLib::CharManipulations().ToInt(oss.str());
}
