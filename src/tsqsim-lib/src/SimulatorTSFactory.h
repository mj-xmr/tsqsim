#ifndef SIMULATORTSFACTORY_H
#define SIMULATORTSFACTORY_H

#include "ISimulatorTS.h"
#include <Template/CorradePointerFwd.h>

class TSInput;
class ITSFun;
class SimulatorTSFactory
{
    public:
        SimulatorTSFactory();
        virtual ~SimulatorTSFactory();

        CorPtr<ISimulatorTS> CreateTS(const TSInput & tsin, const ITSFun & fun) const;


    protected:

    private:
};

#endif // SIMULATORBETFACTORY_H
