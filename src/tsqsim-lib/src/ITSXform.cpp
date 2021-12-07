#include "ITSXform.h"

ITSXform::ITSXform(){}
ITSXform::~ITSXform(){}

unsigned ITSXform::MaxShift() const
{
    return 0;
}

double ITSXform::Invert(const EnjoLib::VecD & vals) const
{
    return vals.at(0);
}
