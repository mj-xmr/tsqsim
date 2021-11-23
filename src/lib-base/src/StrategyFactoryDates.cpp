#include "StrategyFactoryDates.h"
#include "StrategyType.h"
#include "StrategyTypeEnum.h"

DataDates StrategyFactoryDates::Create(const StrategyType & type) const
{
    DataDates dates;
    switch (type.GetType())
    {
        case StrategyFactory::Type::STRA_WEEKEND:
        case StrategyFactory::Type::STRA_WEEKEND2:
            {
                dates.yearStart  = 2015;
                dates.monthStart = 10;
                return dates;
            }
        case StrategyFactory::Type::STRA_SR_BRK:
            {
                dates.yearStart  = 2012;
                dates.monthStart = 1;
                return dates;
            }
        case StrategyFactory::Type::STRA_PAIR:
            {
                dates.yearStart  = 2013;
                dates.monthStart = 5;
                return dates;
            }
        default:
            return dates;
    }
}
