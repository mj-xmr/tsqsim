#include "PeriodFactoryAbstract.h"
#include "IPeriod.h"
#include <Template/CorradePointer.h>

PeriodFactoryAbstract::PeriodFactoryAbstract()
{
    //ctor
}

PeriodFactoryAbstract::~PeriodFactoryAbstract()
{
    //dtor
}

Corrade::Containers::Pointer<IPeriod> PeriodFactoryAbstract::Copy(const IPeriod & per) const
{
    return Create(per.GetNumTicks(), per.GetSymbol());
}
