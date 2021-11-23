#include "pch_test.h"

#include "typesVec.h"
#include "OptiVar.h"
#include <Util/CoutBuf.hpp>

#include <UnitTest++/UnitTest++.h>

using namespace std;

TEST(OptiVar_fixed_space1)
{
    const float valMin = 0;
    const float valMax = 10;
    const float step = 1;
    const EnjoLib::VecF ret = OptiVarF::GetSpaceDiscrete(valMin, valMax, step);

    CHECK(ret.size());
}

TEST(OptiVar_random_space1)
{
    const float valMin = 0;
    const float valMax = 10;
    const float step = 1;
    const EnjoLib::VecF retFix = OptiVarF::GetSpaceDiscrete(valMin, valMax, step);
    const EnjoLib::VecF retRan = OptiVarF::GetSpaceRandom(valMin, valMax);

    CHECK(retFix.size());
    CHECK(retRan.size());

    CHECK(retRan.size() > retFix.size());
}
