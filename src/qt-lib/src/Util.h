#ifndef UTIL_H
#define UTIL_H

#include "typesVec.h"
#include <Util/VecF.hpp>
#include <Template/ArrayFwd.hpp>
#include <QVector>
#include <QDate>
#include <QTime>
#include <qcustomplot.h>
#include <types.h>
#include <Buffer.h>

class ISymbol;
class IPeriod;
class Candle;
class DateTime;
class PlotDataBase;
class IHasDateComponents;
class PlotDataBase;
class BufferType;
class XY;
class BufferUpdateable;
class BufferVecUpdateable;

class Util
{
    public:
        Util(){}
        virtual ~Util(){}

        template<class T, class N>
        static QVector<T> stdVectToQVect( const std::vector<N> & in );
        static QVector<double> stdVectToQVectF( const std::vector<float> & in );
        static QVector<double> stdVectToQVectF( const std::vector<double> & in );
        static QVector<double> BufferToQVectF( Buffer in );
        template <class T>
        static QVector<T> ExtractEveryNth(const QVector<T> & in, int everyNth);
        static QDate ToQDate(const IHasDateComponents & dt);
        static QTime ToQTime(const IHasDateComponents & dt);
        static QDateTime ToQDateTime(const IHasDateComponents & dt);
        static QDateTime ToQDateTime(DateInt dt);
        static double ToSeconds(QDateTime qdt);
        static double ToNoWeekendSeconds(double time0, int arrayIdx, const IPeriod & period);
        static QCPFinancialData CandleToQCPFinancialData(const Candle & candle);
        static std::vector<QCPFinancialData> CandlesToQCPFinancialData(const IterCan & candles);
        static int CalcIdx(int i, int n);

        static QCPGraph * AddMA(QCustomPlot *customPlot, const PlotDataBase & d, const BufferType & bt, const QColor & color);
        static QCPGraph * AddMA(const QVector<double> & time, const QVector<double> & ma, QCustomPlot *customPlot, const QColor & color);
        //static std::vector<QCPGraph *> AddMAVec(QCustomPlot *customPlot, const PlotDataBase & d, const std::vector<const BufferUpdateable *> & bufs);
        static std::vector<QCPGraph *> AddMAVec(QCustomPlot *p, const PlotDataBase & d, const EnjoLib::Array<EnjoLib::VecF> & bufs);
        static QCPItemLine * AddVLine(double x, double y1, double y2, QCustomPlot *customPlot, const QColor & color);
        static QCPGraph * AddVLineTech(double x, QCustomPlot *customPlot, QCPAxisRect *techRect, const QColor & color);
        static QVector<QCPItemLine *> AddVLines(const QVector<double> & x, double y1, double y2, QCustomPlot *customPlot, const QColor & color);
        static QVector<QCPGraph *> AddVLinesTech(const QVector<double> & x, QCustomPlot *customPlot, QCPAxisRect *techRect, const QColor & color);
        static QCPItemLine * AddLine(const QVector<double> & time, const QVector<double> & data, QCustomPlot *customPlot, const QColor & color);
        static QCPItemLine * AddLine(QCustomPlot *p, const QVector<double> & timeRev, int idxPrev, float valPrev, int idxCurr, float valCurr, bool isPredicting, const char * colPast, const char * colFuture, int penWidth = 1);
        static std::vector<QCPAbstractItem *> AddCurve(QCustomPlot *p, const QVector<double> & timeRev, const EnjoLib::Array<XY> & data, int predictAhead, const char * colPast, const char * colFuture, bool straightLine = false, int penWidth = 1);
        static QCPItemText * AddText(QCustomPlot *p, const EnjoLib::Str & str);
        static QCPItemText * AddTextCoords(QCustomPlot *p, const EnjoLib::Str & str, const QPointF & coords);
        static QCPItemText * AddTextQ(QCustomPlot *p, const QString & str);
        static QVector<QString> DatesToStr(const QVector<double> & dates);
        static QString DateToStr(double date);
        static EnjoLib::Str QStringToStdString(const QString & str);
        static EnjoLib::Str DateToDateIntStr(double date);
        static QString NumToStr(double num, int digits);
        static QString FormatSymPer(const ISymbol & sym, EnjoLib::Str periodName);
        static QString FormatSymPer(EnjoLib::Str symName, EnjoLib::Str periodName);
        static EnjoLib::Str GetIndexes(const PlotDataBase & d, int i, bool lineBreak = false);


    protected:
    private:
};


#endif // UTIL_H
