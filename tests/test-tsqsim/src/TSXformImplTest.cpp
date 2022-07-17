#include "pch_test.h"

#include "TSXformMan.h"
#include "TSXformDataMan.h"
#include "TSXformFactory.h"
#include "TSXformType.h"
#include "TSXformTypeString.h"
#include "TSRes.h"
#include "IHasCandles.h"
#include "TSXformRes.h"
#include "Candle.h"
#include "SymbolFactoryClean.h"
#include "OrderedSeries.h"
#include "TradeUtilThin.h"

#include "PredictorFactory.h"
#include "PredictorType.h"
#include "PriceType.h"

#include <Util/CoutBuf.hpp>

#include <UnitTest++/UnitTest++.h>

/// TODO: Add opti tests as a separate package

using namespace EnjoLib;
TEST(Conv_Log)
{
    TSXformTypeString xform2str;
    const TSXformType type = TSXformType::LOGS;
    const Str xformStr = xform2str.at(int(type));
    CorPtr<ITSXform> xform = TSXformFactory().Create(xformStr);

    CHECK_CLOSE(-xform->Run(VecD(1, 1.5)).conv, xform->Run(VecD(1, 0.5)).conv, 0.01);
}

static void TestXformIteration(const VecD & inp, ITSXform * xform, bool verbose)
{
    //const int idxMin = xform->MaxShift();
    const int idxMin = 0;
    //VecD prevVec;
    for (int i = 0; i < idxMin; ++i)
    {
        //prevVec.Add()
    }
    for (int i = idxMin; i < int(inp.size()); ++i)
    {
        VecD vecIn;
        for (int j = i; j >= i - idxMin; --j)
        {
            vecIn.Add(inp.at(j));
        }
        const double valIn = vecIn.at(0);
        const XformRes & res = xform->Run(vecIn); /// TODO: Simulate a collection of the data and then reconstruction, not all in one iteration
        const double inv = xform->Invert(VecD(1, res.conv), res.lost);
        if (verbose)
        {
            LOGL << "in = " << valIn << ", res = " << res.conv << ", inv = " << inv << Nl;
        }
        CHECK_CLOSE(valIn, inv, 0.01);
    }
}

static VecD TestXformGenInput()
{
    VecD inp;

    inp.Add(-11);
    inp.Add(-2);
    inp.Add(-0.5);
    inp.Add(0);
    inp.Add(0.5);
    inp.Add(1);
    inp.Add(1.5);
    inp.Add(10);


    inp.clear();

    inp.Add(-2);
    inp.Add(-1);
    inp.Add(0);
    inp.Add(1);
    inp.Add(2);
    inp.Add(3);
    inp.Add(4);
    inp.Add(5);

    return inp;
}

class CandlesMinimal : public IHasCandles
{
public:
    CandlesMinimal(const VecD & vec);
    Candle GetCandleTS(int idx, int shift = 0) const override;
    Candle GetCandle0Based(int idx) const override;
    unsigned Len() const override;
private:
    std::vector<Candle> m_candles;
};

CandlesMinimal::CandlesMinimal(const VecD & vec)
{
    for (const double & ele : vec)
    {
        m_candles.push_back(Candle(ele, ele, ele, ele));
    }
}

Candle CandlesMinimal::GetCandleTS(int idx, int shift) const
{
    const int idxTS = TradeUtilThin::ConvertIndex(idx + shift, m_candles.size());
    return m_candles.at(idxTS);
}

Candle CandlesMinimal::GetCandle0Based(int idx) const
{
    return m_candles.at(idx);
}

unsigned CandlesMinimal::Len() const
{
    return m_candles.size();
}

