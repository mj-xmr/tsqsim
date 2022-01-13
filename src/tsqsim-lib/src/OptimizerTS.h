#ifndef OPTIMIZERTS_H
#define OPTIMIZERTS_H

#include "OptimizerBase.h"
#include "StartEnd.h"
//#include "SimulatorCalcsDistrib.h"
#include "TSFunType.h"

#include <Util/Str.hpp>
#include <Util/VecD.hpp>
class ISymbol;
class IOptimizable;
class IPeriod;
class ProfitsCalc;
class StartEnd;
class TSFunFactory;
template<class T> class OptiVar;

class OptimizerTS : public OptimizerBase
{
    public:
        OptimizerTS(const TSFunType & funType, const ISymbol & sym, const IPeriod & period, const TSFunFactory & funFact, StartEnd startEndFrame = StartEnd());
        virtual ~OptimizerTS();

        void Consume(const EnjoLib::VecD & data) override; // IMultiDimIterConsumerTpl

    protected:
        STDFWD::vector<const IPeriod *> GetPeriods() const override;
        void PrintStats() const override;
        void PrintStatsSummary() const override;
    private:
        const ISymbol & m_sym;
        const IPeriod & m_period;
        const TSFunFactory & m_funFact;

        TSFunType m_funType;
};

#endif // OPTIMIZER_H
