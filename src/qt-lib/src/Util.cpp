#include "pch_qt.h"

#include "Util.h"
#include "PlotDataBase.h"

#include <Candle.h>
#include <ISymbol.h>
#include <IPeriod.h>
#include <DateTime.h>
#include <XY.h>
#include <ConfigQTPlot.h>
#include <IHasDateComponents.h>
#include <BufferUpdateable.h>
#include <BufferVecUpdateable.h>

#include <Math/GeneralMath.hpp>
#include <Util/StrColour.hpp>
#include <Util/Except.hpp>

#include <Ios/Osstream.hpp>


using namespace std;
using namespace EnjoLib;

QDate Util::ToQDate(const IHasDateComponents & dt)
{
    int y = dt.GetYear();
    int m = dt.GetMonth();
    int d = dt.GetDay();
    QDate ret(y,m,d);
    return ret;
}

QTime Util::ToQTime(const IHasDateComponents & dt)
{
    int h = dt.GetHour();
    int m = dt.GetMinute();
    QTime ret(h,m);
    return ret;
}

QDateTime Util::ToQDateTime(const IHasDateComponents & dt)
{
    return QDateTime(ToQDate(dt),ToQTime(dt));
}

QDateTime Util::ToQDateTime(DateInt di)
{
    DateTime dt(di);
    return ToQDateTime(dt);
}

double Util::ToSeconds(QDateTime qdt)
{
    //qdt.setTimeSpec(Qt::UTC);
    double sec = qdt.toTime_t();
    return sec;
}

double Util::ToNoWeekendSeconds(double time0, int arrayIdx, const IPeriod & period)
{
    double noWeekendSec = time0 + arrayIdx * period.GetNumSeconds();
    return noWeekendSec;
}

QCPFinancialData Util::CandleToQCPFinancialData(const Candle & candle)
{
    QCPFinancialData ret;
    ret.close = candle.GetClose();
    ret.open = candle.GetOpen();
    ret.high = candle.GetHigh();
    ret.low = candle.GetLow();

    QDateTime qdateTime = ToQDateTime(candle);
    //qdateTime.setTimeSpec(Qt::UTC);
    double timeSec = qdateTime.toTime_t();
    ret.key = timeSec;
    return ret;
}

std::vector<QCPFinancialData> Util::CandlesToQCPFinancialData(const IterCan & candles)
{
    std::vector<QCPFinancialData> ret(candles.size());
    for (unsigned i = 0; i < candles.size(); ++i)
        ret[i] = CandleToQCPFinancialData(candles[i]);
    return ret;
}

/*
std::vector<QCPGraph *> Util::AddMAVec(QCustomPlot *p, const PlotDataBase & d, const std::vector<const BufferUpdateable *> & bufs)
{
    std::vector<QCPGraph *> ret;
    for (unsigned i = 0; i < bufs.size(); ++i)
    {
        const BufferUpdateable * buf = bufs.at(i);
        const float x = (i) / float(bufs.size());
        QCPGraph * graph = AddMA(d.GetTime(), stdVectToQVectF(buf->GetBuf().GetData()), p, QColor::fromHslF(x, 0.95, 0.5));
        ret.push_back(graph);
    }
    return ret;
}
*/

std::vector<QCPGraph *> Util::AddMAVec(QCustomPlot *p, const PlotDataBase & d, const EnjoLib::Array<VecF> & bufs)
{
    std::vector<QCPGraph *> ret;
    for (unsigned i = 0; i < bufs.size(); ++i)
    {
        const VecF & data = bufs.at(i);
        const float x = (i) / float(bufs.size());
        QCPGraph * graph = AddMA(d.GetTime(), stdVectToQVectF(data.Data()), p, QColor::fromHslF(x, 0.95, 0.5));
        ret.push_back(graph);
    }
    return ret;
}

QCPGraph * Util::AddMA(QCustomPlot *customPlot, const PlotDataBase & d, const BufferType & bt, const QColor & color)
{
    return AddMA(d.GetTime(), d.GetBuf(bt), customPlot, color);
}

