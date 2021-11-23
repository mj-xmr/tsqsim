#include "RegOptiBase.h"
#include "RegressionPars.h"

RegOptiBase::RegOptiBase()
{}


int RegOptiBase::GetPast(const RegressionPars & reg) const
{
    return GetPast(reg.future);
}

int RegOptiBase::GetPast(int future) const
{
    if (not IsValid())
    {
        return 0;
    }
    const int past = GetDiffPastFuture() + future;
    return past;
}

bool RegOptiBase::IsValid() const
{
    return GetDiffPastFuture() >= 0;
}
