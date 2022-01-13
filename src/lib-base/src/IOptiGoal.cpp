#include "IOptiGoal.h"

IOptiGoal::IOptiGoal()
{
    //ctor
}

IOptiGoal::~IOptiGoal()
{
    //dtor
}

bool IOptiGoal::IsGoalReached(const ProfitsCalc & profits, float previous) const
{
    if (GetGoal(profits) > previous)
    {
        return true;
    }
    return false;
}