QCPGraph * Util::AddMA(const QVector<double> & time, const QVector<double> & ma, QCustomPlot *customPlot, const QColor & color)
{
    QCPGraph * maGraph = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
    //maGraph->setUseFastVectors(true);
    maGraph->setData(time, ma);
    //maGraph->removeData(time[time.size()-1]); // Why was this done here? If really purged the last data point.
    maGraph->setPen(QPen(color));
    customPlot->setAutoAddPlottableToLegend(false);
    customPlot->addPlottable(maGraph);
    return maGraph;
}

QCPItemLine * Util::AddVLine(double x, double y1, double y2, QCustomPlot *customPlot, const QColor & color)
{
    QCPItemLine * line = new QCPItemLine(customPlot);
    line->start->setCoords(x, y1);
    line->end->setCoords(x, y2);
    line->setPen(QPen(color));
    customPlot->addItem(line);
    return line;
}

QVector<QCPItemLine *> Util::AddVLines(const QVector<double> & xx, double y1, double y2, QCustomPlot *p, const QColor & color)
{
    QVector<QCPItemLine *> ret;
    for (double x : xx)
    {
        ret += Util::AddVLine(x, y1, y2, p, color);
    }
    return ret;
}

QCPItemLine * Util::AddLine(const QVector<double> & time, const QVector<double> & data, QCustomPlot *customPlot, const QColor & color)
{
    if (time.empty() || data.empty())
        return NULL;
    QCPItemLine * line = new QCPItemLine(customPlot);
    line->start->setCoords(time.front(), data.front());
    line->end->setCoords(time.back(), data.back());
    line->setPen(QPen(color));
    customPlot->addItem(line);
    return line;
}

QCPItemLine * Util::AddLine(QCustomPlot *p, const QVector<double> & timeRev, int idxPrev, float valPrev, int idxCurr, float valCurr, bool isPredicting, const char * colPast, const char * colFuture, int penWidth)
{
    QCPItemLine * line = new QCPItemLine(p);
    line->start->setCoords(timeRev[idxCurr], valCurr);
    line->end->setCoords(timeRev[idxPrev], valPrev);
    QPen pen(isPredicting ? colFuture : colPast);
    pen.setWidth(penWidth);
    line->setPen(pen);
    p->addItem(line);
    return line;
}

QCPItemText * Util::AddText(QCustomPlot *p, const EnjoLib::Str & str)
{
    ConfigQTPlot confPlot;
    confPlot.Read();

    QCPItemText * txtItem = new QCPItemText(p);
    if (confPlot.DARK)
    {
        txtItem->setColor(QColor(200, 200, 200));
    }
    txtItem->setText(str.c_str());
    p->addItem(txtItem);
    return txtItem;
}

QCPItemText * Util::AddTextQ(QCustomPlot *p, const QString & str)
{
    return AddText(p, QStringToStdString(str));
}

QCPItemText * Util::AddTextCoords(QCustomPlot *p, const EnjoLib::Str & str, const QPointF & coords)
{
    QCPItemText * txtItem = AddText(p, str);
    txtItem->position->setCoords(coords);
    //txtItem->setColor("Blue");
    return txtItem;
}

std::vector<QCPAbstractItem *> Util::AddCurve(QCustomPlot *p, const QVector<double> & timeRev, const Array<XY> & data, int predictAhead, const char * colPast, const char * colFuture, bool straightLine, int penWidth)
{
    const int sz = data.size();
    std::vector<QCPAbstractItem *> ret;
    if (straightLine)
    {
        ret.push_back(Util::AddLine(p, timeRev, data.at(0).x, data.at(0).y, data.at(sz-predictAhead).x, data.at(sz-predictAhead).y, false, colPast, colFuture));
        ret.push_back(Util::AddLine(p, timeRev, data.at(sz-predictAhead).x, data.at(sz-predictAhead).y, data.at(sz-1).x, data.at(sz-1).y, true, colPast, colFuture));
    }
    else
    {

        for (int i = 1; i < sz; ++i)
        {
            bool isPredicting = i > sz - predictAhead;
            int idxPrev = data.at(i-1).x;
            int idxCurr = data.at(i).x;
            ret.push_back(Util::AddLine(p, timeRev, idxPrev, data.at(i-1).y, idxCurr, data.at(i).y, isPredicting, colPast, colFuture));
        }
    }

    return ret;
}

