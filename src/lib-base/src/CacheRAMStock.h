#ifndef CacheRAMStock1_H
#define CacheRAMStock1_H

#include "ICacheRAMStock.h"
#include "State.h"
#include "Statistical/Assertions.hpp"
#include <STD/Map.hpp>

template <class TCalcRes>
class CacheRAMStock : public ICacheRAMStock<TCalcRes>
{
    public:
        CacheRAMStock(){}
        virtual ~CacheRAMStock(){}

        const TCalcRes & GetRes(const State & st, const ICalcsCacheRes<TCalcRes> & calculatable) override;

    protected:

    private:
        std::map<int, TCalcRes> m_cacheBull;
        std::map<int, TCalcRes> m_cacheBear;
};

template <class TCalcRes>
const TCalcRes & CacheRAMStock<TCalcRes>::GetRes(const State & st, const ICalcsCacheRes<TCalcRes> & icalcs)
{
    auto * cache = st.bullish ? &m_cacheBull : &m_cacheBear;
    if (ICacheRAMStock<TCalcRes>::IsDirSingle()) cache = &m_cacheBull;

    const int key = st.i;
    auto it = cache->find(key);
    if (it == cache->end())
    {
        const TCalcRes & res = icalcs.CalcForCache(st);
        const auto pairInserted = cache->emplace(key, res);
        if (not pairInserted.second)
        {
            EnjoLib::Assertions::Throw("Couldn't insert for key = ", key, "CacheRAMStock<TCalcRes>::GetRes");
            //throw EnjoLib::ExceptRuntimeError("CacheRAMStock<TCalcRes>::GetRes: Couldn't insert for key = " + std::to_string(key) );
        }
        return pairInserted.first->second;
    }
    return it->second;
}

#endif // CacheRAMStock1_H
