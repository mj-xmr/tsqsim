#include "SymbolFactoryClean.h"
#include "Symbol.cpp"
#include "PeriodClean.h"
#include <Util/VecStr.hpp>

SymbolFactoryClean::SymbolFactoryClean(){}

Corrade::Containers::Pointer<ISymbol> SymbolFactoryClean::Create(const EnjoLib::Str & name, const VecStr & periodNames, bool isMetaTrader, float spread) const
{
    return Corrade::Containers::Pointer<ISymbol>(new Symbol<PeriodClean>(name, periodNames, isMetaTrader, spread));
}

Corrade::Containers::Pointer<ISymbol> SymbolFactoryClean::Create(const EnjoLib::Str & name, bool isMetaTrader, float spread) const
{
    return Create(name, VecStr(), isMetaTrader, spread);
}
