#include "OptimizerTS.h"
#include "IOptimizable.h"
#include "IPeriod.h"
#include "ConfigGlob.h"
#include "ConfigMan.h"
#include "ConfigOpti.h"

#include "SimulatorTSFactory.h"
#include "StrategyFactoryAbstract.h"
#include "StrategyType.h"
#include "OptiVar.h"
#include "TradeUtil.h"
#include "OptiVarVec.h"
#include "OptiType.h"
#include "TSUtil.h"
#include "TSFunFactory.h"
#include "TSInput.h"
//#include "OptiGoalFactory.h"

#include <Math/MultiDimIter/MultiDimIterTpl.hpp>
#include <Math/Opti/OptiMultiNelderMead.hpp>
#include <Math/Opti/OptiMultiBinSearch.hpp>
#include <Math/GeneralMath.hpp>
#include <Util/ProgressMonit.hpp>
#include <Util/ToolsMixed.hpp>
#include <Util/Except.hpp>
#include <Util/CoutBuf.hpp>
#include <Statistical/Statistical.hpp>
#include <Template/CorradePointer.h>

#include <STD/VectorCpp.hpp>

using namespace std;
using namespace EnjoLib;

OptimizerTS::OptimizerTS(const TSFunType & stratType, const ISymbol & sym, const IPeriod & period, const TSFunFactory & stratFact, StartEnd startEndFrame)
: OptimizerBase(startEndFrame)
, m_sym(sym)
, m_period(period)
, m_funFact(stratFact)
, m_funType(stratType)
{
    const TSInput tsin(m_period, *gcfgMan.cfgTS.get());
    CorPtr<ITSFun> pfun = m_funFact.Create(tsin, m_funType);
    ITSFun & fun = *pfun;
    InitFromOptimizable(fun, period);
}
OptimizerTS::~OptimizerTS(){}

void OptimizerTS::Consume(const EnjoLib::VecD & data)
{
    ++m_iter;
    const EnjoLib::Str & idd = m_period.GetSymbolPeriodId();

    //const OptiGoalType type = OptiGoalType::SHARPE;
    //const OptiGoalType type = gcfgMan.cfgOpti->GetGoalType();
    //const CorPtr<IOptiGoal> pgoal = OptiGoalFactory::Create(type);
    //const IOptiGoal & igoal = *pgoal;

    //LOGL << "Data = " << data.Print() << Nl;
    float goal = 0;

    //CorPtr<IPosition> pos = IPosition::Create(m_period.GetSymbolName());
    switch (gcfgMan.cfgOpti->GetMethod())
    {
        case OptiMethod::OPTI_METHOD_BISECTION:
        {
            /*
            SafePtrThin<IOptiSubjectTF> osub(IOptiSubjectTF::Create(m_sym, m_period, m_stratType, m_stratFact, igoal, GetOptiFloat(), data));
            //Result<VecD> res = OptiMultiNelderMead().Run(*osub, 0.1, 10, 10);
            Result<VecD> res = OptiMultiBinSearch().Run(*osub, 3, 100); /// TODO: Make multithreaded
            if (not res.isSuccess)
            {
                LOGL << idd << ": Failed Nelder-Mead" << Nl;
                //return;
            }
            //pos->CopyFrom(osub->GetPosition());

            //const ProfitsCalc & profits = pos->GetProfitsCalc();
            //float sum = igoal.GetGoal(profits);
            LOGL << idd << ": Nelder-Mead sum = " << sum << Nl;

            //PrintArgs(os.GetOptiVarsResult());
            //if (IsOptiGoalReached(profits))
            {
                GetOptiFloatResult() = osub->GetOptiVarsResult();
            }
            */
        }
        break;
        case OptiMethod::OPTI_METHOD_MONTECARLO:
        case OptiMethod::OPTI_METHOD_GRID:
        {
            const TSInput tsin(m_period, *gcfgMan.cfgTS.get());
            CorPtr<ITSFun> fun = m_funFact.Create(tsin, m_funType);
            fun->UpdateOptiVars(data);
            CorPtr<ISimulatorTS> psim = TSUtil().GetSim(m_period, *fun, m_startEndFrame);

            goal = psim->GetScoreStationarity();

            if (IsGoalReached(goal))
            {
                OnGoalReached(fun.get());
            }

            /// TODO: MonteCarlo early stop if goal's variance stops changing
            //ToolsMixed().SystemCallWarn("clear", __PRETTY_FUNCTION__); PrintCurrentResults();
        }
    }

    //const ProfitsCalc & profits = pos->GetProfitsCalc();
    //m_calcs.Add(profits);
    //m_goals.Add(igoal.GetGoal(profits));
    AddGoal(goal);
    const bool verbose = gcfgMan.cfgOpti->OPTI_VERBOSE && m_isVerbose;
    if (IsGoalReached(goal))
    {
        //const float goal = igoal.GetGoal(profits);
        // Plot new, better solution
        if (verbose)
        {
            if (not gcfgMan.cfgOpti->IsXValid())
            {
                //GnuplotMan().PlotGnuplot(profits.GetProfits(), m_outDir, true);
                PrintCurrentResults();
                LOGL << idd << ": New profit = " << goal << ", after " << m_iter << " iterations\n";
            }
        }
        //m_calcs.SetBest(profits);
        UpdateGoalMax(goal);
    }
    else
    {
        // Print status, erasing the previous one
        if (verbose)
        {
            if (not gcfgMan.cfgOpti->IsXValid())
            {
                m_progressMonitHigh.PrintProgressBarTime(m_iter, m_numCombis, idd);
            }
        }
        //GnuplotMan().PlotGnuplot(pos.GetProfitsCalc().GetProfits(), true); /// test
    }
}

void OptimizerTS::PrintStats() const
{
    ///LOGL << m_calcs.GetStats() << Nl;
}

void OptimizerTS::PrintStatsSummary() const
{
    //{LOGL << "Variance changes:" << Endl;}
    //m_calcs.PlotVariance(m_goalsMod.Diffs().Smooth(SMOOTHING));
}

std::vector<const IPeriod *> OptimizerTS::GetPeriods() const
{
    return std::vector<const IPeriod *>{&m_period};
}

