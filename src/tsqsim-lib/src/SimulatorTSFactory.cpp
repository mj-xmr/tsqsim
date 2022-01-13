#include "SimulatorTSFactory.h"
#include "SimulatorTS.h"
#include <Template/CorradePointer.h>

SimulatorTSFactory::SimulatorTSFactory()
{
}

SimulatorTSFactory::~SimulatorTSFactory()
{
}

CorPtr<ISimulatorTS> SimulatorTSFactory::CreateTS(const TSInput & tsin, const ITSFun & fun) const
{
    return  CorPtr<ISimulatorTS> (new SimulatorTS(tsin, fun));
}
