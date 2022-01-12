#ifndef PREDICTORBASE_HPP
#define PREDICTORBASE_HPP

#include "IPredictor.h"
#include "OptiVar.h"


class PredictorBase : public IPredictor
{
    public:
        PredictorBase(const IDataProvider & dat, const EnjoLib::Str & lagName);
        virtual ~PredictorBase();
        
        OptiVarVec GetOptiFloat() override; // IOptimizable
        int Len() const override; // IHasLen
        
        const IDataProvider & GetDat() const;
        const OptiVarF & GetLag1() const;

    protected:
        void AddOptiVar(OptiVarF & var);
        void AddOptiVars(IOptimizable & iopt);
        OptiVarVec & GetOptiFloatRW();

    private:
        const IDataProvider & m_dat;
        
        EnjoLib::SafePtrFast<OptiVarVec> m_optiFloats;
        OptiVarF m_lagMain;
};

#endif // PREDICTORBASE_HPP
