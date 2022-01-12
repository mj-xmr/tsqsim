#ifndef SIMULATORTSFACTORYIMPL_H
#define SIMULATORTSFACTORYIMPL_H

#include "SimulatorFactoryAbstract.h"

class TSInput;
class ITSFun;
class IPredictor;

class SimulatorTSFactoryImpl : public SimulatorFactoryAbstract
{
    public:
        SimulatorTSFactoryImpl(const TSInput & tsin, const ITSFun & fun);
        virtual ~SimulatorTSFactoryImpl();
        
        CorPtr<ISimulator> Create() const override;

    protected:

    private:
        const TSInput & m_tsin;
        const ITSFun & m_fun;
};

#endif // SIMULATORTSFACTORYIMPL_H
