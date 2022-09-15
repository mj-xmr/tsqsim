#include "OptimizerPred.h"
#include "IOptimizable.h"
#include "IPeriod.h"
#include "ConfigGlob.h"
#include "ConfigMan.h"
#include "ConfigOpti.h"

#include "StrategyFactoryAbstract.h"
#include "StrategyType.h"
#include "OptiVar.h"
#include "TradeUtil.h"
#include "OptiVarVec.h"
#include "OptiType.h"
#include "OptiSubjectPred.h"
#include "TSUtil.h"
#include "PredictorFactory.h"
#include "TSInput.h"

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

OptimizerPred::OptimizerPred(const PredictorType & type, const ISymbol & sym, const IPeriod & period, const PredictorFactory & stratFact, StartEnd startEndFrame)
: OptimizerBase(startEndFrame)
, m_sym(sym)
, m_period(period)
, m_fact(stratFact)
, m_type(type)
{
    const TSInput tsin(m_period, *gcfgMan.cfgTS.get());
    CorPtr<IPredictor> fun = m_fact.Create(period, m_type);
    InitFromOptimizable(*fun, period);

    m_len = fun->Len();
}
OptimizerPred::~OptimizerPred(){}

CorPtr<IOptimizer> OptimizerPred::Create(const StartEnd & startEndFrame) const
{
    return CorPtr<IOptimizer>(new OptimizerPred(m_type, m_sym, m_period, m_fact, startEndFrame));
}

int OptimizerPred::Len() const
{
    return m_len;
}

void OptimizerPred::Consume(const EnjoLib::VecD & data)
{
    ++m_iter;
    const EnjoLib::Str & idd = m_period.GetSymbolPeriodId();

    //const OptiGoalType type = OptiGoalType::SHARPE;
    //const OptiGoalType type = gcfgMan.cfgOpti->GetGoalType();
    //const CorPtr<IOptiGoal> pgoal = OptiGoalFactory::Create(type);
    //const IOptiGoal & igoal = *pgoal;

    //LOGL << "Iter Data = " << data.Print() << Nl;
    float goal = 0;

    //CorPtr<IPosition> pos = IPosition::Create(m_period.GetSymbolName());
    switch (gcfgMan.cfgOpti->GetMethod())
    {
        case OptiMethod::OPTI_METHOD_BISECTION:
        {
            OptiSubjectPred osub(m_sym, m_period, m_fact, m_type, GetOptiFloat(), m_startEndFrame, data);

            //Result<VecD> res = OptiMultiNelderMead().Run(*osub, 0.1, 10, 10);
            Result<VecD> res = OptiMultiBinSearch().Run(osub, 3, 100); /// TODO: Make multithreaded
            if (not res.isSuccess)
            {
                LOGL << idd << ": Failed Bisection" << Nl;
                return;
            }
            goal = osub.GetGoal();
            LOGL << idd << ": Bisection sum = " << goal << Nl;

            //PrintArgs(os.GetOptiVarsResult());
            //if (IsOptiGoalReached(profits))
            {
                GetOptiFloatResult() = osub.GetOptiVarsResult();
            }
        }
        break;
        case OptiMethod::OPTI_METHOD_MONTECARLO:
        case OptiMethod::OPTI_METHOD_GRID:
        {

            CorPtr<ISimulatorTS> psim = TSUtil().GetSimPred(m_period, data, m_startEndFrame);

            goal = psim->GetScorePred();
            //LOGL << Nl << "goal = " << goal << ". data = " << data.Print() << Nl;

            if (IsGoalReached(goal))
            {
                CorPtr<IPredictor> fun = m_fact.Create(m_period, m_type);
                fun->UpdateOptiVars(data); // Just needs a carrier TODO: Remove in future as is not abstract enough

                //LOG << "Goal reached = " << goal << Nl;
                OnGoalReached(fun.get());
                if (gcfgMan.cfgOpti->OPTI_VERBOSE)
                {
                    psim->PrintOpti();
                }
            }
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
                LOGL << idd << ": New goal = " << goal << ", after " << m_iter << " iterations\n";
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

void OptimizerPred::PrintStats() const
{
    ///LOGL << m_calcs.GetStats() << Nl;
}

void OptimizerPred::PrintStatsSummary() const
{
    if (gcfgMan.cfgOpti->GetMethod() == OptiMethod::OPTI_METHOD_MONTECARLO)
    {
        PlotVariance();
    }
}

std::vector<const IPeriod *> OptimizerPred::GetPeriods() const
{
    return std::vector<const IPeriod *>{&m_period};
}

