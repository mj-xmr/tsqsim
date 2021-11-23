#include "pch_test.h"

#include <UnitTest++/UnitTest++.h>

//#include <CorrelMap.h>
#include <Buffer.h>
#include <Util/VecF.hpp>
//#include <BufferUpdateable.h>
//#include <Util/Bimap.hpp>


using namespace std;
using namespace EnjoLib;

TEST(Buffer_stringInt)
{
    VecF test;
    Buffer buf(test);
    string result = "";
    string expected = "";
    CHECK_EQUAL(expected, result);
}


TEST(Buffer_convert_idx_1)
{
    VecF test(30);
    Buffer buf(test);

    const int i = 5;
    CHECK(buf.ConvertIndex(i) != i);
    CHECK_EQUAL(buf.ConvertIndex(buf.ConvertIndex(i)), i);
}


