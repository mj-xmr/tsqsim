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
#include "Logic.h"

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
    //const int idxStart  = m_per.Len() - m_fun.Len();
    const int idxStart  = 0;
    const int idxFinish = m_per.Len();

    std::vector<Inp> input;
    VecD original;
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

        original.Add(m_per.GetCandles().GetDataIter().at(i).GetClose());
    }
    {
         LOGL << "Calculating...\n";
    }
    {
        m_original = original;
        m_dataMan = GetRetsFiltered(input);
    }

    {
        m_predsTrue     = Pred(m_fun, PredictorType::PRED_TRUE);       // Stays fixed. Simulates transformation and inverse transformation
        m_predsBaseline = Pred(m_fun, PredictorType::PRED_BASELINE);   // Stays fixed
        {
            LOGL << "\nPredn";
        }
        m_preds         = Pred(m_fun, m_cfgTS.GetPredType());

        //{LOGL << "Sizes rets = " << m_rets.size() << ", true = " << m_predsTrue.size() << ", base = " << m_predsBaseline.size() << ", pred = " << m_preds.size() << Nl;}

        Assertions::SizesEqual(m_dataMan.converted.size(), m_per.Len(),     "m_rets & m_per"); // Really?
        Assertions::SizesEqual(m_dataMan.converted, m_predsTrue,     "m_rets & m_predsTrue");
        Assertions::SizesEqual(m_dataMan.converted, m_predsBaseline, "m_rets & m_predsBaseline");
        Assertions::SizesEqual(m_dataMan.converted, m_preds,         "m_rets & m_preds");

        Assertions::IsTrue (VecEqual(m_dataMan.converted,     m_predsTrue, 0.01),       "m_rets == m_predsTrue");
        Assertions::IsTrue (VecEqual(m_original, m_predsTrue, 0.01),       "m_original == m_predsTrue");
        Assertions::IsFalse(VecEqual(m_dataMan.converted, m_predsBaseline),   "m_rets != m_predsBaseline");
        if (m_cfgTS.GetPredType() != PredictorType::PRED_TRUE)
        {
            Assertions::IsFalse(VecEqual(m_dataMan.converted, m_preds),           "m_rets != m_preds");
        }
    }
    {
        m_reconstr = m_predsTrue;
        Assertions::SizesEqual(m_dataMan.converted, m_reconstr,     "m_rets & m_reconstr");
        /// TODO: Print also individual transformations and individual reconstructions sequentially for debugging.
        /// Iterate not by data point -> transformations, like now for speed, but by transformation -> data points
    }
    {
        m_reconstrPredBase = m_predsBaseline;
        Assertions::SizesEqual(m_dataMan.converted, m_reconstrPredBase,     "m_rets & m_reconstrPredBase");
    }
    {
        m_reconstrPred = m_preds;
        Assertions::SizesEqual(m_dataMan.converted, m_reconstrPred,     "m_rets & m_reconstrPred");
    }

    PrintResults();
}

TSXformDataMan SimulatorTS::GetRetsFiltered(const std::vector<Inp> & input) const
{
    const std::vector<TSRes> & rets = GetRets(input);
    TSXformDataMan dataMan;
    for (const TSRes & res : rets)
    {
        //if (res.valid)
        {
            dataMan.Add(res);
        }
    }
    return dataMan;
}

EnjoLib::VecD SimulatorTS::Pred(const ITSFun & tsFun, const PredictorType & type) const
{
    const int horizon = 1;
    const CorPtr<IPredictor> predAlgo = PredictorFactory().Create(type);
    const EnjoLib::VecD & preds = predAlgo->Predict(m_dataMan.converted);

    LOGL << preds.Print() << Nl;

    const std::vector<TSRes> & rec = GetReconstruction(&m_fun, preds, m_dataMan.convertedLost);
    return GetReconstructionFiltered(rec);
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

std::vector<TSRes> SimulatorTS::GetReconstruction(const ITSFun * fun, const EnjoLib::VecD & input, const EnjoLib::Matrix & lostMat, bool additive) const
{   /// TODO: the double "initial" should probably be a vector of initial conditions, built from the 1st diffs (len = 1), 2nd diffs (len = 2), and so on.
    /// TODO: extract "lost information" from each transformation and apply here
    std::vector<TSRes> ret;
    //double prev = additive ? initial : 0;
    double prev = 0;
    //TSRes r1st(true);
    //r1st.val = prev;
    //ret.push_back(r1st);
    const size_t startIdx = 0; // Subject to transformation limits
    for (size_t i = startIdx; i < input.size(); ++i)
    {
        //if (inp.valid)
        {
            const VecD & lost = lostMat.at(i);
            TSRes res = fun->Reconstruct(i, input, lost);
            //LOGL << "OUT = " << res.val << " " << res.valid << Nl;
            //if (res.val != 0 && prev == 0 && i > 0)
            if (res.val == 0)
            {
                if (i == 0)
                {
                    res.val = m_original.at(0);
                }
                else
                {
                    res.val = m_original.at(i-1);  // Simulate baseline
                }
            }
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
    const EnjoLib::Str descr = "\n1) Original  2) Transformed  3) Predictions  4) Reconstruction";
    STDFWD::vector<const EnjoLib::VecD *> plots;
    plots.push_back(&closes);
    plots.push_back(&m_dataMan.converted);
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
        SimulatorTSMT::PrintExperimental(m_tsin, m_dataMan.converted, descr, plots);
    }
    else
    {
        PrintReportSingleThreaded(m_dataMan.converted, descr, plots);
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
    LOG << statsPred.GenRepNext(m_original, m_dataMan.converted, m_predsBaseline, m_preds) << Nl;
}

bool SimulatorTS::VecEqual(const EnjoLib::VecD & data1, const EnjoLib::VecD & data2, double eps) const
{
    if (data1.size() != data2.size())
    {
        return false;
    }
    for (size_t i = 0; i < data1.size(); ++i)
    {
        if (data1.at(i) != data2.at(i))
        {
            VecD vec {data1.at(i), data2.at(i) };
            const double mean = vec.Mean();
            if (not Logic::In(mean - eps, mean, mean + eps))
            {
                return false;
            }
        }
    }
    return true;
}

const EnjoLib::VecD & SimulatorTS::GetOutputSeries(const PredictorOutputType & type) const
{
    switch  (type)
    {
    case PredictorOutputType::SERIES:
       return m_dataMan.converted;
    case PredictorOutputType::PREDICTION:
        return m_preds;
    case PredictorOutputType::BASELINE:
        return m_predsBaseline;
    case PredictorOutputType::RECONSTRUCTION:
        return m_reconstr;
    case PredictorOutputType::RECONSTRUCTION_PRED:
        return m_reconstrPred;
   case PredictorOutputType::RECONSTRUCTION_PRED_BASELINE:
        return m_reconstrPredBase;
    }
    throw ExceptLogicError("GetOutputSeries");
}
