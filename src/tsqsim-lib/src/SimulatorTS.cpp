#include "SimulatorTS.h"
#include "SimulatorTSMT.h"
#include "SimulatorTSReports.h"
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
#include "BufferDouble.h"
#include "Logic.h"

#include <Math/GeneralMath.hpp>
#include <Util/VecOpThin.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Except.hpp>
#include <Util/Tuple.hpp>
#include <Util/ThreadWrap.hpp>
#include <Statistical/Assertions.hpp>
#include <Template/Array.hpp>

#include <STD/VectorCpp.hpp>

using namespace std;
using namespace EnjoLib;

SimulatorTS::~SimulatorTS(){}
SimulatorTS:: SimulatorTS(const TSInput & tsin, const ITSFun & fun)
: m_tsin(tsin)
, m_per(tsin.m_per)
, m_fun(fun)
, m_cfgTS(tsin.m_cfgTS)
, m_ppred(PredictorFactory().Create(m_per, m_cfgTS.GetPredType()))
{
}

ISimulator * SimulatorTS::CloneRaw() const
{
    return new SimulatorTS(m_tsin, m_fun);
}

void SimulatorTS::Run()
{
    LOGL << "SimulatorTS(): Run() unimplemented\n";
}

void SimulatorTS::RunRaw(const StartEnd & startEndFrame)
{
    //const int idxStart  = m_per.Len() - m_fun.Len();
    int idxStart  = 0;
    int idxFinish = m_per.Len();
    if (startEndFrame.IsValid()) /// TODO: This should only influence the VIEW of the data, not the data itself. Symptom - torn XVAL plot at the end.
    {
        idxStart = startEndFrame.start;
        idxFinish = startEndFrame.end;
    }
    const int len = idxFinish - idxStart;

    const SimulatorTSReports reps;

    std::vector<Inp> input;
    VecD original;
    //const double initial = m_per.GetCandles().GetDataIter().at(idxStart).GetPriceByType(m_cfgTS.GetPriceType());
    input.reserve(idxFinish - idxStart);
    {
         //LOGL << "Collecting input...\n";
    }
    for (int i = idxStart; i < idxFinish; ++i)
    {
        Inp ele; /// TODO: MakeTuple
        //Inp ele(&m_per, &m_fun, i); /// TODO: MakeTuple
        Get<0>(ele) = &m_per;
        Get<1>(ele) = &m_fun;
        Get<2>(ele) = i;
        input.push_back(ele);

        original.Add(m_per.GetCandles().GetDataIter().at(i).GetPriceByType(m_cfgTS.GetPriceType()));
    }
    {
         //LOGL << "Calculating... " << startEndFrame.ToStr() << "\n";
    }
    {
        m_original = original;
        m_dataMan = GetRetsFiltered(input);
    }

    {
        m_predsTrue     = Pred(PredictorType::PRED_TRUE);       // Stays fixed. Simulates transformation and inverse transformation
        m_predsBaseline = Pred(PredictorType::PRED_BASELINE);   // Stays fixed
        {
            //LOGL << "\nPredn";
        }
        m_preds         = PredAlgo(*m_ppred);

        //{LOGL << "Sizes rets = " << m_rets.size() << ", true = " << m_predsTrue.size() << ", base = " << m_predsBaseline.size() << ", pred = " << m_preds.size() << Nl;}

        Assertions::SizesEqual(m_dataMan.converted.size(),  len,             "m_rets & m_per"); // Really?
        Assertions::SizesEqual(m_dataMan.converted,         m_predsTrue,     "m_rets & m_predsTrue");
        Assertions::SizesEqual(m_dataMan.converted,         m_predsBaseline, "m_rets & m_predsBaseline");
        Assertions::SizesEqual(m_dataMan.converted,         m_preds,         "m_rets & m_preds");

        Assertions::IsTrue (Logic::VecEqual(m_dataMan.converted,  m_predsTrue, 0.01),   "m_rets == m_predsTrue");
        Assertions::IsTrue (Logic::VecEqual(m_original,           m_predsTrue, 0.01),   "m_original == m_predsTrue");
        Assertions::IsFalse(Logic::VecEqual(m_dataMan.converted,  m_predsBaseline),     "m_rets != m_predsBaseline");
        if (m_cfgTS.GetPredType() != PredictorType::PRED_TRUE)
        {
            //Assertions::IsFalse(Logic::VecEqual(m_dataMan.converted, m_preds, 0.01),           "m_rets != m_preds");
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

    {
        const URTWrap urtWrap;
        //const double urtStat = urtWrap.GetStatistic(m_dataMan.converted);
        //m_goalStationarity = urtStat;

        const PredictorStats statsPred;
        const PredictorStatsRes & predPoints = statsPred.GenPoints(m_original, m_predsBaseline, m_preds);
        m_goalPred = predPoints.ratioPred2Base;
    }

    const VecD & predsNew = reps.PrepPredsPlot(m_original, m_predsBaseline, m_preds);
    VecOpThin().AddRef(predsNew, &m_predsPlot);
    //m_predsPlot = predsNew;
    if (IsVerbose())
    {
        PrintResults();
    }
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

EnjoLib::VecD SimulatorTS::Pred(const PredictorType & type) const
{
    const CorPtr<IPredictor> predAlgo = PredictorFactory().Create(m_per, type);
    return PredAlgo(*predAlgo);
}

EnjoLib::VecD SimulatorTS::PredAlgo(const IPredictor & predAlgo) const
{
    //const int horizon = 1;
    const EnjoLib::VecD & preds = PredCommon(predAlgo, m_dataMan.converted);

    const std::vector<TSRes> & rec = GetReconstruction(&m_fun, preds, m_dataMan.convertedLost);
    const EnjoLib::VecD & recV = GetReconstructionFiltered(rec);
    //LOGL << "Preds = " << preds.Print() << Nl << "Reconstr = " << recV.Print()<< Nl;
    return recV;
}

EnjoLib::VecD SimulatorTS::PredCommon(const IPredictor & predAlgo, const EnjoLib::VecD & data) const
{
    if (m_cfgTS.USE_VECTOR_PRED)
    {
        const EnjoLib::VecD & predVec = predAlgo.AssertNoLookaheadBiasGetVec(data);
        //const EnjoLib::VecD & predVec = predAlgo.PredictVec(data); // Dangerous
        return predVec;
    }
    else
    {
        return predAlgo.Predict(data);
    }
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

std::vector<TSRes> SimulatorTS::GetReconstruction(const ITSFun * fun, const EnjoLib::VecD & input, const EnjoLib::Matrix & lostMat) const
{   /// TODO: the double "initial" should probably be a vector of initial conditions, built from the 1st diffs (len = 1), 2nd diffs (len = 2), and so on.
    /// TODO: extract "lost information" from each transformation and apply here
    std::vector<TSRes> ret;
    const VecD & reconstr = fun->ReconstructVec(input, lostMat);
    //LOGL << "Reconstr = " << reconstr.Print() << Nl;
    for (int i = 0; i < reconstr.size(); ++i)
    {
        TSRes res;
        res.val = reconstr.at(i);
        if (reconstr.at(i) == 0)
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
    return ret;
}

TSRes SimulatorTS::IterBet(const Inp & ele)
{
    const IDataProvider * data = Get<0>(ele);
    const ITSFun * fun = Get<1>(ele);
    const int i = Get<2>(ele);

    //const unsigned sti = data->GetCandles().ConvertIndex(i);
    const TSRes & res = fun->OnDataPoint(i);
    return res;
    //LOGL << "i = " << i << ", res = " << res << Nl;
}

void SimulatorTS::ReinitOptiVars(const EnjoLib::VecD & optiVars)
{
    m_ppred->UpdateOptiVars(optiVars);
}

void SimulatorTS::PrintResults() const
{
    //PrintChanges();
    //PrintBalance();
    PrintExperimental();
}

void SimulatorTS::PrintOpti() const
{
    //const VecD & predsPlot = SimulatorTSReports().PrepPredsPlot(m_original, m_predsBaseline, m_preds);
    //SimulatorTSReports().PrintOpti(predsPlot);
    SimulatorTSReports().PrintOpti(m_predsPlot);
}

void SimulatorTS::PrintExperimental() const
{
    bool printPreds = false;
    printPreds = true;
    const DataOCHL ohlc(m_per.GetCandles().GetDataIter());
    const EnjoLib::VecD closes(ohlc.closes);
    const EnjoLib::Str descr = "\n1) Original  2) Transformed  3) Predictions  4) Cumul. score  5) Reconstruction";
    STDFWD::vector<const EnjoLib::VecD *> plots;
    plots.push_back(&closes);
    plots.push_back(&m_dataMan.converted);
    if (printPreds)
    {
        //plots.push_back(&m_predsTrue);
        //plots.push_back(&m_predsBaseline);
        plots.push_back(&m_preds);
        plots.push_back(&m_predsPlot);
    }
    plots.push_back(&m_reconstr);


    if (m_cfgTS.MT_REPORT)
    {
        // Multithreaded
        SimulatorTSMT::PrintExperimental(m_tsin, m_dataMan.converted, descr, plots);
    }
    else
    {
        SimulatorTSReports().PrintReportSingleThreaded(m_per, m_cfgTS, m_dataMan.converted, descr, plots);
    }
    ELO
    const PredictorStats statsPred;
    const PredictorStatsRes & predPoints = statsPred.GenPoints(m_original, m_predsBaseline, m_preds);
    LOG << statsPred.GenRepNext(predPoints) << Nl;
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

float SimulatorTS::GetScorePred() const
{
    return - m_goalPred;
}
float SimulatorTS::GetScoreStationarity() const
{
    return - m_goalStationarity;
}

void SimulatorTS::SetSilent()
{
    m_silent = true;
}

bool SimulatorTS::IsVerbose() const
{
    return not m_silent;
}
