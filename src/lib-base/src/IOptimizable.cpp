#include "IOptimizable.h"
#include "OptiVar.h"
#include "OptiVarVec.h"
#include "ConfigMan.h"
#include "ConfigOpti.h"

#include <Util/CoutBuf.hpp>
#include <Statistical/Assertions.hpp>

using namespace EnjoLib;

IOptimizable::IOptimizable(){}
IOptimizable::~IOptimizable(){}

void IOptimizable::ReinitVars()
{
    for (OptiVarF * var : GetOptiFloat().Vec())
    {
        var->Init();
    }
}

void IOptimizable::UpdateOptiVars(const EnjoLib::IIterable<OptiVarF *> & opti)
{
    auto vecOwn = GetOptiFloat().Vec();
    EnjoLib::Assertions::SizesEqual(vecOwn.size(), opti.size(), "IOptimizable::UpdateOptiVars(const IOptimizable & opti)");
    for (size_t i = 0; i < opti.size() && i < vecOwn.size(); ++i)
    {
        //LOGL << "IOptimizable::UpdateOptiVars: " << opti.at(i)->GetVal() << Nl;
        vecOwn.atw(i)->SetVal(opti.at(i)->GetVal());
    }
}


void IOptimizable::UpdateOptiVars(const EnjoLib::VecD & optiVarsLoopData)
{
    EnjoLib::Array<OptiVarF *> vopti = GetOptiFloat().Vec();
    //OptiVarF * varReal = FindVarCurrent(strat, iVar);
    for (unsigned iVar = 0; iVar < optiVarsLoopData.size(); ++iVar)
    {
        const float val = optiVarsLoopData[iVar];
        OptiVarF * varReal = vopti.at(iVar);
        if (gcfgMan.cfgOpti->IsSearchFloatingPoint() && varReal->fp)
        {
            //continue; /// TODO: Reconsider later on
        }
        varReal->SetVal(val);
    }
}

void IOptimizable::PrintOptiVars(const EnjoLib::Str & context)
{
    ELO
    LOG << "Opti vars from: " << context << ": ";
    for (OptiVarF * var : GetOptiFloat().Vec())
    {
        LOG << var->GetVal() << ", ";
    }
    LOG << EnjoLib::Nl;
}

EnjoLib::VecD IOptimizable::GetOptiVec()
{
    EnjoLib::VecD ret;
    for (const OptiVarF * var : GetOptiFloat().Vec())
    {
        ret.Add(var->GetVal());
    }
    return ret;
}