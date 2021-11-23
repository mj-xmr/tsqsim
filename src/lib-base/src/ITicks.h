#ifndef ITICKS_HPP
#define ITICKS_HPP

#include "typesVec.h"
#include <3rdParty/stdfwd.hh>
#include <Template/CorradePointer.h>
#include <Template/IIterable.hpp>
#include <Template/View.hpp>

class Candle;
class Tick;

class ITicks : public EnjoLib::IIterableConst<Tick>
{
public:
    virtual ~ITicks();
    
    static CorPtr<ITicks> Create();
    
    virtual const stdfwd::vector<Tick> & GetTicks3() const = 0;
    virtual EnjoLib::View<Tick> GetTicksView() const = 0;
    
    virtual CorPtr<ITicks> FromYear(int year) const = 0;
    virtual CorPtr<ITicks> TillYear(int year) const = 0;
    virtual CorPtr<ITicks> BetweenYears(int yearStart, int yearEnd) const = 0;
    virtual CorPtr<ITicks> FromMonth(int month, int year) const = 0;
    virtual CorPtr<ITicks> TillMonth(int month, int year) const = 0;
    virtual CorPtr<ITicks> DeleteMonth(int month, int year) const = 0;
    virtual bool HasMonth(int month, int year) const = 0;
    virtual void Set(const ITicks & ticks) = 0;
    virtual void Add(const ITicks & ticks) = 0;
    virtual void Add(const Tick & tick) = 0;

    virtual VecCan ToCandles() const = 0;
};

#endif // ITICKS_HPP
