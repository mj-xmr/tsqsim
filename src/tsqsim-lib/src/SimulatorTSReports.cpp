#include "SimulatorTSReports.h"
#include "URTWrap.h"
#include "GnuplotIOSWrap.h"
#include "StatsMedianSplit.h"
#include "ConfigTS.h"
#include "IDataProvider.h"
#include "Logic.h"

#include <Statistical/Statistical.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/ToolsMixed.hpp>

using namespace EnjoLib;

SimulatorTSReports::~SimulatorTSReports(){}
SimulatorTSReports::SimulatorTSReports()
{
    //ctor
}

EnjoLib::VecD SimulatorTSReports::PrepPredsPlot(const EnjoLib::VecD & orig, const EnjoLib::VecD & predBaseline, const EnjoLib::VecD & pred) const
{
    const VecD & diff = (predBaseline - orig) - (pred - orig); /// TODO: this could make more sense using squares?
    return Statistical().CumSum(diff);
}

void SimulatorTSReports::PrintReportSingleThreaded(const IDataProvider & per, const ConfigTS & cfgTS, const EnjoLib::VecD & data, const EnjoLib::Str & descr, const STDFWD::vector<const EnjoLib::VecD *> & plots) const
{
    const float scaleX = 1.00;
    const float scaleY = 0.6;
    const int numSplits = 3;
    const URTWrap urtWrap1, urtWrap2;
    const bool multithreaded = false;
    const StatsMedianSplit stats(multithreaded);


    ELO
    urtWrap2.Show(data);
    if (cfgTS.PLOT_SERIES)
    {
        GnuplotPlotTerminal1dSubplots(plots, descr, scaleX, scaleY);
    }
    stats.Stats(per.GetSymbolPeriodId(), data, numSplits);
    const double urtStat = urtWrap1.GetStatistic(data);
    LOG << "Stationarity score = " << urtStat << Nl;
}

bool SimulatorTSReports::VecEqual(const EnjoLib::VecD & data1, const EnjoLib::VecD & data2, double eps) const
{
    if (data1.size() != data2.size())
    {
        return false;
    }
    for (size_t i = 0; i < data1.size(); ++i)
    {
        if (data1.at(i) != data2.at(i))
        {
            VecD vec;
            vec.Add(data1.at(i));
            vec.Add(data2.at(i));
            const double mean = vec.Mean();
            if (not Logic::In(mean - eps, mean, mean + eps))
            {
                return false;
            }
        }
    }
    return true;
}

void SimulatorTSReports::PrintOpti(const VecD & predsPlot) const
{
    const EnjoLib::Str descr = "Opti results";
    //ToolsMixed().SystemCallWarn("clear", __PRETTY_FUNCTION__);
    GnuplotPlotTerminal1d(predsPlot, descr, 1, 1.1);
}
    
