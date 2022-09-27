#include "EnumStringMapPeriod.h"
#include "Periods.h"

#include <Util/Str.hpp>

EnumStringMapPeriod::~EnumStringMapPeriod(){}
EnumStringMapPeriod::EnumStringMapPeriod()
{
    const PeriodsAll pall;
    for (int i = 0; i < pall.GetPeriods().size(); ++i)
    {
        PeriodsEnum type = PeriodsEnum(i);
        switch (type) // Generate compiler warnings
        {
            case PeriodsEnum::Minute1: Add(i, "m1"); break;
            case PeriodsEnum::M5:   Add(i, "m5"); break;
            case PeriodsEnum::M15:  Add(i, "m15"); break;
            case PeriodsEnum::M30:  Add(i, "m30"); break;
            case PeriodsEnum::H1:   Add(i, "h1"); break;
            case PeriodsEnum::H2:   Add(i, "h2"); break;
            case PeriodsEnum::H4:   Add(i, "h4"); break;
            case PeriodsEnum::H8:   Add(i, "h8"); break;
            case PeriodsEnum::H12:  Add(i, "h12"); break;
            case PeriodsEnum::D:    Add(i, "d"); break;
            case PeriodsEnum::W:    Add(i, "w"); break;
            case PeriodsEnum::M:    Add(i, "m"); break;
        }
    }
}
