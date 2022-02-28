#ifndef TXTSMALLBASE_H
#define TXTSMALLBASE_H

#include <Direction.h>
class QCustomPlot;
class IDataProvider;
class IStrategy;
class ISignal;
class PlotDataBase;
class State;

class TxtSmallBase
{
    public:
        TxtSmallBase();
        virtual ~TxtSmallBase();


        virtual void SignalScore(QCustomPlot *customPlot, const IDataProvider & period, const IStrategy & strategy, Direction dir, const PlotDataBase & d) const = 0;
        virtual void SpecialSignalText(QCustomPlot *customPlot, const IDataProvider & period, const IStrategy & strategy, const PlotDataBase & d) const = 0;
        virtual void SpecialSignalPred(QCustomPlot *customPlot, const IDataProvider & period, const IStrategy & strategy, Direction dir, const PlotDataBase & d) const = 0;
        virtual void Fractals(QCustomPlot *customPlot, const IDataProvider & period, const PlotDataBase & d) const = 0;
        virtual void Pinbars(QCustomPlot *customPlot, const IDataProvider & period, const IStrategy & strat, const PlotDataBase & d) const = 0;

    protected:

    private:
};

#endif // TXTSMALLBASE_H
