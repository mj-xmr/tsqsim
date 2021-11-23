#include "MainTester.h"

#include "TicksProviderFactory.h"
#include "ITicks.h"
#include "Ticks.h"
#include "SymbolFactoryAbstract.h"
#include "IPeriod.h"
#include "ISymbol.h"
#include "IBufferCandles.h"
#include "SerializationSpec.h"
#include "TicksFilesExt.h"
#include "ConfigGlob.h"
#include "ConfigSym.h"
#include "ConfigTF2.h"
#include "Candle.h"
#include "ConfigMan.h"
//#include "HmmStates.h"
#include "MainTesterUtil.h"
#include "MainTesterMT.h"
#include "TradeUtil.h"
#include "DataSrcType.h"

#include <Util/Timer.hpp>
#include <Util/CoutBuf.hpp>
#include <Util/CharManipulations.hpp>
#include <Util/FileUtils.hpp>
#include <Util/ThreadWrap.hpp>
#include <Template/UniquePtr.hpp>
#include <Template/CorradePointer.h>
#include <Template/Array.hpp>
#include <Util/CoutBuf.hpp>

using namespace std;
using namespace EnjoLib;

std::mutex MainTester::m_counterMutex; /// TODO: could be the source of crashes on static O3=OFF ?
//std::condition_variable MainTester::m_cv;
std::atomic<bool> MainTester::m_isReady(true);
int MainTester::m_counter;

MainTester::MainTester(const SymbolFactoryAbstract & symFact, const ConfigTF2 * confTF2, const ConfigSym * confSym, bool verbose)
: m_confTF2(confTF2)
, m_confSym(confSym)
, m_symFact(symFact)
, m_log(GetLog(verbose))
{
    if (confSym)
    {
        const DataSrcType type = confSym->GetDataSrc();
        switch (type)
        {
        case DataSrcType::FOREX_TESTER:
            m_tickProvType = TickProviderType::ARCHIVER;
            break;
        case DataSrcType::MONERO:
            m_tickProvType = TickProviderType::XMR;
            break;
        }
    }
}

void MainTester::SetFake()
{
    m_tickProvType = TickProviderType::SMALL;
}

void MainTester::SetProvider(const TickProviderType & provType)
{
    m_tickProvType = provType;
}

MainTester::~MainTester() {}

CorPtr<ISymbol> MainTester::GetSymbol(EnjoLib::Str symbolName, const VecStr & periodNames) const
{
    symbolName = CharManipulations().ToUpper(symbolName);
    const CorPtr<ITicksProvider> tickProvider = TickProviderFactory().Create(m_tickProvType);
    if (IsPeriodMissing(symbolName))
        ArchiveSymbol(symbolName, tickProvider.get());

    CorPtr<ISymbol> sym = m_symFact.Create(symbolName, periodNames);
    MainTesterUtil mtu(m_confTF2, sym.get(), m_log);
    for (IPeriod * p : sym->GetPeriodsRW())
    {
        if (p->GetNumTicks() < 15)
        {
            // Speed up loading by aggregating monthly ticks
            m_log << "Restoring Ticks '" << symbolName << "'" << EnjoLib::Nl;
            CorPtr<ITicks> t = tickProvider->GetTicks(symbolName, m_confSym);
            t->Set(*mtu.Filter(symbolName, *t, m_confSym));
            p->Feed(*t);
        }
        else
        {
            Ticks t;
            if (lastSymbol == symbolName && lastPeriod == p->GetName())
            {
                m_log << "Uncaching '" << p->GetSymbolPeriodId() << "'" << EnjoLib::Nl;
                t = m_cacheTicks->GetTicksView();
            }
            else
            {
                m_log << "Restoring '" << p->GetSymbolPeriodId() << "'" << EnjoLib::Nl;
                t = tickProvider->GetPeriod(symbolName, p->GetName())->GetTicksView();
                // TODO: Mutex, or segfaults.
                //m_cacheTicks = t;
                //lastSymbol = symbolName;
                //lastPeriod = p->GetName();
            }
            t = mtu.Filter(symbolName, t, m_confSym)->GetTicksView();
            p->SetCandles(t.ToCandles());
        }

        /*
        const TicksFilesExt tfxSt(symbolName, p->GetName(), "states");
        HmmStates states = SerializationSpec().RestoreZippedStates(tfxSt.binZipFile);
        p->SetStates(states);
        */

    }
    mtu.RestoreTicks(tickProvider.get(), m_confSym);
    mtu.FilterBySpread();

    m_log << symbolName << ": " << "Calculating Techs " << EnjoLib::Nl;
    sym->CalcTech();
    m_log << symbolName << ": " << "Ready" << EnjoLib::Nl;

    return sym;
}

void MainTester::ArchiveSymbol(EnjoLib::Str symbolName, const ITicksProvider * tickProvider) const
{
    Ticks t = tickProvider->GetTicks(symbolName)->GetTicksView();
    m_log << t.GetTicks3().size() << EnjoLib::Nl;
    m_log << symbolName << ": " << "Converting" << EnjoLib::Nl;
    CorPtr<ISymbol> sym = m_symFact.Create(symbolName);
    sym->Feed(t);
    for (const IPeriod * p : sym->GetPeriods())
    {
        if (p->GetName() == "m1")
        {
            m_log << symbolName << ": Skipping " << p->GetName() << EnjoLib::Nl;
            continue; // We use monthly m1 anyway
        }
        const TicksFilesExt tfx(symbolName, symbolName, p->GetName());
        m_log << symbolName << ": Archiving " << p->GetName() << EnjoLib::Nl;
        const IBufferCandles & bufCan = p->GetCandles();
        Ticks out(*bufCan.ToTicks());
        SerializationSpec().ArchiveZipped(tfx.binZipFile, out);

        /*
        if (string(p->GetName()) == string("h8"))
        {
            const TicksFilesExt tfxSt(symbolName, p->GetName(), "states");
            HmmStates hmmStates;
            hmmStates.Add(bufCan, p->GetSymbolPeriodId());
            cout << symbolName << ": Archiving states " << p->GetName() << endl;
            SerializationSpec().ArchiveZipped(tfxSt.binZipFile, hmmStates);
        }
        */
    }
}

