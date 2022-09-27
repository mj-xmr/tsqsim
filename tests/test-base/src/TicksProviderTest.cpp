#include "pch_test.h"

#include "IMainTester.h"
#include "ISymbol.h"
#include "IPeriod.h"
#include "SymbolFactoryClean.h"
#include "TicksProviderFactory.h"

#include <Util/CoutBuf.hpp>
#include <Util/Str.hpp>
#include <Template/CorradePointer.h>
#include <UnitTest++/UnitTest++.h>

TEST(TesterFake_1)
{
    const SymbolFactoryClean symFact;
    CorPtr<IMainTester> ptester = IMainTester::Create(symFact, nullptr, nullptr, false);
    ptester->SetFake();

    const IMainTester & tester = *ptester;
    CorPtr<ISymbol> sym = tester.GetSymbol("EURUSD");
    CHECK(sym->GetSizeAll() > 0);
}

TEST(TesterFake_XMR_perD)
{
    const SymbolFactoryClean symFact;
    CorPtr<IMainTester> ptester = IMainTester::Create(symFact, nullptr, nullptr, false);
    ptester->SetFake();

    const IMainTester & tester = *ptester;
    CorPtr<ISymbol> sym = tester.GetSymbol("EURUSD");
    const IPeriod & perD = sym->GetPeriod("d");
    const IPeriod & perW = sym->GetPeriod("w");
    LOGL << "Len day = " << perD.Len() << ", Len Week = " << perW.Len() << EnjoLib::Nl;
    CHECK(perD.Len() > 0);
    CHECK(perD.Len() > perW.Len());
}

TEST(TesterFake_XMR)
{
    const SymbolFactoryClean symFact;
    CorPtr<IMainTester> ptester = IMainTester::Create(symFact, nullptr, nullptr, false);
    ptester->SetProvider(TickProviderType::XMR_FAKE);

    const IMainTester & tester = *ptester;
    CorPtr<ISymbol> sym = tester.GetSymbol("EURUSD");
    CHECK(sym->GetSizeAll() > 0);
}

TEST(TesterFake_Adaptive)
{
    const SymbolFactoryClean symFact;
    CorPtr<IMainTester> ptester = IMainTester::Create(symFact, nullptr, nullptr, false);
    ptester->SetProvider(TickProviderType::ADAPTIVE_FAKE);

    const IMainTester & tester = *ptester;
    CorPtr<ISymbol> sym = tester.GetSymbol("EURUSD");
    CHECK(sym->GetSizeAll() > 0);
}
