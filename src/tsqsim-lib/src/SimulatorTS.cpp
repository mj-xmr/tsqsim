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
#include "PredictorStats.h"
#include "TSRes.h"
#include "URTWrap.h"
#include "DataOCHL.h"
#include "PredictorType.h"
#include "PredictorFactory.h"
#include "PredictorOutputType.h"

//#include <Template/ValArray.hpp>
#include <Math/GeneralMath.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Except.hpp>
#include <Util/Tuple.hpp>
#include <Util/ThreadWrap.hpp>
#include <Statistical/Assertions.hpp>

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
    //const double initial = m_per.GetCandles().GetDataIter().at(idxStart).GetHigh();
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
        m_rets = GetRetsFiltered(input);
    }
    {
        m_predsTrue     = Pred(m_rets, PredictorType::PRED_TRUE);       // Stays fixed
        m_predsBaseline = Pred(m_rets, PredictorType::PRED_BASELINE);   // Stays fixed
        m_preds         = Pred(m_rets, PredictorType::PRED_REGRESSION); // User interaction expected
        //m_preds         = Pred(m_rets, PredictorType::PRED_DUMB); // User interaction expected

        //{LOGL << "Sizes rets = " << m_rets.size() << ", true = " << m_predsTrue.size() << ", base = " << m_predsBaseline.size() << ", pred = " << m_preds.size() << Nl;}

        Assertions::SizesEqual(m_rets, m_predsTrue,     "m_rets & m_predsTrue");
        Assertions::SizesEqual(m_rets, m_predsBaseline, "m_rets & m_predsBaseline");
        Assertions::SizesEqual(m_rets, m_preds,         "m_rets & m_preds");

        Assertions::IsTrue (VecEqual(m_rets, m_predsTrue),       "m_rets == m_predsTrue");
        Assertions::IsFalse(VecEqual(m_rets, m_predsBaseline),   "m_rets != m_predsBaseline");
        Assertions::IsFalse(VecEqual(m_rets, m_preds),           "m_rets != m_preds");
    }
    {
        const std::vector<TSRes> & rec = GetReconstruction(&m_fun, m_rets, initial);
        m_reconstr = GetReconstructionFiltered(rec);
        /// TODO: Print also individual transformations and individual reconstructions sequentially for debugging.
        /// Iterate not by data point -> transformations, like now for speed, but by transformation -> data points
    }

    PrintResults();
}

EnjoLib::VecD SimulatorTS::GetRetsFiltered(const std::vector<Inp> & input) const
{
    const std::vector<TSRes> & rets = GetRets(input);
    EnjoLib::VecD retsFiltered;
    for (const TSRes & res : rets)
    {
        if (res.valid)
        {
            retsFiltered.Add(res.val);
        }
    }
    return retsFiltered;
}


EnjoLib::VecD SimulatorTS::Pred(const EnjoLib::VecD & data, const PredictorType & type) const
{
    //EnjoLib::VecD preds;
    const int horizon = 1;

    //preds.Add(data.at(0)); // Keep size equal
    const CorPtr<IPredictor> predAlgo = PredictorFactory().Create(type);
    return predAlgo->PredictNextVec(data);
    //return preds;
}

EnjoLib::VecD SimulatorTS::GetReconstructionFiltered(const std::vector<TSRes> & input) const
{
    EnjoLib::VecD reconstrFiltered;
    for (const TSRes & res : input)
    {
        //if (res.valid)
        {
            reconstrFiltered.Add(res.val);
        }
    }
    return reconstrFiltered;
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
    bool printPreds = false;
    printPreds = true;
    const DataOCHL ohlc(m_per.GetCandles().GetDataIter());
    const EnjoLib::VecD closes(ohlc.closes);
    const EnjoLib::Str descr = "\n1) Closes  2) Stationary  3) Predictions  4) Reconstruction";
    STDFWD::vector<const EnjoLib::VecD *> plots;
    plots.push_back(&closes);
    plots.push_back(&m_rets);
    if (printPreds)
    {
        //plots.push_back(&m_predsTrue);
        //plots.push_back(&m_predsBaseline);
        plots.push_back(&m_preds);
    }
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
    const PredictorStats statsPred;

    ELO
    urtWrap2.Show(data);
    if (m_cfgTS.PLOT_SERIES)
    {
        GnuplotPlotTerminal1dSubplots(plots, descr, scaleX, scaleY);
    }
    stats.Stats(m_per.GetSymbolPeriodId(), data, numSplits);
    const double urtStat = urtWrap1.GetStatistic(data);
    LOG << "Stationarity score = " << urtStat << Nl;
    LOG << statsPred.GenRepNext(m_rets, m_preds) << Nl;
}

bool SimulatorTS::VecEqual(const EnjoLib::VecD & data1, const EnjoLib::VecD & data2) const
{
    if (data1.size() != data2.size())
    {
        return false;
    }
    for (size_t i = 0; i < data1.size(); ++i)
    {
        if (data1.at(i) != data2.at(i))
        {
            return false;
        }
    }
    return true;
}

const EnjoLib::VecD & SimulatorTS::GetOutputSeries(const PredictorOutputType & type) const
{
    switch  (type)
    {
    case PredictorOutputType::SERIES:
       return m_rets;
    case PredictorOutputType::PREDICTION:
        return m_preds;
    case PredictorOutputType::BASELINE:
        return m_predsBaseline;
    }
    throw ExceptLogicError("GetOutputSeries");
}
