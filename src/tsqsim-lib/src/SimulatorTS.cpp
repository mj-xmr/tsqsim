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

//#include <Template/ValArray.hpp>
#include <Math/GeneralMath.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Except.hpp>
#include <Util/Tuple.hpp>

#include <STD/VectorCpp.hpp>

using namespace std;
using namespace EnjoLib;

SimulatorTS::~SimulatorTS(){}
SimulatorTS:: SimulatorTS(const TSInput & tsin, const ITSFun & fun)
: m_tsin(tsin)
, m_per(tsin.m_per)
, m_fun(fun)
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
    for (int i = idxStart; i < idxFinish; ++i)
    {
        Inp ele; /// TODO: MakeTuple
        //Inp ele(&m_per, &m_fun, i); /// TODO: MakeTuple
        Get<0>(ele) = &m_per;
        Get<1>(ele) = &m_fun;
        Get<2>(ele) = i;
        input.push_back(ele);
    }
    const std::vector<TSRes> & rets = SimulatorTSMT::GetRets(input);
    for (const TSRes & res : rets)
    {
        if (res.valid)
        {
            m_rets.Add(res.val);
        }
    }
    PrintResults();
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
    /// TODO: Make a non MT version as well
    SimulatorTSMT::PrintExperimental(m_tsin, m_rets);
}
