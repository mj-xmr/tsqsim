#include "MainTesterMT.h"
#include "MainTester.h"
#include "MainTesterUtil.h"
#include "ISymbol.h"

#include "CtplWrap.h"

#include <Template/UniquePtr.hpp>

using namespace std;
using namespace EnjoLib;

MainTesterMT::MainTesterMT(){}
MainTesterMT::~MainTesterMT(){}

VecUPtr<ISymbol> MainTesterMT::GetSymbols(const std::vector<TupleIn> & inp, bool multiThreaded)
{
    CtplWrap<CorPtr<ISymbol>> ctpl;
    ctpl.GetCfgRW().SetMT(multiThreaded);

    for (const TupleIn & tin : inp)
    {
        ctpl.Add(MainTester::GetSymbolStatic, Get<0>(tin), Get<1>(tin), Get<2>(tin));
    }

    vector<CorPtr<ISymbol>> futures = ctpl.Get();
    vector<ISymbol*> vecPtr;
    for(auto &e : futures) {
        //ret.push_back(EnjoLib::UniquePtr<ISymbol>(e.get().release()));
        vecPtr.push_back(e.release());
    }
    vecPtr = MainTesterUtil::SortISymbolsGrowing(vecPtr);

    VecUPtr<ISymbol> ret;
    for(ISymbol* psym : vecPtr) {
        ret.push_back(EnjoLib::UniquePtr<ISymbol>(psym));
    }

    return ret;
}
