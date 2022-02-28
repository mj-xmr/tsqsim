#include "SimulatorFactoryTSImpl.h"
#include "TSUtil.h"

#include <Statistical/Assertions.hpp>

SimulatorFactoryTSImpl::SimulatorFactoryTSImpl()
{
    //ctor
}

SimulatorFactoryTSImpl::~SimulatorFactoryTSImpl()
{
    //dtor
}

CorPtr<ISimulator> SimulatorFactoryTSImpl::Create(const EnjoLib::Str & params) const
{
    CorPtr<ISimulatorTS> simTS = TSUtil().GetSimDontRun(strat->GetPeriod());
    return CorPtr<ISimulator>(simTS.release());

    EnjoLib::Assertions::Throw("Factory Create not implemented", "");
    throw "asd";
}
