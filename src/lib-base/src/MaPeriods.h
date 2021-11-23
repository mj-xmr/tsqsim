#ifndef MAPERIODS_H
#define MAPERIODS_H


struct MaPeriods
{
    MaPeriods(int maSlow = 10);
    bool IsMaUsedPeriodSlowMax() const;
    bool IsMaUserPeriodSlowErr() const;

    int m_maSlow;
    int m_maFast;
};

#endif // MAPERIODS_H
