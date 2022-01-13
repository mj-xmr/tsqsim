#include "pch_test.h"

#include "PredictorFactory.h"
#include "PredictorType.h"
#include "PredictorTypeStr.h"
#include <Util/CoutBuf.hpp>
#include <Util/VecD.hpp>

#include <UnitTest++/UnitTest++.h>

using namespace std;
using namespace EnjoLib;

static VecD PredGenTrue()
{
    VecD ret;
    for (int i = 1; i < 12; ++i)
    {
        ret.Add(i);
    }
    return ret;
}

/// TODO: Restore
/*
static VecD Pred(const VecD & inp, const PredictorType & type)
{
    CorPtr<IPredictor> algo = PredictorFactory().Create(type);
    return algo->Predict(inp);
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
    //vecExpected.Add(vecTrue.at(0)); // No chance of knowing the truth.
    vecExpected.Add(IPredictor::ERROR);
    for (int i = 0; i < vecTrue.size() - 1; ++i)
    {
        vecExpected.Add(vecTrue.at(i));
    }

    CHECK_ARRAY_EQUAL(vecExpected, vecActual, vecTrue.size());
    CHECK(vecExpected == vecActual);
}

TEST(Pred_all_zero_cond)
{
    bool verbose = false;
    //verbose = true;
    PredictorTypeStr typeStr;
    const VecD & vecTrue = PredGenTrue();
    for (int iType = 0; iType <= int(PredictorType::PRED_TRUE); ++iType)
    {
        if (verbose)
        {
            LOGL << "Pred type = " << typeStr.at(iType) << Nl;
        }
        const PredictorType type = PredictorType(iType);
        CorPtr<IPredictor> algo = PredictorFactory().Create(type);
        const VecD & vecActual = algo->Predict(vecTrue);
        CHECK_EQUAL(vecTrue.size(), vecActual.size());
        
        const int lags = algo->GetLags();
        for (int i = 0; i < lags; ++i)
        {
            CHECK_EQUAL(IPredictor::ERROR, vecActual.at(i)); // Initial condition: no predictions made
        }
        for (int i = lags; i < vecTrue.size() - 1; ++i)
        {
            CHECK(vecActual.at(i) != IPredictor::ERROR); // Predicted something
            if (type != PredictorType::PRED_TRUE)
            {
                //CHECK(vecActual.at(i) != vecTrue.at(i));
            }
        }
    }
}
*/
