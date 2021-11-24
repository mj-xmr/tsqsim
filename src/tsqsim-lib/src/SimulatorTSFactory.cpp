#include "SimulatorTSFactory.h"
#include "SimulatorTS.h"
#include <Template/CorradePointer.h>

SimulatorTSFactory::SimulatorTSFactory()
{
}

SimulatorTSFactory::~SimulatorTSFactory()
{
}

Corrade::Containers::Pointer<ISimulatorTS> SimulatorTSFactory::CreateTS(const TSInput & tsin, const ITSFun & fun) const
{
    return  Corrade::Containers::Pointer<ISimulatorTS> (new SimulatorTS(tsin, fun));
}
