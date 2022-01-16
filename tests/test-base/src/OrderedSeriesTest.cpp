#include "pch_test.h"

#include "typesVec.h"
#include "OrderedSeries.h"
#include "SymbolFactoryClean.h"
#include "Candle.h"

#include <Util/CoutBuf.hpp>
#include <Util/VecD.hpp>

#include <UnitTest++/UnitTest++.h>

using namespace std;
using namespace EnjoLib;

static VecD GenerateOrderedSeries(int numVals)
{
    VecD ret;
    for (int i = 0; i < numVals; ++i)
        ret.Add(i);
    return ret;
}

TEST(OrderedSeries_sizes)
{
    static const int NUM_ELEMENTS_ORDERED_SERIES = 10;
    const VecD series = GenerateOrderedSeries(NUM_ELEMENTS_ORDERED_SERIES);
    
    CorPtr<ISymbol> sym = SymbolFactoryClean().Create("Ordered");
    OrderedSeries oser(*sym);
    CHECK_EQUAL(0, oser.Len());
    for (const double val : series)
    {
        oser.FeedVal(val);
    }
    
    CHECK_EQUAL(NUM_ELEMENTS_ORDERED_SERIES, series.size());
    CHECK_EQUAL(NUM_ELEMENTS_ORDERED_SERIES - 1, oser.Len()); // The first one gets merged, but this might change.
}

TEST(OrderedSeries_timestamps_ordered)
{
    static const int NUM_ELEMENTS_ORDERED_SERIES = 1e4;
    const VecD series = GenerateOrderedSeries(NUM_ELEMENTS_ORDERED_SERIES);
    
    CorPtr<ISymbol> sym = SymbolFactoryClean().Create("Ordered");
    OrderedSeries oser(*sym);
    oser.FeedVals(series);
    
    const IBufferCandles & bufCan = oser.GetCandles();
    const IterCan & iterCan = bufCan.GetDataIter();
    CHECK_EQUAL(oser.Len(), bufCan.Len());
    CHECK_EQUAL(oser.Len(), iterCan.size());
    for (int i = 1; i < oser.Len(); ++i)
    {
        const Candle & canPrev = iterCan.at(i-1);
        const Candle & canCurr = iterCan.at(i);
        
        CHECK(canPrev.GetDate() < canCurr.GetDate());
    }
}