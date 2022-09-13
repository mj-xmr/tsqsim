#include "pch_test.h"

#include "PredictorFactory.h"
#include "PredictorType.h"
#include "PredictorTypeStr.h"
#include "OrderedSeries.h"
#include "SymbolFactoryClean.h"

#include <Util/CoutBuf.hpp>
#include <Util/VecD.hpp>

#include <UnitTest++/UnitTest++.h>

using namespace std;
using namespace EnjoLib;

static VecD PredGenTrue()
{
    const int LEN = 40;
    VecD ret;
    for (int i = 1; i < LEN + 1; ++i)
    {
        ret.Add(i);
    }
    return ret;
}

static VecD Pred(const VecD & inp, const PredictorType & type)
{
    CorPtr<ISymbol> sym = SymbolFactoryClean().Create("Ordered");
    OrderedSeries oser(*sym);
    oser.FeedVals(inp);
    
    CorPtr<IPredictor> algo = PredictorFactory().Create(oser, type);
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
    verbose = true;
    PredictorTypeStr typeStr;
    VecI ignored;
    ignored.push_back(int(PredictorType::PRED_R_BASELINE));
    ignored.push_back(int(PredictorType::PRED_R_CUSTOM));
    ignored.push_back(int(PredictorType::PRED_PY_CUSTOM)); /// TODO: It would be good to check it on a smaller sample as well
    const VecD & vecTrue = PredGenTrue();
    for (int iType = 0; iType <= int(PredictorType::PRED_TRUE); ++iType)
    {
        if (verbose)
        {
            LOGL << "Pred type = " << typeStr.at(iType) << Nl;
        }
        const PredictorType type = PredictorType(iType);
        if (ignored.Contains(iType))
        {
            LOGL << "Ignoring: " << typeStr.at(iType) << Nl;
            continue;
        }
        CorPtr<ISymbol> sym = SymbolFactoryClean().Create("Ordered");
        OrderedSeries oser(*sym);
        //oser.FeedVals(vecTrue); // Not needed
        CorPtr<IPredictor> algo = PredictorFactory().Create(oser, type);
        const VecD & vecActual = algo->Predict(vecTrue);
        const VecD & vecActualVec = algo->PredictVec(vecTrue);
        CHECK_EQUAL(vecTrue.size(), vecActual.size());
        CHECK_EQUAL(vecTrue.size(), vecActualVec.size());
        
        const int lags = algo->GetLags();
        for (int i = 0; i < lags; ++i)
        {
            CHECK_EQUAL(IPredictor::ERROR, vecActual.at(i));    // Initial condition: no predictions made
            CHECK_EQUAL(IPredictor::ERROR, vecActualVec.at(i)); // Initial condition: no predictions made
        }
        for (int i = lags; i < vecTrue.size() - 1; ++i)
        {
            CHECK(vecActual.at(i) != IPredictor::ERROR);    // Predicted something
            if (type != PredictorType::PRED_TRUE)
            {
                //CHECK(vecActual.at(i) != vecTrue.at(i));
            }
        }
        for (int i = lags; i < vecTrue.size() - 1; ++i)
        {
            CHECK(vecActualVec.at(i) != IPredictor::ERROR); // Predicted something
            CHECK_CLOSE(vecActual.at(i), vecActualVec.at(i), 0.01);   // The vector prediction is equivalent to the looped PredictNext 
        }
    }
}

