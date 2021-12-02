#ifndef PERIODUTIL_H
#define PERIODUTIL_H

#include <Template/CorradePointerFwd.h>
#include "typesStr.h"
#include <Util/Str.hpp>

class IDataProvider;
class SymbolFactoryAbstract;
class ISymbol;
class ITicks;

class PeriodUtil
{
    public:
        PeriodUtil();
        virtual ~PeriodUtil(){}

        EnjoLib::Str Data2Str(const IDataProvider & data) const;
        Corrade::Containers::Pointer<ISymbol> LoadSymbolFromFile(const SymbolFactoryAbstract & symFact, const EnjoLib::Str & symName, const VecStr & periodName, const EnjoLib::Str & fileName, bool calcTech) const;
        Corrade::Containers::Pointer<ISymbol> LoadSymbolFromFileFeed(const SymbolFactoryAbstract & symFact, const EnjoLib::Str & symName, const VecStr & periodName, const EnjoLib::Str & fileName, bool calcTech) const;
        Corrade::Containers::Pointer<ISymbol> LoadSymbolFromFileSetCan(const SymbolFactoryAbstract & symFact, const EnjoLib::Str & symName, const VecStr & periodName, const EnjoLib::Str & fileName, bool calcTech) const;

        Corrade::Containers::Pointer<ISymbol> LoadSymbolFromFileMT(const SymbolFactoryAbstract & symFact, const EnjoLib::Str & symName, const VecStr & periodName, const EnjoLib::Str & fileName, bool calcTech) const;
    protected:

    private:
        Corrade::Containers::Pointer<ISymbol> LoadSymbolFromFileCommon(const SymbolFactoryAbstract & symFact, bool feed, const EnjoLib::Str & symName, const VecStr & periodName, const EnjoLib::Str & fileName, bool calcTech) const;
        Corrade::Containers::Pointer<ISymbol> LoadSymbolFromFileCommon(const SymbolFactoryAbstract & symFact, bool feed, const EnjoLib::Str & symName, const VecStr & periodName, const EnjoLib::Str & fileName, const ITicks & ticks, bool calcTech) const;
};

#endif // PERIODUTIL_H
