#include "pch_test.h"
//#include "RInitDeinit.h"
#include <UnitTest++/UnitTest++.h>
#include <Util/CoutBuf.hpp>

using namespace std;

int main()
{
    //RInitDeinit rinit;
    LOGL << "Running tests!" << EnjoLib::Nl;
    return UnitTest::RunAllTests();
}
