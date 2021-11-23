#include "AbstractsIndep.h"
#include "MasConsts.h"

AbstractsIndep::AbstractsIndep(){}
AbstractsIndep::~AbstractsIndep(){}

int AbstractsIndep::GetMaMin() const
{
    return MasConsts::MIN_MA;
}
int AbstractsIndep::GetMaMax() const
{
    return MasConsts::MAX_MA;
}
