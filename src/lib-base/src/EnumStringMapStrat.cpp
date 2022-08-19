#include "EnumStringMapStrat.h"
#include "StrategyFactoryName.h"
#include "StrategyType.h"
#include "StrategyTypeEnum.h"

#include <Util/Str.hpp>

using namespace StrategyFactory;

EnumStringMapStrat::EnumStringMapStrat()
{
    for (int i = 0; i <= int(Type::STRA_LAST); ++i)
    {
        AddPriv(i);
    }
}

EnumStringMapStrat::~EnumStringMapStrat(){}

void EnumStringMapStrat::AddPriv(int istrat)
{
    Type stra = Type(istrat);
    Add(istrat, StrategyFactoryName().Create(stra));
}
