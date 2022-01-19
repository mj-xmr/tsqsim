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

static void TestXformIteration(const VecD & inp, const ITSXform * xform, bool verbose)
{
    const int idxMin = xform->MaxShift();
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

    return inp;
}

class CandlesMinimal : public IHasCandles
{
public:
    CandlesMinimal(const VecD & vec);
    Candle GetCandle(int idx, int shift = 0) const override;
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

Candle CandlesMinimal::GetCandle(int idx, int shift) const
{
    return m_candles.at(idx + shift);
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
        //case TSXformType::DIFF:
         //   break;        // This is how you'd make exceptions
        default:
            {
                TestXformIteration(inp, xform.get(), verbose);
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
        dataMan->Add(res);
    }
}

static void TestXformArrayMan(const VecD & inp, const TSXformMan & man)
{
    bool verbose = false;
    //verbose = true;
    TSXformDataMan dataMan;
    FillDataMan(inp, man, &dataMan);

    VecD reconstructed;
    for (int i = 0; i < int(dataMan.Len()); ++i)
    {
        const double & conv = dataMan.converted.at(i);
        const VecD & lost = dataMan.convertedLost.at(i);
        const TSRes & reconstr = man.Reconstruct(conv, lost);
        reconstructed.push_back(reconstr.val);
    }

    CHECK_EQUAL(inp.size(), reconstructed.size());
    CHECK_ARRAY_CLOSE(inp, reconstructed, reconstructed.size(), 0.01);
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

    CorPtr<IPredictor> algo = PredictorFactory().Create(dat, type);
    const VecD & pred = algo->Predict(dataMan.converted);
    VecD reconstructed;
    for (int i = 0; i < int(dataMan.Len()); ++i)
    {
        const double & conv = pred.at(i);
        const VecD & lost = dataMan.convertedLost.at(i);
        const TSRes & reconstr = man.Reconstruct(conv, lost);
        reconstructed.push_back(reconstr.val);
    }

    VecD vecExpected;
    const int lags = algo->GetLags();
    for (int i = 0; i < lags; ++i)
    {
        vecExpected.Add(IPredictor::ERROR);
    }
    for (int i = lags; i < vecTrue.size(); ++i)
    {
        vecExpected.Add(vecTrue.at(i - lags));
    }
    CHECK_EQUAL(vecTrue.size(), reconstructed.size());
    CHECK_EQUAL(vecExpected.size(), reconstructed.size());
    CHECK_ARRAY_CLOSE(vecExpected, reconstructed, reconstructed.size(), 0.01);

    return reconstructed;
}

TEST(Pred_xform_sqrt)
{
    TSXformMan man(PriceType::CLOSE);
    man.AddXForm(TSXformType::SQRTS);
    const VecD & vecTrue = TestXformGenInput();
    CorPtr<ISymbol> isym = SymbolFactoryClean().Create("Oser");
    OrderedSeries oser(*isym);
    //oser.FeedVals(vecTrue);
    const VecD & reconstrPred = TestXformArrayManPred(oser, vecTrue, man, PredictorType::PRED_BASELINE);
    //LOGL << reconstrPred.Print() << Nl;
}

TEST(Pred_xform_diff) /// TODO: FIXME
{
    TSXformMan man(PriceType::CLOSE);
    man.AddXForm(TSXformType::DIFF);
    const VecD & vecTrue = TestXformGenInput();
    /// TODO: Diff distorts the signal being inverted
    CorPtr<ISymbol> isym = SymbolFactoryClean().Create("Oser");
    OrderedSeries oser(*isym);
    //oser.FeedVals(vecTrue);
    //const VecD & reconstrPred = TestXformArrayManPred(oser, vecTrue, man, PredictorType::PRED_BASELINE);
    //LOGL << reconstrPred.Print() << Nl;
}
