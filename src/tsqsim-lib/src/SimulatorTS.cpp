#include "SimulatorTS.h"
#include "SimulatorTSMT.h"
#include "IPeriod.h"
#include "IBufferCandles.h"
#include "Candle.h"
#include "GnuplotIOSWrap.h"
#include "ITSFun.h"
#include "TSInput.h"
#include "ConfigTS.h"
#include "StatsMedianSplit.h"
#include "TSRes.h"
#include "URTWrap.h"
#include "DataOCHL.h"

//#include <Template/ValArray.hpp>
#include <Math/GeneralMath.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Except.hpp>
#include <Util/Tuple.hpp>
#include <Util/ThreadWrap.hpp>

#include <STD/VectorCpp.hpp>

using namespace std;
using namespace EnjoLib;

SimulatorTS::~SimulatorTS(){}
SimulatorTS:: SimulatorTS(const TSInput & tsin, const ITSFun & fun)
: m_tsin(tsin)
, m_per(tsin.m_per)
, m_fun(fun)
, m_cfgTS(tsin.m_cfgTS)
{
}

void SimulatorTS::Run()
{
    LOGL << "SimulatorTS(): Run() unimplemented\n";
}

void SimulatorTS::RunRaw(const StartEnd & startEndFrame)
{
    const int idxStart  = m_per.Len() - m_fun.Len();
    const int idxFinish = m_per.Len();

    std::vector<Inp> input;
    input.reserve(idxFinish - idxStart);
    {
         LOGL << "Collecting input...\n";
    }
    for (int i = idxStart; i < idxFinish; ++i)
    {
        Inp ele; /// TODO: MakeTuple
        //Inp ele(&m_per, &m_fun, i); /// TODO: MakeTuple
        Get<0>(ele) = &m_per;
        Get<1>(ele) = &m_fun;
        Get<2>(ele) = i;
        input.push_back(ele);
    }
    {
         LOGL << "Calculating...\n";
    }
    const std::vector<TSRes> & rets = GetRets(input);
    for (const TSRes & res : rets)
    {
        if (res.valid)
        {
            m_rets.Add(res.val);
        }
    }
    PrintResults();
}

std::vector<TSRes> SimulatorTS::GetRets(const std::vector<Inp> & input) const
{
    if (m_cfgTS.MT_XFORM)
    {
        {
            LOGL << "Multithreaded transformations selected. Using " << ThreadWrap::GetConcurrency() << " cores.\n";
        }
        return SimulatorTSMT::GetRetsMT(input);
    }
    else
    {
        std::vector<TSRes> ret;
        for (const Inp & inp : input)
        {
            ret.push_back(IterBet(inp));
        }
        return ret;
    }
}

/// TODO: Reconstruct signal!!!
TSRes SimulatorTS::IterBet(const Inp & ele)
{
    const IDataProvider * data = Get<0>(ele);
    const ITSFun * fun = Get<1>(ele);
    const int i = Get<2>(ele);
    /*
    const Candle & canCurr = m_per.GetCandles().GetDataIter().at(i);
    const double changeAvg = GetChangeAverage(canCurr.GetHour());
    const BetIter betIter(changeAvg, m_meanChange);
    const double houseProfit = betIter.GetHouseProfitDrawBet(m_gen);
    m_balance.push_back(houseProfit);
    */
    const unsigned sti = data->GetCandles().ConvertIndex(i);
    const TSRes & res = fun->OnDataPoint(sti);
    return res;
    //LOGL << "i = " << i << ", res = " << res << Nl;
}

void SimulatorTS::PrintResults()
{
    //PrintChanges();
    //PrintBalance();
    PrintExperimental();
}

void SimulatorTS::PrintExperimental() const
{
    if (m_cfgTS.MT_REPORT)
    {
        /// TODO: Make a non MT version as well
        SimulatorTSMT::PrintExperimental(m_tsin, m_rets);
    }
    else
    {
        PrintReportSingleThreaded(m_rets);
    }
}

void SimulatorTS::PrintReportSingleThreaded(const EnjoLib::VecD & data) const
{
    DataOCHL ohlc(m_per.GetCandles().GetDataIter());
    const float scaleX = 1.00;
    const float scaleY = 0.6;
    const int numSplits = 3;
    const URTWrap urtWrap1, urtWrap2;
    const bool multithreaded = false;
    const StatsMedianSplit stats(multithreaded);

    ELO
    urtWrap2.Show(data);
    if (m_cfgTS.PLOT_SERIES)
    {
        GnuplotPlotTerminal1d(ohlc.closes, "Closes & Diffs", scaleX, scaleY);
        GnuplotPlotTerminal1d(data,      "",               scaleX, scaleY);
    }
    stats.Stats(m_per.GetSymbolPeriodId(), data, numSplits);
    const double urtStat = urtWrap1.GetStatistic(data);
    LOG << "Stationarity score = " << urtStat << Nl;
}