QVector<QString> Util::DatesToStr(const QVector<double> & dates)
{
    QVector<QString> ret;
    for (int i = 0; i < dates.size(); i++)
    {
        QDateTime timestamp;
        timestamp.setTime_t(dates[i]);
        //ret.push_back(timestamp.toString(Qt::SystemLocaleShortDate));
        //ret.push_back(timestamp.toString("dd. MMM"));
        ret.push_back(timestamp.toString("yyyy-MM-dd hh"));

    }
    return ret;
}

QString Util::DateToStr(double date)
{
    QDateTime timestamp;
    timestamp.setTime_t(date);
    //return timestamp.toString("dd. MMM");
    return timestamp.toString("yyyy-MM-dd hh:mm");
}

EnjoLib::Str Util::DateToDateIntStr(double date)
{
    QDateTime timestamp;
    timestamp.setTime_t(date);
    return QStringToStdString(timestamp.toString("yyyyMMddhhmmss"));
}

EnjoLib::Str Util::QStringToStdString(const QString & str)
{
    return str.toUtf8().constData();
}

int Util::CalcIdx(int i, int n)
{
    const int idx = n - i - 1;
    return idx;
}

//template QVector<double> Util::stdVectToQVect<double, float>(const EnjoLib::VecF & in);
template<class T, class N>
QVector<T> Util::stdVectToQVect( const std::vector<N> & in )
{
    QVector<T> ret(in.size());
    for (unsigned i = 0; i < in.size(); ++i)
        ret[i] = in[i];
    return ret;
}

QVector<double> Util::stdVectToQVectF( const std::vector<float> & in )
{
    return Util::stdVectToQVect<double, float>(in);
}

QVector<double> Util::stdVectToQVectF( const std::vector<double> & in )
{
    return Util::stdVectToQVect<double, double>(in);
}

QVector<double> Util::BufferToQVectF( Buffer in )
{
    return Util::stdVectToQVectF(in.GetData().Data());
}

template QVector<QString> Util::ExtractEveryNth<QString>(const QVector<QString> & in, int everyNth);
template QVector<double>  Util::ExtractEveryNth<double> (const QVector<double>  & in, int everyNth);
template <class T>
QVector<T> Util::ExtractEveryNth(const QVector<T> & in, int everyNth)
{
    QVector<T> ret;
    for (int i = 0; i < in.size(); i++)
    {
        if (i % everyNth != 0)
            continue;
        ret.push_back(in[i]);

    }
    return ret;
}

QString Util::NumToStr(double num, int digits)
{
    EnjoLib::GeneralMath gm;
    double muldiv = pow(10, digits);
    return QString::number(gm.round(num * muldiv) / muldiv);
}

QString Util::FormatSymPer(const ISymbol & sym, EnjoLib::Str periodName)
{
    return FormatSymPer(sym.GetName().str(), periodName);
}

QString Util::FormatSymPer(EnjoLib::Str symName, EnjoLib::Str periodName)
{
    return QString((symName + ", " + periodName).c_str());
}

EnjoLib::Str Util::GetIndexes(const PlotDataBase & d, int i, bool lineBreak)
{
    EnjoLib::Osstream oss;
    oss << "(" << i << (lineBreak ? "\n" : ", ") << "-" << d.GetSz() - i << ")";
    return oss.str();
}

void Util::HandleException(std::exception & ex)
{
    qDebug() << EnjoLib::StrColour::GenErr("\n\nEXCEPTION!\n").c_str();
    qDebug() << EnjoLib::StrColour::GenErr(ex.what()).c_str();
    QMessageBox msgBox;
    msgBox.setWindowTitle("EXCEPTION!");
    msgBox.setText(ex.what());
    msgBox.exec();
    throw EnjoLib::ExceptRuntimeError(ex.what());
}
