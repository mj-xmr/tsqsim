#include "SignalBase.h"
#include "StateFactory.h"
#include "Candle.h"
#include "ConfigGlob.h"
#include <Util/StackTrace.hpp>
#include <Template/AlgoSTDThin.hpp>
#include <Template/VecT.hpp>
#include <Template/CorradePointer.h>
#include <Template/Array.hpp>

#include <STD/VectorCpp.hpp>
#include <typeinfo>
#include <future>
#include <Ios/Osstream.hpp>
#include <mutex>

using namespace std;
using namespace EnjoLib;

struct SignalBaseImpl
{
    SignalBaseImpl()
    : m_mutexBuy(new std::mutex())
    , m_mutexSell(new std::mutex())
    {
        
    }
    mutable EnjoLib::VecT<int> m_lastPosSignalBuy;
    mutable EnjoLib::VecT<int> m_lastPosSignalSell;
        //mutable std::map<unsigned, bool> m_cacheIsSignalBuy;
        //mutable std::map<unsigned, bool> m_cacheIsSignalSell;
        //mutable std::vector<Bool3State> m_vecCacheIsSignalBuy;
        //mutable std::vector<Bool3State> m_vecCacheIsSignalSell;
        //mutable int m_len = 0;
        mutable Corrade::Containers::Pointer<std::mutex> m_mutexBuy, m_mutexSell; // Could be making problems? Doesn't appear to be
    //mutable std::mutex m_mutexBuy, m_mutexSell; // Original
};

SignalBase::~SignalBase(){}
SignalBase::SignalBase()
: m_pimp(new SignalBaseImpl())
//: m_mutexBuy(new std::mutex())
//, m_mutexSell(new std::mutex())
{
}

void SignalBase::Init(Direction dir) const
{
    if (dir == BUY)
    {
        if (m_pimp->m_lastPosSignalBuy.empty())
            m_pimp->m_lastPosSignalBuy = EnjoLib::VecT<int>(Len(), -2);
    }
    else
    {
        if (m_pimp->m_lastPosSignalSell.empty())
            m_pimp->m_lastPosSignalSell = EnjoLib::VecT<int>(Len(), -2);
    }
    
    if (not m_pimp->m_lastPosSignalBuy.empty() && not m_pimp->m_lastPosSignalSell.empty())
    {
        m_inited = true;
    }
}

int SignalBase::GetLastPosCacheVector(const State & st, EnjoLib::VecT<int> & cache) const
{
    if (st.i >= int(cache.size()))
        return -1;
    int pos = cache.at(st.i);
    if (pos >= 0)
        return pos;
    else
    {
        State sig = st;
        bool found = false;
        for (;sig.i < Len() - 3 && not found; ++sig)
        {
            if (IsSignalProt(sig))
                found = true;
        }
        if (found)
        {
            pos = sig.i-1;
            for(int i = st.i; i < pos + 1; ++i) // Troszke szybsze
            //for(int i = pos; i >= int(st.i); --i)
               cache.atw(i) = pos;
            //for (EnjoLib::VecT<int>::iterator it = cache.begin() + st.i; it != cache.begin() + pos + 1; ++it) // slower?
                //*it = pos;
            return cache[st.i];
        }
        else
        {
            return -1;
        }
    }
}

int SignalBase::GetPosLastSignal(const State & st) const
{
    if (not m_inited)
    {
        Init(st.bullish);
    }
    if (UseCache())
    {
       if (st.bullish)
        {
            return GetLastPosCacheVector(st, m_pimp->m_lastPosSignalBuy);
        }
        else
        {
            return GetLastPosCacheVector(st, m_pimp->m_lastPosSignalSell);
        }
    }
    else
    {
        for (State nx = st; nx.i < Len() - 2; ++nx)
        {
            if (IsSignalProt(nx))
                return nx.i;
        }
        return -1;
    }
}

int SignalBase::GetPosPrevSignal(const State & st) const
{
    const StateFactory fact;
    for (int i = st.i; i >= 0; --i)
        if (IsSignal(*fact.Create(st.bullish, i)))
            return i;
    return -1;
}

bool SignalBase::IsSignal(const State & st) const
{
    std::mutex * mut = st.bullish ? m_pimp->m_mutexBuy.get() : m_pimp->m_mutexSell.get();
    //std::mutex * mut = st.bullish ? &m_mutexBuy : &m_mutexSell;
    std::lock_guard<std::mutex> lock(*mut); /// TODO: a bit controversial
    if (not m_inited)
    {
        Init(st.bullish);
    }
    bool isSignal;
    if (!UseCache() || st.GetCandle().IsDataValid())
    //if (true)
        isSignal = IsSignalProt(st);
    else
    {
        if (st.bullish)
        {
            isSignal = HandleCacheVector(st, m_pimp->m_lastPosSignalBuy);
        }
        else
        {
            isSignal = HandleCacheVector(st, m_pimp->m_lastPosSignalSell);
        }
    }

    return isSignal;
}

