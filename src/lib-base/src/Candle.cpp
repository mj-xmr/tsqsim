#include "Candle.h"
#include "Tick.h"
#include "State.h"
#include "PriceType.h"

#include <Template/AlgoVariadic.hpp>
#include <Template/AlgoSTDThin.hpp>
#include <Math/GeneralMath.hpp>
#include <Util/Except.hpp>
#include <Ios/Osstream.hpp>
#include <Ios/IoManip.hpp>

using namespace std;
using namespace EnjoLib;

Candle::Candle(){}
Candle::Candle(const PriceData & price)
: price(price)
{
    
}
Candle::Candle(float open, float close, float hi, float lo)
: price(open, close, hi, lo)
{}
Candle::~Candle(){}

void Candle::UpdateHighLow( const Tick & tick )
{
    if (price.hi == 0 || price.lo == 0)
    {
        price.open = tick.open;
        price.hi = tick.hi;
        price.lo = tick.lo;
    }
    else
    {
        price.hi = AlgoSTDThin().Max(price.hi, tick.hi);
        price.lo = AlgoSTDThin().Min(price.lo, tick.lo);
    }
}
void Candle::MakePinbar( const Tick & tick )
{
    price.open = tick.open;
}

void Candle::SetOpen( float o )
{
    price.open = o;
}
void Candle::SetClose( float c )
{
    price.close = c;
}
void Candle::SetOpen( const Tick & tick )
{
    price.open = tick.open;
    YYYYMMDDhhmmssOpen = tick.YYYYMMDDhhmmss();
}
void Candle::SetClose( const Tick & tick )
{
    price.close = tick.close;
    YYYYMMDDhhmmss = tick.YYYYMMDDhhmmss();
    year = tick.year;
    month = tick.month;
    day = tick.day;
    hour = tick.hour;
    minute = tick.minute;
    second = 0;
    vol = tick.vol;
}
void Candle::SetHigh( float c )
{
    price.hi = c;
}
void Candle::SetLow( float c )
{
    price.lo = c;
}
float Candle::GetExtr(const State & st) const
{
    return st.bullish ? price.lo : price.hi;
}
float Candle::GetExtrBody(const State & st) const
{
    return st.bullish ? GetBodyMin() : GetBodyMax();
}
float Candle::GetLen() const
{
    return price.hi-price.lo;
}

float Candle::GetBodyMin() const
{
    //const float val = AlgoSTDThin().Min(price.open, price.close);
    const float val = EL_MIN(price.open, price.close);
    return val;
}
float Candle::GetBodyMax() const
{
    //const float val = AlgoSTDThin().Max(price.open, price.close);
    const float val = EL_MAX(price.open, price.close);
    return val;
}

float Candle::GetWickHi() const
{
    const float val = EnjoLib::GeneralMath().Fabs(GetHigh() - GetBodyMax());
    return val;
}

float Candle::GetWickLo() const
{
    const float val = EnjoLib::GeneralMath().Fabs(GetLow()  - GetBodyMin());
    return val;
}

EnjoLib::Str Candle::GetDateStr() const
{
    EnjoLib::Osstream oss;
    oss << Iom::SetFill(oss, '0');
    oss << year << "_" << Iom::SetW(oss, 2) << month << "_" << Iom::SetW(oss, 2) << day << "__";
    oss << Iom::SetW(oss, 2) << hour << ":" << Iom::SetW(oss, 2) << minute;
    return oss.str();
}
EnjoLib::Str Candle::GetDateStrR() const
{
    EnjoLib::Osstream oss;
    oss << Iom::SetFill(oss, '0');
    oss << year << "-" << Iom::SetW(oss, 2) << month << "-" << Iom::SetW(oss, 2) << day << " ";
    oss << Iom::SetW(oss, 2) << hour << ":" << Iom::SetW(oss, 2) << minute;
    return oss.str();
}

Tick Candle::ToTick() const
{
    Tick t;
    t.close = price.close;

    t.open = price.open;
    t.hi = price.hi;
    t.lo = price.lo;
    //t.YYYYMMDDhhmmss = YYYYMMDDhhmmss;
    t.year = year;
    t.month = month;
    t.day = day;
    t.hour = hour;
    t.minute = minute;
    t.vol = vol;

    return t;
}

bool Candle::IsDataValid() const
{
    return price.open && price.close && price.hi && price.lo;
}

bool Candle::IsDataUnchanging() const
{
    return EnjoLib::AlgoVariadic().AllEqual(price.open, price.close,price. hi, price.lo);
}


EnjoLib::Str Candle::ToStringTick(const EnjoLib::Str & symbolName) const
{
    const char d = ',';
    ///GBPUSD,20150630,080000,1.57044,1.57576,1.57014,1.57568,0

    EnjoLib::Osstream oss;
    oss << Iom::SetFill(oss, '0');
    oss << symbolName << d << year << Iom::SetW(oss, 2) << month << Iom::SetW(oss, 2) << day << d << Iom::SetW(oss, 2) << hour << Iom::SetW(oss, 2) << minute << "00" << d;
    oss << price.open << d << price.hi << d << price.lo << d << price.close << d << vol;
    return oss.str();
}

EnjoLib::Str Candle::PrintOCHL() const
{
    EnjoLib::Osstream oss;
    oss << "(" << price.open << ", " << price.close << ", " << price.hi << ", " << price.lo << ");";
    return oss.str();
}

EnjoLib::Str Candle::PrintOHLC() const
{
    EnjoLib::Osstream oss;
    oss << "(" << price.open << ", " << price.hi << ", " << price.lo << ", " << price.close << ");";
    return oss.str();
}

Direction Candle::GetDir() const
{
    return Direction(price.close > price.open);
}
bool Candle::IsInDir(Direction bullish) const
{
    if (price.close == price.open)
        return true;
    return GetDir() == bullish;
}

bool Candle::IsNeutral() const
{
    return price.close == price.open;
}

float Candle::GetTypical() const
{
    const float typical = (GetHigh() + GetLow() + GetClose()) / float(3);
    return typical;
}

float Candle::GetWeightedClose() const
{
    const float weighted = (GetHigh() + GetLow() + 2 * GetClose()) / float(4);
    return weighted;
}

float Candle::GetPriceByType(const PriceType & type) const
{
    switch(type)
    {
    case PriceType::CLOSE:
        return GetClose();
    case PriceType::HIGH:
        return GetHigh();
    case PriceType::LOW:
        return GetLow();
    case PriceType::OPEN:
        return GetOpen();
    case PriceType::WEIGHTED_CLOSE:
        return GetWeightedClose();
    case PriceType::TYPICAL:
        return GetTypical();
    }

    throw EnjoLib::ExceptRuntimeError("Candle::GetPriceByType(): unimplemented type");
}
