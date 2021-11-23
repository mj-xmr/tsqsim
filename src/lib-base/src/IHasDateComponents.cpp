#include "IHasDateComponents.h"

#include <Ios/Osstream.hpp>
#include <Ios/IoManip.hpp>

using namespace std;
using namespace EnjoLib;

IHasDateComponents::IHasDateComponents()
{
    //ctor
}

IHasDateComponents::~IHasDateComponents()
{
    //dtor
}

EnjoLib::Str IHasDateComponents::GetISODateTime() const
{
    EnjoLib::Osstream oss;
    const char d = '-';
    const char t = ':';
    oss << Iom::SetFill(oss, '0');
    oss << GetYear() << d << Iom::SetW(oss, 2) << GetMonth() << d << Iom::SetW(oss, 2) << GetDay() << ' ';
    oss << Iom::SetW(oss, 2) << GetHour() << t << Iom::SetW(oss, 2) << GetMinute() << t << Iom::SetW(oss, 2) << GetSecond();
    return oss.str();
}
