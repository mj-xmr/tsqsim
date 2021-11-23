#include "MinMax.h"

MinMax::MinMax()
: MinMax(0, 0)
{}

MinMax::MinMax(float a, float b)
: min(a)
, max(b)
{
    if (min > max)
    {
        float c(a); min=b; max=c; // swap
    }
}

MinMax::~MinMax(){}

bool MinMax::IsZero() const
{
    return min == 0 && max == 0;
}

float MinMax::Diff() const
{
    return max - min;
}
