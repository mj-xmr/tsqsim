#include "TSUtil.h"

#include "TSFunType.h"
#include "TSFunFactory.h"
#include "TSInput.h"
#include "SimulatorTSFactory.h"
#include "PredictorType.h"
#include "MatplotLine.h"

#include "ConfigMan.h"
#include "ConfigTS.h"
#include "ConfigSym.h"

#include <Util/CoutBuf.hpp>
#include <Util/TimerChrono.hpp>

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
    return CorPtr<ISimulatorTS>(sim.release());
}

CorPtr<ISimulatorTS> TSUtil::GetSimBenchmark(const IPeriod & per, const PredictorType & predType, const EnjoLib::Str & scriptName, const StartEnd & startEndFrame) const
{
    const SimulatorTSFactory simFact;
    const TSFunFactory tsFunFact;

    ConfigTS & confTS   = *gcfgMan.cfgTS.get();
    const TSFunType tsFunType = TSFunType::TXT; /// TODO: make user's choice
    confTS.SetPredType(predType);
    confTS.SetScriptNamePy(scriptName);
    const TSInput tsin(per, confTS);

    CorPtr<ITSFun> fun = tsFunFact.Create(tsin, tsFunType);
    CorPtr<ISimulatorTS> sim = simFact.CreateTS(tsin, *fun);
    const EnjoLib::TimerChrono timer;
    sim->RunRaw(startEndFrame);
    const double seconds = timer.ToNowMilliseconds() / 1000.0;
    
    ELO
    LOG << "Benchmarked " << (scriptName.size() ? scriptName : "Native C++") << EnjoLib::Nl;
    LOG << "Time taken = " << seconds << "s\n";
    
    return CorPtr<ISimulatorTS>(sim.release());
}

CorPtr<ISimulatorTS> TSUtil::GetSimDontRun(const IPeriod & per, const StartEnd & startEndFrame) const
{
    const SimulatorTSFactory simFact;
    const TSFunFactory tsFunFact;

    const ConfigTS & confTS   = *gcfgMan.cfgTS.get();
    const TSFunType tsFunType = TSFunType::XFORM; /// TODO: make user's choice
    const TSInput tsin(per, confTS);

    CorPtr<ITSFun> fun = tsFunFact.Create(tsin, tsFunType);
    CorPtr<ISimulatorTS> sim = simFact.CreateTS(tsin, *fun);
    return CorPtr<ISimulatorTS>(sim.release());
}

CorPtr<ISimulatorTS> TSUtil::GetSim(const IPeriod & per, const ITSFun & tsFun, const StartEnd & startEndFrame) const
{
    const SimulatorTSFactory simFact;

    const ConfigTS & confTS   = *gcfgMan.cfgTS.get();
    const TSInput tsin(per, confTS);

    CorPtr<ISimulatorTS> sim = simFact.CreateTS(tsin, tsFun);
    sim->RunRaw(startEndFrame);
    return CorPtr<ISimulatorTS>(sim.release());
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
    return CorPtr<ISimulatorTS>(sim.release());
}
