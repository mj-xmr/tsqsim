#ifndef SYMBOLFACTORY_CLEAN_H
#define SYMBOLFACTORY_CLEAN_H

#include "SymbolFactoryAbstract.h"
#include "ISymbol.h"

#include <Template/CorradePointer.h>

class SymbolFactoryClean : public SymbolFactoryAbstract
{
    public:
        SymbolFactoryClean();
        virtual ~SymbolFactoryClean(){}
                                        
        Corrade::Containers::Pointer<ISymbol> Create(const EnjoLib::Str & name, 
                                                             const VecStr & periodNames,
                                                bool isMetaTrader = false, float spread = 0) const override;
        Corrade::Containers::Pointer<ISymbol> Create(const EnjoLib::Str & name, 
                                                bool isMetaTrader = false, float spread = 0) const override;
    protected:
    private:
};

#endif // SYMBOLFACTORY_H
