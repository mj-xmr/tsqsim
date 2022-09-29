#include "EnumStringMapPeriod.h"
#include "Periods.h"
#include "PeriodType.h"

#include <Util/Str.hpp>

EnumStringMapPeriod::~EnumStringMapPeriod(){}
EnumStringMapPeriod::EnumStringMapPeriod()
{
    const PeriodsAll pall;
    for (int i = 0; i < pall.GetPeriods().size(); ++i)
    {
        PeriodType type = PeriodType(i);
        switch (type) // Generate compiler warnings
        {
            case PeriodType::M1:   Add(i, "m1"); break;
            case PeriodType::M5:   Add(i, "m5"); break;
            case PeriodType::M15:  Add(i, "m15"); break;
            case PeriodType::M30:  Add(i, "m30"); break;
            case PeriodType::H1:   Add(i, "h1"); break;
            case PeriodType::H2:   Add(i, "h2"); break;
            case PeriodType::H4:   Add(i, "h4"); break;
            case PeriodType::H8:   Add(i, "h8"); break;
            case PeriodType::H12:  Add(i, "h12"); break;
            case PeriodType::D:    Add(i, "d"); break;
            case PeriodType::W:    Add(i, "w"); break;
            case PeriodType::M:    Add(i, "m"); break;
        }
    }
}
