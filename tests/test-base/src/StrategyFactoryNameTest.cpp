#include "pch_test.h"
#include <UnitTest++/UnitTest++.h>

#include <StrategyFactoryName.h>
#include "StrategyType.h"
#include "StrategyTypeEnum.h"

static StrategyFactoryName sfn;

#ifndef DEBUG
// Exceptions mess up debugging sessions
TEST(StrategyFactoryName_nonExisting_throws)
{
    const bool expected = false;
    try
    {
        sfn.NameToType("Nonexisting");
        CHECK_EQUAL(expected, true);
    }
    catch (std::exception & ex)
    {
        // Should throw
        CHECK_EQUAL(expected, false);
    }
}
#endif

TEST(StrategyFactoryName_wknd_returns_wknd)
{
    const int expected = int(StrategyFactory::Type::STRA_WEEKEND2);
    const int result   = int(sfn.NameToType("Wknd").GetType());
    CHECK_EQUAL(expected, result);
}
