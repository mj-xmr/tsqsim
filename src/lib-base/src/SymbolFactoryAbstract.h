#ifndef SYMBOLFACTORYABSTRACT_H
#define SYMBOLFACTORYABSTRACT_H

#include <3rdParty/stdfwd.hh>
#include <Util/VecStr.hpp>
#include <Template/CorradePointerFwd.h>

class ISymbol;

class SymbolFactoryAbstract
{
    public:
        SymbolFactoryAbstract();
        virtual ~SymbolFactoryAbstract();

        virtual Corrade::Containers::Pointer<ISymbol> Create(const EnjoLib::Str & name, 
                                                             const VecStr & periodNames,
                                                bool isMetaTrader = false, float spread = 0) const = 0;
        virtual Corrade::Containers::Pointer<ISymbol> Create(const EnjoLib::Str & name, 
                                                bool isMetaTrader = false, float spread = 0) const = 0;

    protected:

    private:
};

#endif // SYMBOLFACTORYABSTRACT_H
