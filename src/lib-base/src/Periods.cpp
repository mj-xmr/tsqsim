#include "Periods.h"
#include "PeriodClean.h"
////#include "ConfigGlob.h"

template <class T> Minute1<T>::Minute1    (const ISymbol & sym): T(PeriodType::M1,    sym){}
template <class T> Minute5<T>::Minute5    (const ISymbol & sym): T(PeriodType::M5,    sym){}
template <class T> Minute15<T>::Minute15  (const ISymbol & sym): T(PeriodType::M15,   sym){}
template <class T> Minute30<T>::Minute30  (const ISymbol & sym): T(PeriodType::M30,   sym){}
template <class T> Hour1<T>::Hour1        (const ISymbol & sym): T(PeriodType::H1,   sym){}
template <class T> Hour2<T>::Hour2        (const ISymbol & sym): T(PeriodType::H2,  sym){}
template <class T> Hour4<T>::Hour4        (const ISymbol & sym): T(PeriodType::H4,  sym){}
template <class T> Hour8<T>::Hour8        (const ISymbol & sym): T(PeriodType::H8,  sym){}
template <class T> Hour12<T>::Hour12      (const ISymbol & sym): T(PeriodType::H12,  sym){}
template <class T> Day<T>::Day            (const ISymbol & sym): T(PeriodType::D,   sym){}
template <class T> Week<T>::Week          (const ISymbol & sym): T(PeriodType::W, sym){}
template <class T> Month<T>::Month        (const ISymbol & sym): T(PeriodType::M, sym){}

template <class T> float Minute1<T>:: GetMaxLossPercent() const { return 0.5; }
template <class T> float Minute5<T>:: GetMaxLossPercent() const { return 0.5; }
template <class T> float Minute15<T>::GetMaxLossPercent() const { return 0.3; }
template <class T> float Minute30<T>::GetMaxLossPercent() const { return 0.5; }
template <class T> float Hour1<T>::   GetMaxLossPercent() const { return 0.5; }
template <class T> float Hour2<T>::   GetMaxLossPercent() const { return 0.5; }
template <class T> float Hour4<T>::   GetMaxLossPercent() const { return 0.5; }
template <class T> float Hour8<T>::   GetMaxLossPercent() const { return 0.5; }
template <class T> float Hour12<T>::  GetMaxLossPercent() const { return 0.5; }
template <class T> float Day<T>::     GetMaxLossPercent() const { return 0.5; }
template <class T> float Week<T>::    GetMaxLossPercent() const { return 0.5; }
template <class T> float Month<T>::   GetMaxLossPercent() const { return 0.5; }

/*
template <class T> float Minute15<T>::GetTPRatio() const
{
    return 2.1; // Divergence
    //return 4;
    //return 200;
}

template <class T> float Hour1<T>::GetTPRatio() const
{
    return 3.1;
    //return 20;
}
*/

/*
template class Minute1 <PeriodBase>;
template class Minute5 <PeriodBase>;
template class Minute15<PeriodBase>;
template class Minute30<PeriodBase>;
template class Hour1   <PeriodBase>;
template class Hour2   <PeriodBase>;
template class Hour4   <PeriodBase>;
template class Hour8   <PeriodBase>;
template class Hour12  <PeriodBase>;
template class Day      <PeriodBase>;
*/

template class Minute1 <PeriodClean>;
template class Minute5 <PeriodClean>;
template class Minute15<PeriodClean>;
template class Minute30<PeriodClean>;

template class Hour1   <PeriodClean>;
template class Hour2   <PeriodClean>;
template class Hour4   <PeriodClean>;
template class Hour8   <PeriodClean>;
template class Hour12  <PeriodClean>;

template class Day      <PeriodClean>;
template class Week     <PeriodClean>;
template class Month    <PeriodClean>;

PeriodsAll::PeriodsAll()
{
    const int istart = static_cast<int>(PeriodType::M1);
    const int iend   = static_cast<int>(PeriodType::M);

    for (int i = istart; i <= iend; ++i)
    {
        //periods.push_back(static_cast<PeriodsEnum>(i));
        periods.push_back(i);
    }
}
PeriodsAll::~PeriodsAll(){}
