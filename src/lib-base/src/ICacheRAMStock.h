#ifndef ICACHERAMSTOCK_H
#define ICACHERAMSTOCK_H

#include <Template/SafePtr.hpp>

class State;
template <class TCalcRes>
struct ICalcsCacheRes
{
    virtual TCalcRes CalcForCache(const State & st) const = 0;
    virtual ~ICalcsCacheRes(){}
};

template <class TCalcRes>
class ICacheRAMStock
{
    public:
        ICacheRAMStock(){}
        virtual ~ICacheRAMStock(){}

        virtual const TCalcRes & GetRes(const State & st, const ICalcsCacheRes<TCalcRes> & calculatable) = 0;
        void SetDirSingle() { m_isSingleDir = true; }
        bool IsDirSingle () const { return m_isSingleDir; }

    protected:

    private:
        bool m_isSingleDir = false;
};

#endif // ICACHERAMSTOCK_H
