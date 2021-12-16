#include "pch_test.h"

#include <UnitTest++/UnitTest++.h>
#include <Util/CoutBuf.hpp>

using namespace std;

int main()
{
    LOGL << "Running tests!" << EnjoLib::Nl;
    return UnitTest::RunAllTests();
}
