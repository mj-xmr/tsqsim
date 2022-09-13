#ifndef SIMULATORTS_H
#define SIMULATORTS_H

#include "ISimulatorTS.h"
#include "TSXformDataMan.h"
#include <Util/VecD.hpp>
#include <Util/Str.hpp>
#include <Util/Tuple.hpp>
#include <Statistical/MatrixFwd.hpp>
#include <Template/CorradePointer.h>

class ISimulatorAccum;
class IPeriod;
class ITSFun;
class TSInput;
class TSRes;
class ConfigTS;
class IPredictor;
enum class PredictorType;

class SimulatorTS : public ISimulatorTS
{
    public:
        SimulatorTS(const TSInput & tsin, const ITSFun & fun);
        virtual ~SimulatorTS();

        ISimulator * CloneRaw() const override;

        void Run() override;
        //void Collect() override;
        void RunRaw(const StartEnd & startEndFrame = StartEnd()) override;

        const EnjoLib::VecD & GetOutputSeries(const PredictorOutputType & type) const override;
        float GetScorePred() const override;
        float GetScoreStationarity() const override;
        void SetSilent() override;
        void PrintOpti() const override;
        //void ReinitOptiVars(const EnjoLib::IIterable<OptiVarF *> & opti) override;
        void ReinitOptiVars(const EnjoLib::VecD & optiVars) override;
        EnjoLib::Str GetLogs() const override;
        void AddLogs(const EnjoLib::Str & logs) const override;

        using Inp = EnjoLib::Tuple<const IDataProvider *, const ITSFun *, int>;
        static TSRes IterBet(const Inp & ele);

        STDFWD::vector<TSRes> GetRets(const STDFWD::vector<Inp> & inp) const;
        TSXformDataMan GetRetsFiltered(const STDFWD::vector<Inp> & inp) const;
        STDFWD::vector<TSRes> GetReconstruction(const ITSFun * fun, const EnjoLib::VecD & inp, const EnjoLib::Matrix & lost) const;
        EnjoLib::VecD GetReconstructionFiltered(const STDFWD::vector<TSRes> & input) const;

        TSRes Reconstr(const ITSFun * fun, const double val) const;
        EnjoLib::VecD Pred(const PredictorType & type) const;
        EnjoLib::VecD PredAlgo(const IPredictor & pred) const;
        EnjoLib::VecD PredCommon(const IPredictor & predAlgo, const EnjoLib::VecD & data) const;
        EnjoLib::VecD GetSeasonal(int period = 24, int averages = 26) const;
        EnjoLib::VecD GetMA(int period = 100) const;
        EnjoLib::VecD GetMA2Diff(const EnjoLib::VecD & maa, size_t period = 100) const;
        void OutputVariable(const EnjoLib::VecD & var, const EnjoLib::Str & name) const;
        void OutputVariable(double var, const EnjoLib::Str & name) const;

    protected:
        bool IsVerbose() const;

    private:
        void PrintResults() const;
        void PrintExperimental() const;

        const TSInput & m_tsin;
        const IPeriod & m_per;
        const ITSFun & m_fun;
        const ConfigTS & m_cfgTS;

        ISimulatorAccum * m_accum = nullptr;

        //double sum = 0;
        double m_meanChange = 0;
        float m_goalPred = 0;
        float m_goalStationarity = 0; /// TODO: A separate simulator for this?
        bool m_silent = false;
        EnjoLib::VecD m_balance;
        EnjoLib::VecD m_original;
        EnjoLib::VecD m_preds;
        EnjoLib::VecD m_predsTrue;
        EnjoLib::VecD m_predsBaseline;
        EnjoLib::VecD m_reconstr;
        EnjoLib::VecD m_reconstrPred;
        EnjoLib::VecD m_reconstrPredBase;
        EnjoLib::VecD m_predsPlot;
        EnjoLib::VecD m_seasonal;
        EnjoLib::VecD m_ma;
        EnjoLib::VecD m_ma2Diff;
        EnjoLib::VecD m_ma2DiffNoSeasonal;
        mutable EnjoLib::Str m_logs;

        CorPtr<IPredictor> m_ppred;

        TSXformDataMan m_dataMan;
};

#endif // SIMULATORTS_H
