#include "OptimizerBase.h"
#include "IOptimizable.h"
#include "IPeriod.h"
#include "GnuplotIOSWrap.h"

#include "OptiVar.h"
#include "OptiVarVec.h"
#include "IOptiSubject.h"
#include "IOptiGoal.h"
//#include "ProfitsCalc.h"
//#include "GnuplotMan.h"
#include "ConfigOpti.h"
#include "ConfigMan.h"
#include "TradeUtil.h"
#include "StatsUtil.h"

#include <Statistical/Distrib.hpp>
#include <Statistical/Formatters.hpp>
#include <Statistical/Statistical.hpp>
#include <Math/MultiDimIter/MultiDimIterTpl.hpp>
#include <Math/Opti/OptiMultiNelderMead.hpp>
#include <Math/Opti/OptiMultiBinSearch.hpp>
#include <Math/GeneralMath.hpp>
#include <Util/ProgressMonit.hpp>
#include <Util/PimplCopier.hpp>
#include <Util/PimplDeleter.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/Except.hpp>
#include <Ios/IoManip.hpp>
#include <Template/Array.hpp>

#include <STD/VectorCpp.hpp>

using namespace std;
using namespace EnjoLib;

struct OptimizerBase::Impl
{
    std::vector<OptiVarF> m_optiFloat;
    std::vector<OptiVarF> m_optiFloatResult;
};
PIMPL_COPIER(OptimizerBase)
PIMPL_DELETER(OptimizerBase)

OptimizerBase::~OptimizerBase(){}
OptimizerBase::OptimizerBase(const StartEnd & startEndFrame)
: m_startEndFrame(startEndFrame)
, m_impl(new Impl())
{}

void OptimizerBase::InitFromOptimizable(IOptimizable & opti, const IDataProvider & per)
{
    if (opti.GetOptiFloat().Vec().empty())
    {
        throw EnjoLib::ExceptInvalidArg("OptimizerBase::OptimizerBase(): empty GetOptiFloat().Vec()");
    }
    for (OptiVarF * var : opti.GetOptiFloat().Vec())
    {
        GetOptiFloat().push_back(*var);
    }
    GetOptiFloatResult() = GetOptiFloat();
    m_numCombis = GetNumCombinations(opti);
    m_outDir = TradeUtil().GetOutputDir(per);
}

int OptimizerBase::GetNumCombinations(IOptimizable & opt) const
{
    int combis = 0;
    for (OptiVarF * var : opt.GetOptiFloat().Vec())
    {
        int sz;
        if (gcfgMan.cfgOpti->IsSearchFloatingPoint() && var->fp)
            sz = 1;
        else
            sz = var->GetSpace().size();
        if (combis == 0)
            combis = sz;
        else
            combis *= sz;
    }
    if (gcfgMan.cfgOpti->IsSearchRandom())
    {
        const long int maxSamples = gcfgMan.cfgOpti->OPTI_RANDOM_SAMPLES_NUM;
        if (combis > maxSamples)
        {
            return maxSamples;
        }
    }
    return combis;
}

OptiVarF * OptimizerBase::FindVarCurrent(IOptimizable & opt, unsigned iVar) const
{
    EnjoLib::Array<OptiVarF *> vopti = opt.GetOptiFloat().Vec();
    if (iVar >= vopti.size())
        return NULL;
    return vopti.at(iVar);
}


void OptimizerBase::operator()()
{
    MultiDimIterTpl multiDimIter;
    MultiDimIterTpl::VVt data;
    const size_t numVars = GetOptiFloat().size();
    for (unsigned iVar = 0; iVar < numVars; ++iVar)
    {
        const OptiVarF & var = GetOptiFloat().at(iVar);
        if (gcfgMan.cfgOpti->IsSearchFloatingPoint() && var.fp)
            continue;
        data.push_back(var.GetSpace().Data());
    }
    if (gcfgMan.cfgOpti->IsSearchRandom())
    {
        const long int maxSamples = gcfgMan.cfgOpti->OPTI_RANDOM_SAMPLES_NUM;
        const MultiDimIterTpl::VVt & dataT = data.T();
        MultiDimIterTpl::VVt dataNewT; // Shorten the data down to the requested number of samples
        /// TODO: Unit Test. Crucial element
        for (unsigned i = 0; i < maxSamples && i < dataT.size() ; ++i)
        {
            dataNewT.Add(dataT.at(i));
        }
        for (unsigned i = 0; i < dataNewT.size(); ++i)
        {
            Consume(dataNewT.at(i));
            if (gcfgMan.cfgOpti->OPTI_RANDOM_EARLY_STOP && IsEarlyStop())
            {
                LOGL << "Early stop. The recent variance changes were less than " << gcfgMan.cfgOpti->OPTI_RANDOM_MIN_DIFF_PROMILE << " ‰ after " << i << " iterations.\n";
                break;
            }
        }
    }
    else
    {
        multiDimIter.StartIteration(data, *this);
    }

    //Assertions::Throw("maxRows", data.size(), "Empty variable in OptimizerBase");
    //LOGL << "size = " << data.size() << Endl;



    for (OptiVarF v : GetOptiFloatResult())
    {
        for (const IPeriod * period : GetPeriods())
            v.StoreVariable(*period);
    }

    if (gcfgMan.cfgOpti->OPTI_VERBOSE && m_isVerbose)
        if (not gcfgMan.cfgOpti->IsXValid())
        {
            LOGL << Endl;
        }

    //cout << id << endl;
    PrintCurrentResults();
    PrintStatsSummary();
}

