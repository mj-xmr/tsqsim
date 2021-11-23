#include "RegressionPars.h"

#include <Util/Pair.hpp>
#include <Math/GeneralMath.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/Str.hpp>
#include <Template/AlgoSTDThin.hpp>

using namespace EnjoLib;

const int RegressionPars::MIN_LEN = 3;

RegressionPars::RegressionPars(int past, int future, int degree)
: past(past)
, future(future)
, degree(degree)
{
    if (past < future)
        AlgoSTDThin().Swap(past, future);
}

RegressionPars RegressionPars::FromPast(const RegressionPars & pars, int past)
{
    RegressionPars loc(pars);
    loc.past = past;
    return loc;
}

RegressionPars RegressionPars::FromFuture(const RegressionPars & pars, int future)
{
    RegressionPars loc(pars);
    loc.future = future;
    return loc;
}

bool RegressionPars::IsValid() const
{
    if (past == 0)
        return false;
    if (future == 0 && past == 0)
        return false;

    return true;
}

bool RegressionPars::IsValidMinLen() const
{
    if (not IsValid())
        return false;

    return GetLen() >= MIN_LEN;
}

int RegressionPars::GetLen() const
{
    const int diff = past - future;
    return diff;
}

EnjoLib::Str RegressionPars::ToStr() const
{
    return EnjoLib::CharManipulations().ToStr(past) + " " + EnjoLib::CharManipulations().ToStr(future);
}
