#ifndef SIMULATORTS_H
#define SIMULATORTS_H

#include "ISimulatorTS.h"
#include <Util/VecD.hpp>
#include <Util/Tuple.hpp>

class ISimulatorAccum;
class IPeriod;
class ITSFun;
class TSInput;
class TSRes;
class ConfigTS;
enum class PredictorType;

class SimulatorTS : public ISimulatorTS
{
    public:
        SimulatorTS(const TSInput & tsin, const ITSFun & fun);
        virtual ~SimulatorTS();
        void Run() override;
        //void Collect() override;
        void RunRaw(const StartEnd & startEndFrame = StartEnd()) override;

        const EnjoLib::VecD & GetOutputSeries(const PredictorOutputType & type) const override;

        using Inp = EnjoLib::Tuple<const IDataProvider *, const ITSFun *, int>;
        static TSRes IterBet(const Inp & ele);

        STDFWD::vector<TSRes> GetRets(const STDFWD::vector<Inp> & inp) const;
        EnjoLib::VecD GetRetsFiltered(const STDFWD::vector<Inp> & inp) const;
        STDFWD::vector<TSRes> GetReconstruction(const ITSFun * fun, const EnjoLib::VecD & inp, double initial) const;
        EnjoLib::VecD GetReconstructionFiltered(const STDFWD::vector<TSRes> & input) const;

        TSRes Reconstr(const ITSFun * fun, const double val) const;
        EnjoLib::VecD Pred(const EnjoLib::VecD & data, const PredictorType & type) const;

        bool VecEqual(const EnjoLib::VecD & data1, const EnjoLib::VecD & data2) const; /// TODO: Extractg

    protected:

    private:
        void PrintResults();
        void PrintExperimental() const;
        void PrintReportSingleThreaded(const EnjoLib::VecD & data, const EnjoLib::Str & descr, const STDFWD::vector<const EnjoLib::VecD *> & plots) const;

        const TSInput & m_tsin;
        const IPeriod & m_per;
        const ITSFun & m_fun;
        const ConfigTS & m_cfgTS;

        ISimulatorAccum * m_accum = nullptr;

        double sum = 0;
        double m_meanChange = 0;
        EnjoLib::VecD m_balance;
        EnjoLib::VecD m_rets;
        EnjoLib::VecD m_preds;
        EnjoLib::VecD m_predsTrue;
        EnjoLib::VecD m_predsBaseline;
        EnjoLib::VecD m_reconstr;
        EnjoLib::VecD m_reconstrPred;
};

#endif // SIMULATORTS_H
