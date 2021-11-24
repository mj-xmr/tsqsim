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

class SimulatorTS : public ISimulatorTS
{
    public:
        SimulatorTS(const TSInput & tsin, const ITSFun & fun);
        virtual ~SimulatorTS();
        void Run() override;
        //void Collect() override;
        void RunRaw(const StartEnd & startEndFrame = StartEnd()) override;

        using Inp = EnjoLib::Tuple<const IDataProvider *, const ITSFun *, int>;
        static TSRes IterBet(const Inp & ele);

    protected:

    private:
        void PrintResults();
        void PrintExperimental() const;

        const TSInput & m_tsin;
        const IPeriod & m_per;
        const ITSFun & m_fun;

        ISimulatorAccum * m_accum = nullptr;

        double sum = 0;
        double m_meanChange = 0;
        EnjoLib::VecD m_balance;
        EnjoLib::VecD m_rets;
};

#endif // SIMULATORTS_H
