#ifndef PLOTDATABASE_H
#define PLOTDATABASE_H

#include <Direction.h>
#include <Template/ArrayFwd.hpp>
#include <Template/CorradePointer.h>
#include <3rdParty/stdfwd.hh>

template <class T> class QVector;
class QString;
class IDataProvider;
class IPeriod;
class BufferType;
class QCPFinancialData;

class PlotDataBase
{
    public:
        PlotDataBase(const IDataProvider & period);
        virtual ~PlotDataBase();

        static CorPtr<PlotDataBase> CreateScreenshot(const IPeriod & period);

        unsigned GetSz() const;
        int CalcIdx(int i) const;


        bool isHideWeekendData;

        QVector<double> GetBuf(const BufferType & type) const;

        virtual double GetRelative0() const = 0;
        virtual const EnjoLib::Array<QCPFinancialData> & GetFinancial() const = 0;
        virtual const QVector<QString> & GetDatesStr() const = 0;
        virtual const QVector<double> & GetTicks() const = 0;
        virtual const QVector<double> & GetTime() const = 0;
        virtual const QVector<double> & GetTimeOrig() const = 0;

        int everyNth;

    protected:
        void InitVec(double val, QVector<double> & vec);
        void InitVec(QVector<double> & vec, double val);

        const IDataProvider & m_period;
    private:

};

#endif // PLOTDATABASE_H
