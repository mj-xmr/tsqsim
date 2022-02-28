#ifndef TXTSIMULATORBASE_H
#define TXTSIMULATORBASE_H

class QCustomPlot;
class IPeriod;
class IStrategy;
class PlotDataBase;
class ISimulatorStd;

class TxtSimulatorBase
{
    public:
        TxtSimulatorBase();
        virtual ~TxtSimulatorBase();

        virtual void Txt(QCustomPlot *customPlot, const IPeriod & period, const IStrategy & strategy, const PlotDataBase & d) const = 0;

    protected:

    private:
};

#endif // TXTSIMULATORBASE_H
