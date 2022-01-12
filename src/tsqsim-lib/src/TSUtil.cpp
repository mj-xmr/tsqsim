#include "TSUtil.h"

#include "TSFunType.h"
#include "TSFunFactory.h"
#include "TSInput.h"
#include "SimulatorTSFactory.h"

#include "ConfigMan.h"
#include "ConfigTS.h"

TSUtil::TSUtil(){}
TSUtil::~TSUtil(){}


CorPtr<ISimulatorTS> TSUtil::GetSim(const IPeriod & per, const StartEnd & startEndFrame) const
{
    const SimulatorTSFactory simFact;
    const TSFunFactory tsFunFact;

    const ConfigTS & confTS   = *gcfgMan.cfgTS.get();
    const TSFunType tsFunType = TSFunType::TXT; /// TODO: make user's choice
    const TSInput tsin(per, confTS);

    CorPtr<ITSFun> fun = tsFunFact.Create(tsin, tsFunType);
    CorPtr<ISimulatorTS> sim = simFact.CreateTS(tsin, *fun);
    sim->RunRaw(startEndFrame);
    return sim;
}

CorPtr<ISimulatorTS> TSUtil::GetSim(const IPeriod & per, const ITSFun & tsFun, const StartEnd & startEndFrame) const
{
    const SimulatorTSFactory simFact;

    const ConfigTS & confTS   = *gcfgMan.cfgTS.get();
    const TSInput tsin(per, confTS);

    CorPtr<ISimulatorTS> sim = simFact.CreateTS(tsin, tsFun);
    sim->RunRaw(startEndFrame);
    return sim;
}

CorPtr<ISimulatorTS> TSUtil::GetSimPred(const IPeriod & per, const EnjoLib::VecD & opti, const StartEnd & startEndFrame) const
{
    const SimulatorTSFactory simFact;
    const TSFunFactory tsFunFact;

    const ConfigTS & confTS   = *gcfgMan.cfgTS.get();
    const TSFunType tsFunType = TSFunType::TXT; /// TODO: make user's choice
    const TSInput tsin(per, confTS);

    CorPtr<ITSFun> fun = tsFunFact.Create(tsin, tsFunType);
    CorPtr<ISimulatorTS> sim = simFact.CreateTS(tsin, *fun);
    fun->SetSilent();
    sim->SetSilent();
    sim->ReinitOptiVars(opti);
    sim->RunRaw(startEndFrame);
    return sim;
}
