#ifndef SIMULATORFACTORYABSTRACT_H
#define SIMULATORFACTORYABSTRACT_H

#include "ISimulator.h"
#include <Template/Factory.hpp>
#include <Template/SafePtr.hpp>
//class IStrategy;
#include "IStrategy.h" /// TODO: Code smell

/// TODO: Propagate the idea to other abstract factories
class SimulatorFactoryAbstract : public EnjoLib::Factory<ISimulator>
{
    public:
        SimulatorFactoryAbstract();
        virtual ~SimulatorFactoryAbstract();

        /// TODO: This is a code smell:
        /// TODO: Add custom deleter: EMPTY
        //EnjoLib::SafePtrNullable<IStrategy> strat;
        IStrategy * strat = nullptr;
        float progress = 0;
        float simulatorMinScore = 0;
        bool isTraining = false;
        bool plotSim = false;
        EnjoLib::Str outDir;

    protected:

    private:
};

#endif // SIMULATORFACTORYABSTRACT_H
