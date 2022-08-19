#include "pch_test.h"

#include <StrategyFactoryName.h>
#include "StrategyType.h"
#include "StrategyTypeEnum.h"
#include <Util/Str.hpp>

#include <UnitTest++/UnitTest++.h>

static StrategyFactoryName sfn;

#ifndef DEBUG
// Exceptions mess up debugging sessions
TEST(StrategyFactoryName_nonExisting_throws)
{
    CHECK_THROW(sfn.NameToType("Nonexisting"), std::exception);
}
#endif

TEST(StrategyFactoryName_wknd_returns_wknd)
{
    const int expected = int(StrategyFactory::Type::STRA_WEEKEND2);
    const int result   = int(sfn.NameToType("Wknd").GetType());
    CHECK_EQUAL(expected, result);
}
