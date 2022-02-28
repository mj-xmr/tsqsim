#ifndef PLOTDATASCREENSHOT_H
#define PLOTDATASCREENSHOT_H

#include "PlotDataBase.h"

#include <Template/Array.hpp>

#include <QtCore/QVector>

class Candle;
class IPeriod;

class PlotDataScreenshot : public PlotDataBase
{
    public:
        PlotDataScreenshot(const IPeriod & period);
        virtual ~PlotDataScreenshot();

        double GetRelative0() const override {return 0;};
        const EnjoLib::Array<QCPFinancialData> & GetFinancial() const override { return financial; };
        const QVector<QString> & GetDatesStr() const override { return datesStr; };
        const QVector<double> & GetTicks() const override { return ticks; };
        const QVector<double> & GetTime() const override { return time; };
        const QVector<double> & GetTimeOrig() const override { return timeOrig; };

    protected:
    private:

        EnjoLib::Array<QCPFinancialData> financial;
        QVector<QString> datesStr;
        QVector<double> ticks;

        QVector<double> time, timeOrig;
        //QVector<double> maFast;
        //QVector<double> maSlow;
};

#endif // PLOTDATASCREENSHOT_H
