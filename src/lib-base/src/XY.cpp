#include "XY.h"

bool XY::operator < (const XY & other) const
{
    return x < other.x;
}

bool XY::IsValid() const
{
    return y != 0;
}
