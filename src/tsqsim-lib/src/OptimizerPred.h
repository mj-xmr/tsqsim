#ifndef OPTIMIZERPRED_H
#define OPTIMIZERPRED_H

#include "OptimizerBase.h"
#include "StartEnd.h"
//#include "SimulatorCalcsDistrib.h"
#include "PredictorType.h"
#include "OptimizerFactoryAbstract.h"

#include <Util/StrFwd.hpp>
#include <Util/VecFwd.hpp>
class ISymbol;
class IOptimizable;
class IPeriod;
class ProfitsCalc;
class StartEnd;
class PredictorFactory;
//class PredictorType;
template<class T> class OptiVar;

class OptimizerPred : public OptimizerBase, public OptimizerFactoryAbstract
{
    public:
        OptimizerPred(const PredictorType & predType, const ISymbol & sym, const IPeriod & period, const PredictorFactory & fact, StartEnd startEndFrame = StartEnd());
        virtual ~OptimizerPred();

        CorPtr<IOptimizer> Create(const StartEnd & startEndFrame) const override; // OptimizerFactoryAbstract
        void Consume(const EnjoLib::VecD & data) override; // IMultiDimIterConsumerTpl
        int Len() const override; // IHasLen

    protected:
        STDFWD::vector<const IPeriod *> GetPeriods() const override;
        void PrintStats() const override;
        void PrintStatsSummary() const override;
    private:

        const ISymbol & m_sym;
        const IPeriod & m_period;
        const PredictorFactory & m_fact;
        //EnjoLib::Str m_outDir;

        PredictorType m_type;
        int m_len = 0;

};

#endif // OPTIMIZERPRED_H
