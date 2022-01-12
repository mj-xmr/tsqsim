#ifndef SIMULATORFACTORYABSTRACT_H
#define SIMULATORFACTORYABSTRACT_H

#include "ISimulator.h"
#include <Template/Factory.hpp>

class SimulatorFactoryAbstract : public EnjoLib::Factory<ISimulator>
{
    public:
        SimulatorFactoryAbstract();
        virtual ~SimulatorFactoryAbstract();

    protected:

    private:
};

#endif // SIMULATORFACTORYABSTRACT_H
