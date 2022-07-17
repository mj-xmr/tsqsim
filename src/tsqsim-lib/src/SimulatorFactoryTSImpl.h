#ifndef SIMULATORFACTORYTSIMPL_H
#define SIMULATORFACTORYTSIMPL_H

#include <SimulatorFactoryAbstract.h>
#include "TSInput.h"

class SimulatorFactoryTSImpl : public SimulatorFactoryAbstract
{
    public:
        SimulatorFactoryTSImpl();
        virtual ~SimulatorFactoryTSImpl();

        CorPtr<ISimulator> Create(const EnjoLib::Str & params) const override;

    protected:

    private:
};

#endif // SIMULATORFACTORYTSIMPL_H
