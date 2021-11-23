#include "OptiVar.h"
#include "OptimizerUtils.h"
#include "IDataProvider.h"
#include "ConfigMan.h"
#include "ConfigOpti.h"
#include "ConfigGlob.h"

#include <Ios/Ofstream.hpp>
#include <Ios/Ifstream.hpp>
#include <Math/RandomMath.hpp>
#include <Util/Str.hpp>
#include <Util/Except.hpp>
#include <Util/FileUtils.hpp>
#include <Util/StackTrace.hpp>
#include <Util/CoutBuf.hpp>

using namespace std;
using namespace EnjoLib;

OptiVarF::OptiVarF(const IDataProvider & period, const EnjoLib::Str & varId, bool fp, const EnjoLib::VecF & valDefaultMinMaxStep, bool multiplyStep)
: OptiVarF(period, varId, fp
          , valDefaultMinMaxStep.at(0)
          , valDefaultMinMaxStep.at(1)
          , valDefaultMinMaxStep.at(2)
          , valDefaultMinMaxStep.at(3)
          , multiplyStep
          )
{
    //Init();
}

OptiVarF::OptiVarF(const IDataProvider & period, const EnjoLib::Str & varId, bool fp, float valDefault, float valMin, float valMax, float step, bool multiplyStep)
: m_per(&period)
, varId(varId)
, val(valDefault)
, valMin(valMin)
, valMax(valMax)
, step(step)
, multiplyStep(multiplyStep)
, fp(fp)
{
    Init();
}


void OptiVarF::Init()
{
    bool verbose = false;
    //verbose = true;
    FileUtils fu;
    OptimizerUtils ou;

    bool release = gcfgMan.cfgOpti->OPTI_USE_RELEASE;
    const char * varIdCstr = varId.c_str();
    //cout << "Using " << (release ? "Release" : "Debug") << " var.\n";
    //bool release = true;
    const EnjoLib::Str baseDir = ou.GetVarBaseDir(release);
    if (not fu.DirExists(baseDir))
        throw EnjoLib::ExceptRuntimeError(STRACE_THROW("Not found dir = " + baseDir));
    if (gcfg.OPTI_USE)
    {
        const EnjoLib::Str & pathVar = ou.GetVarPath(*m_per, varId, release);
        if (fu.FileExists(pathVar))
        {
            if (verbose)
            {
                LOGL << "OptiVar: FOUND! = " << pathVar  << Nl;
            }

            Ifstream f(pathVar);
            if (not (f >> val))
                throw EnjoLib::ExceptRuntimeError(STRACE_THROW("Incompatible format at = " + pathVar));
            else
            {
                if (verbose)
                {
                    LOGL << "OptiVar: FOUND! = " << pathVar << ", val = " << val << Nl;
                }
                    

                f.close(); // For debugging val
            }
        }
        else
        {
            if (verbose)
            {
                //cout << "OptiVar: Not found :( = " << pathVar  << endl;
            }

        }
    }
    //cout << "Opti var '" << varId << "' = " << val << endl;
}

/// TODO: inject config! and OptiVarMan



OptiVarF::~OptiVarF() {}


EnjoLib::VecF OptiVarF::GetSpace() const
{
    EnjoLib::VecF ret;
    if (gcfgMan.cfgOpti->IsSearchFloatingPoint() && fp)
    {
        ret.Add(valMin);
        ret.Add(valMax);
    }
    else
    {
        if (gcfgMan.cfgOpti->IsSearchRandom())
        {
            ret = GetSpaceRandom(valMin, valMax, gcfgMan.cfgOpti->OPTI_RANDOM_SAMPLES_NUM);
        }
        else
        {
            ret = GetSpaceDiscrete(valMin, valMax, step, multiplyStep);
        }
    }
    return ret;
}

EnjoLib::VecF OptiVarF::GetSpaceDiscrete(float valMin, float valMax, float step, bool multiplyStep)
{
    EnjoLib::VecF ret;
    if (multiplyStep)
    {
        for (float val = valMin; val <= valMax; val *= step)
            ret.push_back(val);
    }
    else
    {
        for (float val = valMin; val <= valMax; val += step)
            ret.push_back(val);
    }
    return ret;
}

EnjoLib::VecF OptiVarF::GetSpaceRandom(float valMin, float valMax, int number)
{
    EnjoLib::VecF ret;
    const RandomMath rmath;
    
    for (int i = 0; i < number; ++i)
    {
        const double rnd = rmath.Rand(valMin, valMax);
        ret.push_back(rnd);
    }
    return ret;
}

void OptiVarF::StoreVariable(const IDataProvider & period) const
{
    FileUtils fu;
    OptimizerUtils ou;
    bool release = gcfgMan.cfgOpti->OPTI_USE_RELEASE;;
    const EnjoLib::Str & baseDir = ou.GetVarBaseDir(release);
    const EnjoLib::Str & dir = ou.GetVarDir(period, release);
    fu.CreateDirIfNotExistsLinux(baseDir);
    fu.CreateDirIfNotExistsLinux(dir);
    const EnjoLib::Str & pathVar = ou.GetVarPath(period, varId, release);
    Ofstream f(pathVar);
    f << val << '\n';
}

//template class OptiVarF;
//template class OptiVar<bool>;
//template class OptiVar<int>;
