#include "MaPeriods.h"
#include "MasConsts.h"
#include "AbstractsIndep.h"

MaPeriods::MaPeriods(int maSlow)
{
    const AbstractsIndep abstr;

    m_maSlow = maSlow;
    m_maFast = maSlow / 3;
    if (m_maFast < abstr.GetMaMin()) // abstr.GetMaMin()
        m_maFast = abstr.GetMaMin();
}

bool MaPeriods::IsMaUsedPeriodSlowMax() const
{
    const AbstractsIndep abstr;

    return m_maSlow == abstr.GetMaMax();
}

bool MaPeriods::IsMaUserPeriodSlowErr() const
{
    return m_maSlow == MasConsts::ERR_MA;
}
