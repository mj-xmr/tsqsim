#include "pch_test.h"

#include "PredictorFactory.h"
#include "PredictorType.h"
#include <Util/CoutBuf.hpp>
#include <Util/VecD.hpp>

#include <UnitTest++/UnitTest++.h>

using namespace std;
using namespace EnjoLib;

static VecD PredGenTrue()
{
    VecD ret;
    for (int i = 1; i < 7; ++i)
    {
        ret.Add(i);
    }
    return ret;
}

static VecD Pred(const VecD & inp, const PredictorType & type)
{
    CorPtr<IPredictor> algo = PredictorFactory().Create(type);
    return algo->PredictNextVec(inp);
}

TEST(Pred_True)
{
    const VecD & vecTrue = PredGenTrue();
    const VecD & vecActual = Pred(vecTrue, PredictorType::PRED_TRUE);

    CHECK_ARRAY_EQUAL(vecTrue, vecActual, vecTrue.size());
    CHECK(vecTrue == vecActual);
}

TEST(Pred_Baseline)
{
    const VecD & vecTrue = PredGenTrue();
    const VecD & vecActual = Pred(vecTrue, PredictorType::PRED_BASELINE);
    
    VecD vecExpected;
    vecExpected.Add(vecTrue.at(0));
    for (int i = 0; i < vecTrue.size() - 1; ++i)
    {
        vecExpected.Add(vecTrue.at(i));
    }

    CHECK_ARRAY_EQUAL(vecExpected, vecActual, vecTrue.size());
    CHECK(vecExpected == vecActual);
}