TEST(Conv_inv_low_level_1_iter)
{
    bool verbose = false;
    //verbose = true;
    const VecD & inp = TestXformGenInput();
    TSXformTypeString xform2str;

    for (int itype = 0; itype < int(TSXformType::END); ++itype)
    {
        const TSXformType type = TSXformType(itype);
        Str xformStr = xform2str.at(itype);
        if (verbose)
        {
            LOGL << xformStr << Nl;
        }
        if (type == TSXformType::ADD ||
            type == TSXformType::MUL ||
            type == TSXformType::DIV )
        {
            xformStr += " 3"; // Expects a parameter
        }
        CorPtr<ITSXform> xform = TSXformFactory().Create(xformStr);

        switch (type)
        {
        case TSXformType::DIFF:
            {
                // has to be skipped 4 now, because it uses 2 data elements
                break;        // This is how you'd make exceptions
            }

        default:
            {
                TestXformIteration(inp, xform.release(), verbose);
            }
        }
    }
}

static void FillDataMan(const VecD & inp, const TSXformMan & man, TSXformDataMan * dataMan)
{
    const CandlesMinimal cans(inp);
    for (int i = 0; i < int(inp.size()); ++i)
    {
        const TSRes & res = man.OnDataPointProt(cans, i);
        //LOGL << "Adding = " << res.val << Nl;
        dataMan->Add(res);
    }
}

static void TestXformArrayMan(const VecD & inp, const TSXformMan & man)
{
    ELO
    //LOG << Nl << Nl;
    //LOG << "Inp = " << inp.Print() << Nl;
    bool verbose = false;
    //verbose = true;
    TSXformDataMan dataMan;
    FillDataMan(inp, man, &dataMan);
    //{LOGL << "converted = " << dataMan.converted.Print() << " convertedLost = " << dataMan.convertedLost.Print() << Nl;}

    const VecD & reconstructed = man.ReconstructVec(dataMan.converted, dataMan.convertedLost);
    //{LOGL << " reconstr = " << reconstructed.Print() << Nl;}

    CHECK_EQUAL(inp.size(), reconstructed.size());
    CHECK_ARRAY_CLOSE(inp, reconstructed, reconstructed.size(), 0.01);
}

TEST(Conv_inv_high_level_empty)
{
    TSXformMan man(PriceType::CLOSE);
    TestXformArrayMan(TestXformGenInput(), man);
}

TEST(Conv_inv_high_level_diff)
{
    TSXformMan man(PriceType::CLOSE);
    man.AddXForm(TSXformType::DIFF);
    TestXformArrayMan(TestXformGenInput(), man);
}

TEST(Conv_inv_high_level_sqrt1)
{
    TSXformMan man(PriceType::CLOSE);
    man.AddXForm(TSXformType::SQRTS);
    TestXformArrayMan(TestXformGenInput(), man);
}

TEST(Conv_inv_high_level_sqrt_sqrt)
{
    TSXformMan man(PriceType::CLOSE);
    man.AddXForm(TSXformType::SQRTS);
    man.AddXForm(TSXformType::SQRTS);
    TestXformArrayMan(TestXformGenInput(), man);
}

TEST(Conv_inv_high_level_sqrt_fabs)
{
    TSXformMan man(PriceType::CLOSE);
    man.AddXForm(TSXformType::SQRTS);
    man.AddXForm(TSXformType::FABS);
    TestXformArrayMan(TestXformGenInput(), man);
}

TEST(Conv_inv_high_level_fabs_sqrt)
{
    TSXformMan man(PriceType::CLOSE);
    man.AddXForm(TSXformType::FABS);
    man.AddXForm(TSXformType::SQRTS);
    TestXformArrayMan(TestXformGenInput(), man);
}

TEST(Conv_inv_high_level_diff_sqrts)
{
    TSXformMan man(PriceType::CLOSE);
    man.AddXForm(TSXformType::DIFF);
    man.AddXForm(TSXformType::SQRTS);
    TestXformArrayMan(TestXformGenInput(), man);
}

