#ifndef TSUTIL_H
#define TSUTIL_H

#include "ISimulatorTS.h"
#include "StartEnd.h"
#include <Util/VecFwd.hpp>
#include <Util/Str.hpp>
#include <Template/IIterable.hpp>
#include <Template/CorradePointerFwd.h>

class ITSFun;
class IPeriod;
class IPredictor;
class OptiVarF;
enum class PredictorType;

class TSUtil
{
    public:
        TSUtil();
        virtual ~TSUtil();

        CorPtr<ISimulatorTS> GetSim(const IPeriod & per, const StartEnd & startEndFrame = StartEnd()) const;
        CorPtr<ISimulatorTS> GetSimBenchmark(const IPeriod & per, const PredictorType & predType, const EnjoLib::Str & scriptName = "", const StartEnd & startEndFrame = StartEnd()) const;
        CorPtr<ISimulatorTS> GetSimDontRun(const IPeriod & per, const StartEnd & startEndFrame = StartEnd()) const;
        CorPtr<ISimulatorTS> GetSim(const IPeriod & per, const ITSFun & tsFun, const StartEnd & startEndFrame = StartEnd()) const;
        CorPtr<ISimulatorTS> GetSimPred(const IPeriod & per, const EnjoLib::VecD & opti, const StartEnd & startEndFrame = StartEnd()) const;

    protected:

    private:
};

#endif // TSUTIL_H
