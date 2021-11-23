#include "VecFilters.h"
#include "VecFiltersTpl.h"
#include <Util/VecD.hpp>
#include <Util/VecF.hpp>

#include <Math/MaxMinFind.hpp>

using namespace EnjoLib;

VecFilters::VecFilters(){}

EnjoLib::VecF VecFilters::Smooth(const EnjoLib::VecF & inp, int smoothPer) const
{
    return VecF(VecFiltersTpl().Smooth(inp.Data(), smoothPer).Data());
}

VecD VecFilters::Smooth(const VecD & inp, int smoothPer) const
{
    return VecFiltersTpl().Smooth(inp, smoothPer);
}

EnjoLib::VecF VecFilters::VectorDToVec(const EnjoLib::VecD & evec) const
{
    EnjoLib::VecF ret;
    ret.reserve(evec.size());
    for (const auto & elem : evec)
        ret.push_back(elem);
    return ret;
}

VecD VecFilters::Changes(const VecD & inp) const
{
    EnjoLib::MaxMinFind<double> mmf;
    for (auto var : inp) mmf.UpdateMaxMin(var);
    const double len = mmf.GetMax() - mmf.GetMin();

    VecD changes;
    for (int i = 1; i < int(inp.size()); ++i)
    {
        const double vCurr = inp.at(i);
        const double vPrev = inp.at(i-1);
        const double change = vCurr - vPrev;
        const double changeRel = change / len;
        changes.push_back(changeRel);
    }
    return changes;
}
