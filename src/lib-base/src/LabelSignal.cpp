#include "LabelSignal.h"
#include "IDataProvider.h"
#include "TradeUtil.h"
#include <Util/Str.hpp>

LabelSignal::LabelSignal(){}
LabelSignal::LabelSignal(const IDataProvider & period, DateInt dt, Direction dir)
: m_date(dt)
, m_dir(dir)
, m_symbolPeriodId(period.GetSymbolPeriodId('_'))
{}
LabelSignal::~LabelSignal(){}


bool LabelSignal::IsValid() const
{
    if (m_date == 0)
        return false;

    return true;
}



EnjoLib::Str LabelSignal::GetId() const
{
    return TradeUtil().GetSymbolPeriodCandleIdUnified(m_symbolPeriodId, GetDate());
}

EnjoLib::Str LabelSignal::GetSymbolPeriodId() const {return m_symbolPeriodId; }
bool LabelSignal::operator < (const LabelSignal & other) const
{
    return m_date < other.m_date;
}
