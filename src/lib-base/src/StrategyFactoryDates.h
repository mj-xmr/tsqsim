#ifndef STRATEGYFACTORYDATES_H
#define STRATEGYFACTORYDATES_H

class StrategyType;
#include "DataDates.h"

class StrategyFactoryDates
{
    public:
        StrategyFactoryDates(){}
        virtual ~StrategyFactoryDates(){}

        DataDates Create(const StrategyType & type) const;

    protected:

    private:
};

#endif // STRATEGYFACTORYDATES_H
