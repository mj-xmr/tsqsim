#include "Label.h"
#include "TradeUtil.h"

Label::Label(){}
Label::~Label(){}
Label::Label(DateInt dstart, DateInt dend)
{
    SetStart(dstart);
    SetEnd(dend);
}


void Label::SetStart(DateInt dt)
{
    m_start = TradeUtil().DateZeroMinute(dt);
}
void Label::SetEnd(DateInt dt)
{
    m_end = TradeUtil().DateZeroMinute(dt);
}

bool Label::IsValid() const
{
    if (m_start >= m_end)
        return false;
    if (m_start == 0)
        return false;
    if (m_end == 0)
        return false;

    return true;
}

bool Label::operator < (const Label & other) const
{
    return m_start < other.m_start;
}
