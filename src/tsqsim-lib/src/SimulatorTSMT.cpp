#include "SimulatorTSMT.h"

#include "StatsMedianSplit.h"

#include "URTWrap.h"
#include "DataOCHL.h"
#include "ConfigTS.h"
#include "GnuplotIOSWrap.h"
#include "IPeriod.h"
#include "IBufferCandles.h"
#include "TSInput.h"
#include "TSRes.h"

#include <Util/CoutBuf.hpp>
#include <Util/Tuple.hpp>
#include <Template/LoopThreadedTpl.hpp>

#include <STD/VectorCpp.hpp>

using namespace EnjoLib;

void SimulatorTSMT::PrintExperimental(const TSInput & tsin, const EnjoLib::VecD & data)
{
    DataOCHL ohlc(tsin.m_per.GetCandles().GetDataIter());
    const float scaleX = 1.00;
    const float scaleY = 0.6;
    const int numSplits = 3;
    const URTWrap urtWrap1, urtWrap2;
    const bool multithreaded = true;
    const StatsMedianSplit stats(multithreaded);
    ELO

    std::future<StatsMedianSplit::Results> futSta = std::async(std::launch::async, [&]{ return stats.CalcResults(data, numSplits); });
    std::future<double> futURT2 = std::async(std::launch::async, [&]{ return urtWrap1.GetStatistic(data); });
    std::future<void> futPLT = std::async(std::launch::async, [&]
                                          {
                                              if (tsin.m_cfgTS.PLOT_SERIES)
                                                {
                                                    GnuplotPlotTerminal1d(ohlc.closes, "Closes & Diffs", scaleX, scaleY);
                                                    GnuplotPlotTerminal1d(data,      "",               scaleX, scaleY);
                                                }
                                          });
    urtWrap2.Show(data);
    futPLT.get();
    //const Results & res =
    //const EnjoLib::Str & rep = Report(idd, res);
    //stats.Stats(m_per.GetSymbolPeriodId(), data);
    LOG << stats.Report(tsin.m_per.GetSymbolPeriodId(), futSta.get()) << Nl;
    LOG << "Stationarity score = " << futURT2.get() << Nl;
}

stdfwd::vector<TSRes> SimulatorTSMT::GetRetsMT(const stdfwd::vector<SimulatorTS::Inp> input)
{
    std::function<decltype(SimulatorTS::IterBet)> f_conv = &SimulatorTS::IterBet;
    const std::vector<TSRes> & rets = ConvertVectorThreaded(input, f_conv); /// TODO: 1 Single threaded doesn't work
    return rets;
}
