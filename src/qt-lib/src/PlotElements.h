#ifndef PLOTELEMENTS_H
#define PLOTELEMENTS_H

#include <Util/Pair.hpp>

class QCustomPlot;
class QCPAxisRect;
class PlotDataBase;
class ConfigQTPlot;
class IDataProvider;
class IStrategy;
class BufferType;
class IPeriod;
class ISimulatorTS;
enum class PredictorOutputType;

class PlotElements
{
    public:
        PlotElements(){}
        virtual ~PlotElements(){}

        QCPFinancial * SetupCandles(unsigned mi, QCustomPlot * p, const PlotDataBase & d, const ConfigQTPlot & confPlot, double binSize, bool dark);
        void ConfigureCandlesticks(QCPFinancial *candlesticks, bool dark);
        void SetupDayWeekend(unsigned mi, QCustomPlot * p, const IDataProvider & period, const PlotDataBase & d, bool dark);
        void SetupTechs(QCustomPlot * p, const IStrategy & strat, QCPAxisRect *techRect, const PlotDataBase & d);
        void SetupTechsXform(QCustomPlot * p, const IPeriod & per, QCPAxisRect *techRect, const PlotDataBase & d);
        QCPGraph * SetupTSLine(QCustomPlot * p, QCPAxisRect *techRect, const PlotDataBase & d, const ISimulatorTS & simTS, const PredictorOutputType & type, const QPen & pen, const char * name);
        void SetupTechLine(QCustomPlot * p, const PlotDataBase & d, const QVector<double> & vec, QCPGraph *newCurve);
        QCPAxisRect * SetupGetIndicatorRect(QCustomPlot * p, const PlotDataBase & d);
        void HandleWeekendData(QCPAxis * axis, const PlotDataBase & d, bool hide);
        template<class QCClass>
        void SetPenGrey(bool isDark, QCClass * item) const;
    protected:

    private:
        void SetupTechsVec(QCustomPlot * p, const IStrategy & strat, QCPAxisRect *techRect, const PlotDataBase & d, const std::vector<EnjoLib::Pair<BufferType, QPen>> & techs);
};


template<class QCClass>
void PlotElements::SetPenGrey(bool isDark, QCClass * item) const
{
    if (not isDark) return;
    item->setPen(QPen("Grey"));
}

#endif // PLOTELEMENTS_H
