#ifndef OptimizerBase_H
#define OptimizerBase_H

#include "IOptimizer.h"
#include "StartEnd.h"
#include "IHasLen.h"
#include <Math/MultiDimIter/IMultiDimIterConsumerTpl.hpp>
//#include <Math/MaxMinFindF.hpp>
#include <Util/ProgressMonitHigh.hpp>
#include <Util/Pimpl.hpp>
#include <Util/VecD.hpp>
#include <Template/ArrayFwd.hpp>

class IOptimizable;
class IPeriod;
class IDataProvider;
class OptiVarF;

class OptimizerBase : public IOptimizer
{
    public:
        OptimizerBase(const StartEnd & startEndFrame);
        virtual ~OptimizerBase();

        void operator()() override;
        void SetSilent() override { m_isVerbose = false; };
        EnjoLib::Array<OptiVarF*> GetResult() override;
        EnjoLib::VecD GetResultVec() const override;

    protected:
        void AddGoal(float goal);
        void InitFromOptimizable(IOptimizable & opti, const IDataProvider & per);
        int GetGoalSize() const;
        virtual bool IsEarlyStop() const;
        void OnGoalReached(IOptimizable * optiCarrier);

        virtual STDFWD::vector<const IPeriod *> GetPeriods() const = 0;
        virtual void PrintStats() const = 0;
        virtual void PrintStatsSummary() const {}
        virtual int GetSmoothing() const;

        const STDFWD::vector<OptiVarF> & GetOptiFloat() const;
        const STDFWD::vector<OptiVarF> & GetOptiFloatResult() const;
        STDFWD::vector<OptiVarF> & GetOptiFloat();
        STDFWD::vector<OptiVarF> & GetOptiFloatResult();

        float GetGoalMax() const;
        bool IsGoalReached(float goal) const;
        void UpdateGoalMax(float goal);

        OptiVarF * FindVarCurrent(IOptimizable & opt, unsigned iVar) const;
        void PrintCurrentResults() const;
        void PrintArgs(const STDFWD::vector<OptiVarF> & args) const;
        void PlotVariance() const;
        int GetNumCombinations(IOptimizable & opt) const;

        int m_numCombis = 0;
        bool m_isVerbose = true;
        mutable int m_iter = 0;

        EnjoLib::Timer m_timer;
        EnjoLib::ProgressMonitHigh m_progressMonitHigh;
        EnjoLib::Str m_outDir;
        StartEnd m_startEndFrame;

    private:
        mutable int m_prevStringSize = 0;
        float m_goalMax = 0;
        EnjoLib::VecD m_goals;
        EnjoLib::VecD m_goalsMod;

        PIMPL_CPY
};

#endif // OptimizerBaseTF_H
