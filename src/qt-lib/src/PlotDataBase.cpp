#include "pch_qt.h"

#include "PlotDataBase.h"
#include "Util.h"
#include "ConfigMan.h"
#include "ConfigQTPlot.h"
#include <IDataProvider.h>


using namespace std;

PlotDataBase::PlotDataBase(const IDataProvider & period)
/// TODO: clearly wrong time ticks on the x axis, than when not hiding the weekend data
//: isHideWeekendData(not gcfgMan.cfgQTPlot->WEEKEND_DATA)
: isHideWeekendData(true)
//: isHideWeekendData(false)
, everyNth(10)
, m_period(period)
{}

#include "PlotDataScreenshot.h"
CorPtr<PlotDataBase> PlotDataBase::CreateScreenshot(const IPeriod & period)
{
    return CorPtr<PlotDataBase>(new PlotDataScreenshot(period));
}

PlotDataBase::~PlotDataBase(){}

int PlotDataBase::CalcIdx(int i) const
{
    return Util::CalcIdx(i, GetSz());
}

unsigned PlotDataBase::GetSz() const
{
     return GetFinancial().size();
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
