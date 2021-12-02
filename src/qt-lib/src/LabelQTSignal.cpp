#include "LabelQTSignal.h"
#include <Ios/Osstream.hpp>
#include <IPeriod.h>
#include <IStrategy.h>

LabelQTSignal::LabelQTSignal(const IPeriod & period, const IStrategy & strat, DateInt dt, Direction dir)
: LabelSignal(period, dt, dir)
, m_period(period)
, m_strat(strat)
{}
LabelQTSignal::~LabelQTSignal(){}

EnjoLib::Str LabelQTSignal::ToString() const
{
    EnjoLib::Osstream oss;
    const char d = '|'; // deliminator
    oss << m_strat.GetName() << d << m_period.GetSymbolName() << d << m_period.GetName() << d << GetDate() << d << IsBullish();
    EnjoLib::Str id = oss.str();
    if (!IsValid())
        return "Invalid - " + id;
    return id;
}
