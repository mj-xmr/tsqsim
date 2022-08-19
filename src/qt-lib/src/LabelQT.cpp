#include "LabelQT.h"
#include <Ios/Osstream.hpp>
#include <Util/Str.hpp>
#include <IPeriod.h>

LabelQT::LabelQT(const IPeriod & period)
: m_period(period)
{}

LabelQT::~LabelQT()
{}

EnjoLib::Str LabelQT::ToString() const
{
    EnjoLib::Osstream oss;
    const char d = '|'; // deliminator
    oss << m_period.GetSymbolName() << d << m_period.GetName() << d << GetStart() << d << GetEnd();
    EnjoLib::Str id = oss.str();
    if (!IsValid())
        return "Invalid - " + id;
    return id;
}
