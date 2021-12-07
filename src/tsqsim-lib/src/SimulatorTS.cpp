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
    const double initial = m_per.GetCandles().GetDataIter().at(idxStart).GetClose();
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
    {
        const std::vector<TSRes> & rets = GetRets(input);
        m_rets.clear();
        for (const TSRes & res : rets)
        {
            if (res.valid)
            {
                m_rets.Add(res.val);
            }
        }
    }
    {
        const std::vector<TSRes> & rec = GetReconstruction(&m_fun, m_rets, initial);
        m_reconstr.clear();
        for (const TSRes & res : rec)
        {
            //if (res.valid)
            {
                m_reconstr.Add(res.val);
            }
        }

        /// TODO: Print also individual transformations and individual reconstructions sequentially for debugging.
        /// Iterate not by data point -> transformations, like now for speed, but by transformation -> data points
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

std::vector<TSRes> SimulatorTS::GetReconstruction(const ITSFun * fun, const EnjoLib::VecD & input, double initial) const
{   /// TODO: the double "initial" should probably be a vector of initial conditions, built from the 1st diffs (len = 1), 2nd diffs (len = 2), and so on.
    std::vector<TSRes> ret;
    double prev = initial;
    TSRes r1st(true);
    r1st.val = prev;
    ret.push_back(r1st);
    const size_t startIdx = 1; // Subject to transformation limits
    for (size_t i = startIdx; i < input.size() - 1; ++i)
    {
        //if (inp.valid)
        {
            const TSRes & res = fun->Reconstruct(i, input, prev);
            //LOGL << "OUT = " << res.val << " " << res.valid << Nl;
            prev = res.val;
            ret.push_back(res);
        }
    }
    return ret;
}

TSRes SimulatorTS::IterBet(const Inp & ele)
{
    const IDataProvider * data = Get<0>(ele);
    const ITSFun * fun = Get<1>(ele);
    const int i = Get<2>(ele);

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
    const DataOCHL ohlc(m_per.GetCandles().GetDataIter());
    const EnjoLib::VecD closes(ohlc.closes);
    const EnjoLib::Str descr = "\n1) Closes  2) Stationary  3) Reconstruction";
    STDFWD::vector<const EnjoLib::VecD *> plots;
    plots.push_back(&closes);
    plots.push_back(&m_rets);
    plots.push_back(&m_reconstr);
    if (m_cfgTS.MT_REPORT)
    {
        // Multithreaded
        SimulatorTSMT::PrintExperimental(m_tsin, m_rets, descr, plots);
    }
    else
    {
        PrintReportSingleThreaded(m_rets, descr, plots);
    }
}

void SimulatorTS::PrintReportSingleThreaded(const EnjoLib::VecD & data, const EnjoLib::Str & descr, const STDFWD::vector<const EnjoLib::VecD *> & plots) const
{
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
        GnuplotPlotTerminal1dSubplots(plots, descr, scaleX, scaleY);
    }
    stats.Stats(m_per.GetSymbolPeriodId(), data, numSplits);
    const double urtStat = urtWrap1.GetStatistic(data);
    LOG << "Stationarity score = " << urtStat << Nl;
}