void OptimizerBase::PrintCurrentResults() const
{
    PrintArgs(GetOptiFloatResult());
    PrintStats();
}

void OptimizerBase::PrintArgs(const std::vector<OptiVarF> & args) const
{
    if (not gcfgMan.cfgOpti->IsXValid() && m_isVerbose)
    {
        const EnjoLib::Str id = GetPeriods().at(0)->GetSymbolPeriodId();
        for (OptiVarF v : args)
        {
            Osstream ostr;
            ostr << id << ": " << v.varId << ": ";
            IoManip::SetPrecision(ostr, 6) << v.GetVal() << Endl;
            LOGL << ostr.str();
        }
        LOGL << Endl;
    }
}

void OptimizerBase::UpdateGoalMax(float goal)
{
    m_goalMax = goal;
}

bool OptimizerBase::IsGoalReached(float goal) const
{
    if (goal > m_goalMax || (m_goalMax == 0))
    {
        return true;
    }
    return false;
}

float OptimizerBase::GetGoalMax() const
{
    return m_goalMax;
}

void OptimizerBase::AddGoal(float goal)
{
    m_goals.Add(goal);

    if (m_goals.size() > 1)
    {
        const double stdDevPerc = Statistical().GetRelatStdDev(m_goals, 100);
        m_goalsMod.Add(stdDevPerc);
    }
}

int OptimizerBase::GetGoalSize() const
{
    return m_goalsMod.size();
}

int OptimizerBase::GetSmoothing() const
{
    return 10;
}

void OptimizerBase::OnGoalReached(IOptimizable * optiCarrier)
{
    GetOptiFloatResult().clear();
    Osstream ostr;
    ostr << "OnGoalReached: " << GetGoalMax() << ", \tpars = ";
    for (OptiVarF * v : optiCarrier->GetOptiFloat().Vec())
    {
        ostr << v->GetVal() << " ";
        GetOptiFloatResult().push_back(*v);
    }
    LOGL << ostr.str() << Nl;
}

bool OptimizerBase::IsEarlyStop() const
{
    const int smooth = GetSmoothing();
    if (GetGoalSize() < smooth)
    {
        return false;
    }
    const double lastChange = GMat().Fabs(m_goalsMod.Diffs().Smooth(smooth).Last() * 1000);
    //LOGL << "lastChange = " << lastChange << "Min = " << gcfgMan.cfgOpti->OPTI_RANDOM_MIN_DIFF_PROMILE << Nl;
    return lastChange < gcfgMan.cfgOpti->OPTI_RANDOM_MIN_DIFF_PROMILE;
}

void OptimizerBase::PlotVariance() const
{
    const float scaleX = 1;
    const float scaleY = 0.5;
    const Formatters fmt;
    ELO
    GnuplotPlotTerminal1d(m_goalsMod.Diffs().Smooth(GetSmoothing()), "Variance changes (low values mean that no better solution can be found):", scaleX, scaleY);
    LOG << "Best  │  " << fmt.VecLabel() << "  │\n";
    LOG << fmt.FormatVar(m_goalMax) << " " << fmt.FormatVec(m_goals) << Endl;
    const DistribData & distrib = Distrib().GetDistrib(m_goals);
    if (distrib.IsValid())
    {
        GnuplotPlotTerminal2d(distrib.data, "Distribution of solutions (median must be > -1):", scaleX, scaleY);
    }
    //cout << "Changes abs = " << chg.sumAbsolute << " rel = " << chg.sumRelative << endl;
}

const std::vector<OptiVarF> & OptimizerBase::GetOptiFloat() const
{
    return GetImpl().m_optiFloat;
}
std::vector<OptiVarF> & OptimizerBase::GetOptiFloat()
{
    return GetImplRW().m_optiFloat;
}
std::vector<OptiVarF> & OptimizerBase::GetOptiFloatResult()
{
    return GetImplRW().m_optiFloatResult;
}
const std::vector<OptiVarF> & OptimizerBase::GetOptiFloatResult() const
{
    return GetImpl().m_optiFloatResult;
}

EnjoLib::Array<OptiVarF*> OptimizerBase::GetResult()
{
    std::vector<OptiVarF*> ret;
    for (OptiVarF & val : GetOptiFloatResult())
    {
        ret.push_back(&val);
    }
    return ret;
}

EnjoLib::VecD OptimizerBase::GetResultVec() const
{
    EnjoLib::VecD ret;
    for (const OptiVarF & val : GetOptiFloatResult())
    {
        ret.push_back(val.GetVal());
    }
    return ret;
}
