#ifndef OPTISUBJECTPRED_H
#define OPTISUBJECTPRED_H

#include "IOptiSubject.h"
#include "StartEnd.h"

#include <STD/Vector.hpp>

class ISymbol;
class IPeriod;
class PredictorFactory;
enum class PredictorType;

class OptiSubjectPred : public IOptiSubject
{
    public:
        OptiSubjectPred(const ISymbol & sym, const IPeriod & period, 
                        const PredictorFactory & fact, const PredictorType & type, 
                        const STDFWD::vector<OptiVarF> & optiFloat, 
                        const StartEnd & startEndFrame, const EnjoLib::VecD & iterData);
        virtual ~OptiSubjectPred();
        
        double GetGoal() const;
        
        EnjoLib::FP Get(const EnjoLib::FP * in, int n) override;
        EnjoLib::VecD GetStart() const override;
        EnjoLib::VecD GetStep() const override;
        EnjoLib::Array<EnjoLib::OptiMultiSubject::Bounds> GetBounds() const override;
        
        STDFWD::vector<OptiVarF> GetOptiVarsResult() override { return m_optiFloatResult; }

    protected:

    private:
        const ISymbol & m_sym;
        const IPeriod & m_period;
        const PredictorFactory & m_fact;
        const PredictorType & m_type;
        StartEnd m_startEndFrame;
        
        std::vector<OptiVarF> m_optiFloat;
        std::vector<OptiVarF> m_optiFloatResult;

        EnjoLib::VecD m_iterData;

        float m_sumMax = 0;
};

#endif // OPTISUBJECTPRED_H
