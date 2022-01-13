#include "OptiHigh.h"
#include "ISymbol.h"
#include "IPeriod.h"
#include "ISimulator.h"
#include "IOptimizable.h"
#include "OptimizerBase.h"
#include "OptiType.h"
#include "CrossValidCalc.h"
#include "ConfigGlob.h"
#include "ConfigMan.h"
#include "ConfigOpti.h"
#include "ConfigTF.h"
#include "ConfigTF2.h"
#include "OptimizerFactoryAbstract.h"

#include "OptiVar.h" /// TODO: Remove

#include <Ios/Osstream.hpp>
#include <Util/Str.hpp>
#include <Util/CoutBuf.hpp>
#include <Math/GeneralMath.hpp>
#include <Template/Array.hpp>

using namespace EnjoLib;

OptiHigh::OptiHigh(){}
OptiHigh::~OptiHigh(){}


EnjoLib::Str OptiHigh::WalkForwardOptiIndiv(const ISymbol & sym, const IPeriod & per, int iprogress, int totalSize, 
                                            const OptimizerFactoryAbstract & optiFact, 
                                            ISimulator & sim, const SimulatorFactoryAbstract & simFact) 
                                            const
{
    const GeneralMath gm;
    const CorPtr<IOptimizer> ioptiUpper = optiFact.Create(StartEnd());
    const IOptimizer & optiConst = *ioptiUpper;
    
    ProgressMonitHigh progressMonitHigh(20);
    ConfigOpti & confOpti = *gcfgMan.cfgOpti.get();
    const ConfigTF   & confTF   = *gcfgMan.cfgTF.get();
    const ConfigTF2  & confTF2  = *gcfgMan.cfgTF2.get();
    
    //Corrade::Containers::Pointer<IStrategy> stratPtr = fact.GetStrat().Create(stratType, period);

    CrossValidCalc cvc(optiConst, per, confOpti);
    
    const int iInitial = confOpti.OPTI_LAST ? -1 : 0;
    int i = iInitial;
    const OptiXValid & optiXvalidInitial = cvc.GetPass(i);
    OptiXValid optiXvalid = optiXvalidInitial;
    
    //const SimulatorFactory simFact;
    //Corrade::Containers::Pointer<ISimulatorStd> simul = simFact.CreateStandard(*stratPtr, 0, false, ConfigGlob().MIN_SCORE);
    //simul->SetAccumulator(&simAccum);
    
    do
    {
        EnjoLib::Osstream ossPassed;
        //ossPassed << "X-Valid - " +  period.GetSymbolPeriodId() << " " << gm.round(optiXvalid.xvalid.end / double(stratPtr->Len()) * 100) << "%";
        //progressMonitHigh.PrintProgressBarTime(iprogress, totalSize + 1, ossPassed.str(), false);
        // new
        ossPassed << "X-Valid - " +  per.GetSymbolPeriodId() << " " << gm.round(iprogress / double(totalSize) * 100) << "%";
        progressMonitHigh.PrintProgressBarTime(optiXvalid.xvalid.end, optiConst.Len(), ossPassed.str(), false);
        {
            //cout << "OPTI\n";
            //gcfg.OPTI_USE = false;
            //Optimizer opti(stratType, sym, period, fact.GetStrat(), optiXvalid.opti);
            //confOpti.SetOptimizer(OptiType::OPTI_TYPE_FIND); /// TODO: Make it implicit in the optiBase(); and make OPTI_TYPE_XVALID?
            CorPtr<IOptimizer> opti = optiFact.Create(optiXvalid.opti);
            //optiBase.SetStartEnd(optiXvalid.opti);
            (*opti)();
            {
                //{LOGL << "\nValid:\n";}
                const auto & res = opti->GetResult();
                //for (int i = 0; i < res.size(); ++i)
                {
                    //LOGL << res.at(i)->GetVal() << Nl;
                }
            }
            sim.ReinitOptiVars(opti->GetResultVec());
            sim.RunRaw(optiXvalid.xvalid);
        }
        //simul->RunRaw(optiXvalid.xvalid);
        //system("clear");
        //simAccum.PrintStats(false);
        if (confOpti.OPTI_LAST)
        {
            break;
        }
        optiXvalid = cvc.GetPass(++i);

    } while (optiXvalid.isValid);
    
    sim.Finalize();
    //ToolsMixed().SystemCallWarn("clear", __PRETTY_FUNCTION__);
    //simAccum.PrintStats(false);                           /// UWAGA TUTAJ
    //if (not confTF.SIMUL_MULTITHREAD)
    {
        //simul->PrintStats(false);  /// UWAGA TUTAJ
    }
    return "CrossValid::RunIndiv() ???";
}