CorPtr<ISymbol> MainTester::GetSymbolStatic(int id, const MainTester * instance, const EnjoLib::Str & symbolName, const VecStr & periodNames)
{
    bool loadBalancing = EnjoLib::ThreadWrap::GetConcurrency() > 2;
    loadBalancing = false; // using ctpl
    if (not loadBalancing)
    {
        CorPtr<ISymbol> sym = instance->GetSymbol(symbolName.c_str(), periodNames);
        return sym;
    }
    else
    {
        {
            std::lock_guard<std::mutex> lock(m_counterMutex);
            if (++m_counter == int(ThreadWrap::GetConcurrency()) - 1)
                m_isReady.store(false);
        }
        while (!m_isReady.load())
            ThreadWrap::Yield();
        CorPtr<ISymbol> sym = instance->GetSymbol(symbolName.c_str(), periodNames);
        {
            std::lock_guard<std::mutex> lock(m_counterMutex);
            --m_counter;
            m_isReady.store(true);
        }
        return sym;
    }
}

VecUPtr<ISymbol> MainTester::GetSymbolMT(const VecStr & symbolNames, const VecStr & periodNames, const SetStr & blacklist, bool useBlacklist) const
{
    const Timer timer;
    bool multiThreaded = IsMultithreaded(symbolNames);
    std::vector<MainTesterMT::TupleIn> tupIn;

    for(const auto &sym : symbolNames)
    {
        VecStr periodsUsed;
        bool isBlacklisted = false;
        for (const Str & per : periodNames)
        {
            if (TradeUtil().IsBlacklisted(blacklist, sym, per))
            {
                isBlacklisted = true;
            }
            else
            {   // If not blacklisted, add to used periods
                periodsUsed.push_back(per);
            }
        }
        if (isBlacklisted && periodsUsed.empty())
        {
            LOGL << sym << " blacklisted\n";
            continue; // Otherwise this would mean that all periods are loaded
        }
        MainTesterMT::TupleIn tup;
        Get<0>(tup) = this;
        Get<1>(tup) = sym;
        Get<2>(tup) = periodsUsed;
        tupIn.push_back(tup);
    }
    VecUPtr<ISymbol> ret = MainTesterMT::GetSymbols(tupIn, multiThreaded);
    LOGL << "Got symbols in " << timer.GetElapsedSeconds() << " s" << EnjoLib::Nl;
    if (m_confSym)
        m_log << m_confSym->GetDateFromToStr();
    return ret;
}

VecUPtr<ISymbol> MainTester::GetSymbolPerMT(const EnjoLib::Array<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> & symbolPerNames) const
{
    const Timer timer;
    VecStr symbolNames;
    for (const EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str> & symPer : symbolPerNames)
        symbolNames.push_back(symPer.first);
    bool multiThreaded = IsMultithreaded(symbolNames);
    std::vector<MainTesterMT::TupleIn> tupIn;

    for(const auto &symPer : symbolPerNames)
    {
        VecStr pers; pers.push_back(symPer.second);
        MainTesterMT::TupleIn tup;
        Get<0>(tup) = this;
        Get<1>(tup) = symPer.first;
        Get<2>(tup) = pers;
        tupIn.push_back(tup);
    }
    VecUPtr<ISymbol> ret = MainTesterMT::GetSymbols(tupIn, multiThreaded);

    m_log << "Got symbols in " << timer.GetElapsedSeconds() << " s" << EnjoLib::Nl;
    if (m_confSym)
        m_log << m_confSym->GetDateFromToStr();
    return ret;
}

bool MainTester::IsPeriodMissing(EnjoLib::Str symbolName) const
{
    CorPtr<ISymbol> symAll = m_symFact.Create(symbolName);
    for (const IPeriod * p : symAll->GetPeriods())
    {
        if (p->GetName() == "m1")
            continue; // Exception - won't be able to find its file, as it's spread across months
        const TicksFilesExt tfx(symbolName, symbolName, p->GetName());
        if (FileUtils().FileExists(tfx.binZipFile))
            continue;
        if (FileUtils().FileExists(tfx.binaryFile))
            continue;
        return true;
    }
    return false;
}

bool MainTester::IsMultithreaded(const VecStr & symbolNames) const
{
    bool multiThreaded = ConfigGlob().SYMBOLS_MULTITHREAD;
    //multiThreaded = false;
    //multiThreaded = true;
    int missingPeriods = 0;
    for(const auto &sym : symbolNames) {
        if (IsPeriodMissing(sym)){
            ++missingPeriods;
            m_log << "Missing period of symbol - " << sym << EnjoLib::Nl;
        }
    }
    if (missingPeriods > 0)
        m_log << "Missing total " << missingPeriods << " periods.\n\n";
    if (missingPeriods > 1)
        multiThreaded = false;


    multiThreaded = gcfgMan.IsMT(multiThreaded);
    return multiThreaded;
}

