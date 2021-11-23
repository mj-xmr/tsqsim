#include "IOptimizable.h"
#include "OptiVar.h"
#include "OptiVarVec.h"

#include <Statistical/Assertions.hpp>

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
        vecOwn.atw(i) = opti.at(i);
    }
}