bool SignalBase::UseCache() const
{
    return gcfg.USE_CACHE;
}

bool SignalBase::HandleCacheVector(const State & st, EnjoLib::VecT<int> & cache) const
{
    try
    {
        int & cacheRef = cache.atw(st.i);
        const int cacheInt = cacheRef;
        bool isSignal;
        if (cacheInt < -1) // uninitialized
        {
            isSignal = IsSignalProt(st);
            if (isSignal)
            {
                //cout << "Storing cache for " << st << endl;
                //cache.atw(st.i) = st.i; // This state has signal at this index
                cacheRef = st.i; // This state has signal at this index
            }

            else
            {   // Not a signal
                const int offset = 1;
                if (st.i < Len() - offset)
                {
                    //const int lastPosCache = cache.at(st.i + offset);
                    const int lastPosCache = cache[st.i + offset];
                    //if (lastPosCache < -1)
                      //  cache.at(st.i) = -1;
                    //else
                        //cache.atw(st.i) = lastPosCache; // copy previous last position indexes
                        cacheRef = lastPosCache; // copy previous last position indexes
                }

            }
        }
        else
        {
            //cout << "Restoring cache for " << st << endl;
            isSignal = cacheInt == int(st.i);
        }

        return isSignal;
    }
    catch (exception & ex)
    {
        const EnjoLib::Str msg = "Outside bounds for class " + GetClassName();
        throw EnjoLib::ExceptRuntimeError(STRACE_RETHROW(ex, msg));
    }
}

EnjoLib::Array<State> SignalBase::GetSignalStates() const
{
    std::vector<State> ret;
    const StateFactory fact;
    const unsigned sz = Len();
    for (unsigned i = 0; i < sz; ++i)
    {
        const State stBull = *fact.Create(BUY, i);
        const State stBear = *fact.Create(SELL, i);
        if (IsSignal(stBull))
            ret.push_back(stBull);
        else
        if (IsSignal(stBear))
            ret.push_back(stBear);
    }
    return ret;
}

EnjoLib::Pair<EnjoLib::VecT<int>, EnjoLib::VecT<int>> SignalBase::GetSignalIndexes() const
{
    std::future<EnjoLib::VecT<int>> futBull = std::async(std::launch::async, [&]{ return GetSignalIndexes(BUY); });
    std::future<EnjoLib::VecT<int>> futBear = std::async(std::launch::async, [&]{ return GetSignalIndexes(SELL); });
    //std::cout << "Waiting..." << std::flush;
    //futBull.wait();
    //futBear.wait();
    //std::cout << "Done!" << endl;
    const EnjoLib::VecT<int> & idxesBull = futBull.get();
    const EnjoLib::VecT<int> & idxesBear = futBear.get();
    //const EnjoLib::VecT<int> & idxesBull = GetSignalIndexes(BUY);
    //const EnjoLib::VecT<int> & idxesBear = GetSignalIndexes(SELL);

    return EnjoLib::MakePair(idxesBull, idxesBear);
}

EnjoLib::VecT<int> SignalBase::GetSignalIndexes(Direction dir) const
{
    EnjoLib::VecT<int> ret;
    const unsigned sz = Len();
    const StateFactory fact;
    for (unsigned i = 0; i < sz; ++i)
    {
        const State st = *fact.Create(dir, i);
        if (IsSignal(st))
        {
            ret.push_back(i);
        }
    }
    return ret;
}

int SignalBase::Len() const
{
    if (m_len == 0)
        m_len = LenProt();
    if (m_len < 0)
        m_len = 0;
    return m_len;
}

// For testing
bool SignalBase::IsSignalBetween(const State & st1, const State & st2) const
{
    State past = st1;
    State present = st2;
    if (past.i < present.i)
        AlgoSTDThin().Swap(past, present);
    for (State st = present; st.i <= past.i; ++st)
    {
        if (IsSignal(st))
            return true;
    }
    return false;
}

int SignalBase::GetSignalStart(const State & st) const
{
    if (not IsSignal(st))
    {
        EnjoLib::Osstream oss;
        oss << "Check IsSignal() first! " << st;
        throw EnjoLib::ExceptRuntimeError(STRACE_THROW(oss.str()));
    }
    return GetSignalStartProt(st);
}

int SignalBase::GetSignalStartProt(const State & st) const
{
    return -1;
}

EnjoLib::Str SignalBase::GetClassName() const
{
    return typeid(*this).name();
}
