#include "pch_qt.h"

#include "Util.h"

#include <UnitTest++/UnitTest++.h>

/// TODO: Extend

TEST(Util_stdVectToQVectF_1)
{
    const std::vector<float> exp = {1, 2, 3};
    const QVector<double> & res = Util::stdVectToQVectF(exp);

    CHECK_EQUAL(exp.size(), res.size());
}
