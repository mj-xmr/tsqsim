#include "SRFinal.h"
#include "TradeUtilThin.h"

SRFinal::SRFinal(float level, Direction dir, bool broken, bool touched, int iStart, int iEnd)
: m_level(level)
, m_dir(dir)
, m_broken(broken)
, m_touched(touched)
, m_iStart(iStart)
, m_iEnd(iEnd)
, m_id(TradeUtilThin().GetIdFromPrice(level))
{}

SRFinal::~SRFinal(){}

void SRFinal::AdvanceIndex()
{
    ++m_iStart;
    if (m_iEnd > 0) // <= 0 is special meaning
        ++m_iEnd;
}
