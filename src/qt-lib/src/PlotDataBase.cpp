#include "pch_qt.h"

#include "PlotDataBase.h"
#include "Util.h"
#include <IDataProvider.h>


using namespace std;

PlotDataBase::PlotDataBase(const IDataProvider & period)
: isHideWeekendData(true)
//: isHideWeekendData(false)
, everyNth(10)
, m_period(period)
{}

PlotDataBase::~PlotDataBase(){}

int PlotDataBase::CalcIdx(int i) const
{
    return Util::CalcIdx(i, GetSz());
}

QVector<double> PlotDataBase::GetBuf(const BufferType & type) const
{
    return Util::BufferToQVectF(m_period.GetBuf(type));
}

void PlotDataBase::InitVec(double val, QVector<double> & vec)
{
   vec = QVector<double>(GetSz(), val);
}

void PlotDataBase::InitVec(QVector<double> & vec, double val)
{
    InitVec(val, vec);
}
