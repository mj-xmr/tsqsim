#include "pch_test.h"

#include "ConfigDirs.h"
#include "ConfigMan.h"

#include <Util/ToolsMixed.hpp>
#include <UnitTest++/UnitTest++.h>

using namespace std;
using namespace EnjoLib;
TEST(ConfigDirs_isBasid)
{
    const Str & result = ConfigDirs().DIR_CFG;
    const Str & expected = "cfg/";
    CHECK_EQUAL(expected, result);
}

TEST(ConfigDirs_isConcat)
{
    const Str & result = ConfigDirs().DIR_OUT;
    const Str & expected = ToolsMixed::GetTmpDir() + "tf//screenshots";
    CHECK_EQUAL(expected, result);
}

TEST(ConfigMan_numConfigsEqual)
{
    ConfigMan cfgMan;
    cfgMan.Read(cfgMan.GetConfigString());
}

