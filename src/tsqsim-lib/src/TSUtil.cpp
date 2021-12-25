#include "TSUtil.h"

#include "TSFunType.h"
#include "TSFunFactory.h"
#include "TSInput.h"
#include "SimulatorTSFactory.h"

#include "ConfigMan.h"
#include "ConfigTS.h"

TSUtil::TSUtil(){}
TSUtil::~TSUtil(){}


CorPtr<ISimulatorTS> TSUtil::GetSim(const IPeriod & per) const
{
    const SimulatorTSFactory simFact;
    const TSFunFactory tsFunFact;

    const ConfigTS & confTS   = *gcfgMan.cfgTS.get();
    const TSFunType tsFunType = TSFunType::TXT; /// TODO: make user's choice
    const TSInput tsin(per, confTS);

    auto fun = tsFunFact.Create(tsin, tsFunType);
    CorPtr<ISimulatorTS> sim = simFact.CreateTS(tsin, *fun);
    sim->RunRaw();
    return sim;
}

