#include "OptiSubjectPred.h"
#include "OptiSubjectTSUtil.h"
#include "PredictorFactory.h"
#include "IPeriod.h"
#include "OptiVarVec.h"
#include "ConfigMan.h"
#include "ConfigOpti.h"
#include "ConfigDirs.h"
#include "ISimulatorTS.h"
#include "TSUtil.h"
//#include "GnuplotMan.h"

#include <Util/CoutBuf.hpp>
#include <Template/Array.hpp>

using namespace EnjoLib;

OptiSubjectPred::OptiSubjectPred(const ISymbol & sym, const IPeriod & period, 
                                 const PredictorFactory & fact, const PredictorType & type, 
                                 const STDFWD::vector<OptiVarF> & optiFloat, 
                                 const StartEnd & startEndFrame, const EnjoLib::VecD & iterData)
: m_sym(sym)
, m_period(period)
, m_fact(fact)
, m_type(type)
, m_startEndFrame(startEndFrame)
, m_iterData(iterData)
{
    for (const OptiVarF & var : optiFloat)
    {
        //if (not var.fp)
        //    continue;
        m_optiFloat.push_back(var);
    }
}

OptiSubjectPred::~OptiSubjectPred()
{
    //dtor
}

double OptiSubjectPred::Get(const double * inp, int n)
{
    CorPtr<IPredictor> fun = m_fact.Create(m_period, m_type);
    IPredictor & strat = *(fun.get());
    EnjoLib::Array<OptiVarF *> vopti = fun->GetOptiFloat().Vec();
    const double penality = OptiSubjectTSUtil().UpdateOptiGetPenality(inp, n, m_iterData, fun.get());
    CorPtr<ISimulatorTS> psim = TSUtil().GetSimPred(m_period, fun->GetOptiVec(), m_startEndFrame);
    const double sum = psim->GetScorePred();

    const float sumAdjusted = sum - penality;
    
    //LOGL << sum << ", adj = "  << sumAdjusted << Endl;

    if (sum > m_sumMax || m_sumMax == 0)
    {
        //LOGL << sum << ", adj = "  << sumAdjusted << Endl;
        m_sumMax = sum;
        
        m_optiFloatResult.clear();
        for (OptiVarF * v : vopti)
            m_optiFloatResult.push_back(*v);

        //if (gcfgMan.cfgOpti->OPTI_VERBOSE && m_isVerbose)
        if (gcfgMan.cfgOpti->OPTI_VERBOSE)
        {
            if (not gcfgMan.cfgOpti->IsXValid())
            {
                psim->PrintOpti();
                //GnuplotMan().PlotGnuplot(profits.GetProfits(), "/tmp/a", true);
                //PrintCurrentResults();
                LOGL << ": New goal = " << sum << ", after " << 0 << " iterations\n";
            }
        }
    }

    return sumAdjusted;
    //return -sum;
}

double OptiSubjectPred::GetGoal() const
{
    return m_sumMax;
}

EnjoLib::VecD OptiSubjectPred::GetStart() const
{
    return OptiSubjectTSUtil().GetStartProt(m_optiFloat);
}
EnjoLib::VecD OptiSubjectPred::GetStep() const
{
    return OptiSubjectTSUtil().GetStepProt(m_optiFloat);
}
EnjoLib::Array<EnjoLib::OptiMultiSubject::Bounds> OptiSubjectPred::GetBounds() const
{
    return OptiSubjectTSUtil().GetBoundsProt(m_optiFloat);
}
