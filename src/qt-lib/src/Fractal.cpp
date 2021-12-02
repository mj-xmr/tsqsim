#include "pch_qt.h"
#include "Fractal.h"
#include "Util.h"

const int Fractal::m_numBars = 100;

Fractal::Fractal(const QVector<double> & time, int idx, int numBars, double value, bool broken, bool touched)
: m_broken(broken)
, m_touched(touched)
, m_value(value)
{
    double t = 0;
    for (int i = idx; i - idx < numBars && i < time.size(); ++i)
    //for (int i = idx; i - idx < m_numBars && i < time.size(); ++i)
    {
        const int offset = -1; /// TODO
        t = time[i + offset];
        if (i == idx)
        {
            m_time.push_back(t);
            m_data.push_back(value);
        }
    }
    m_time.push_back(t);
    m_data.push_back(value);
}

Fractal::~Fractal()
{
    //dtor
}

const QVector<double> & Fractal::GetData() const
{
    return m_data;
}
const QVector<double> & Fractal::GetTime() const
{
    return m_time;
}