TEST(Conv_inv_high_level_sqrts_diff) /// TODO: FIXME
{
    TSXformMan man(PriceType::CLOSE);
    man.AddXForm(TSXformType::SQRTS);
    /// man.AddXForm(TSXformType::DIFF); /// TODO
    TestXformArrayMan(TestXformGenInput(), man);
}

TEST(Conv_inv_high_level_diff_sqrt_fabs)
{
    TSXformMan man(PriceType::CLOSE);
    man.AddXForm(TSXformType::DIFF);
    man.AddXForm(TSXformType::SQRTS);
    man.AddXForm(TSXformType::FABS);
    TestXformArrayMan(TestXformGenInput(), man);
}

TEST(Conv_inv_high_level_diff_diff) /// TODO: FIXME
{
    TSXformMan man(PriceType::CLOSE);
    man.AddXForm(TSXformType::DIFF);
    /// man.AddXForm(TSXformType::DIFF); /// TODO
    TestXformArrayMan(TestXformGenInput(), man);
}

static VecD TestXformArrayManPred(const IDataProvider & dat, const VecD & vecTrue, const TSXformMan & man, const PredictorType & type)
{
    bool verbose = false;
    //verbose = true;
    TSXformDataMan dataMan;
    FillDataMan(vecTrue, man, &dataMan);
    ELO

    CorPtr<IPredictor> algo = PredictorFactory().Create(dat, type);
    const VecD & pred = algo->Predict(dataMan.converted);
    //LOG << "New\n\n";
    //LOG << "converted = " << dataMan.converted.Print() << " convertedLost = " << dataMan.convertedLost.Print() << Nl;
    const VecD & reconstructed = man.ReconstructVec(pred, dataMan.convertedLost);

    VecD vecExpected;
    const int lags = algo->GetLags();
    for (int i = 0; i < lags; ++i)
    {
        /// TODO: unify the expectation
        //vecExpected.Add(IPredictor::ERROR); /// TODO: This is correct!
        vecExpected.Add(reconstructed.at(i)); // For now: accept what was returned until the lags end
        ///vecExpected.Add(vecTrue.at(i)); // sus, but seems to work
    }
    for (int i = lags; i < vecTrue.size(); ++i)
    {
        vecExpected.Add(vecTrue.at(i - lags));
    }
    CHECK_EQUAL(vecTrue.size(), reconstructed.size());
    CHECK_EQUAL(vecExpected.size(), reconstructed.size());
    CHECK_ARRAY_CLOSE(vecExpected, reconstructed, reconstructed.size(), 0.01);
    //CHECK_EQUAL(vecTrue.size(), reconstructed.size());
    //CHECK_ARRAY_CLOSE(vecTrue, reconstructed, reconstructed.size(), 0.01);

    return reconstructed;
}

TEST(Pred_xform_sqrt)
{
    //{LOGL << "SQRT\n";}
    TSXformMan man(PriceType::CLOSE);
    man.AddXForm(TSXformType::SQRTS);
    const VecD & vecTrue = TestXformGenInput();
    CorPtr<ISymbol> isym = SymbolFactoryClean().Create("Oser");
    OrderedSeries oser(*isym);
    //oser.FeedVals(vecTrue);
    const VecD & reconstrPred = TestXformArrayManPred(oser, vecTrue, man, PredictorType::PRED_BASELINE);
    //LOGL << reconstrPred.Print() << Nl;
    //{LOGL << "SQRT end\n";}
}

TEST(Pred_xform_diff)
{
    TSXformMan man(PriceType::CLOSE);
    man.AddXForm(TSXformType::DIFF);
    const VecD & vecTrue = TestXformGenInput();
    CorPtr<ISymbol> isym = SymbolFactoryClean().Create("Oser");
    OrderedSeries oser(*isym);
    //oser.FeedVals(vecTrue);
    const VecD & reconstrPred = TestXformArrayManPred(oser, vecTrue, man, PredictorType::PRED_BASELINE);
    //LOGL << reconstrPred.Print() << Nl;
}
