#ifndef IMAINTESTER_H
#define IMAINTESTER_H

#include <Template/CorradePointerFwd.h>
#include <Template/UniquePtrVecFwd.hpp>

//#include "types.h"
#include <Util/VecStr.hpp>
#include <Util/Pair.hpp>
#include <Template/ArrayFwd.hpp>

#include <STD/Set.hpp>
#include <3rdParty/stdfwd.hh>

class ConfigTF2;
class ConfigSym;
class ISymbol;
class SymbolFactoryAbstract;
enum class TickProviderType;

class IMainTester
{
    public:
        IMainTester();
        virtual ~IMainTester();

        static CorPtr<IMainTester> Create(const SymbolFactoryAbstract & symFact,
                const ConfigTF2 * m_confTF2, const ConfigSym * confSym = nullptr, bool verbose = true);

        using SetStr = std::set<EnjoLib::Str>;

        virtual void SetFake() = 0;
        virtual void SetProvider(const TickProviderType & provType) = 0;
        virtual CorPtr<ISymbol> GetSymbol(EnjoLib::Str symbol, const VecStr & periodNames = VecStr()) const = 0;
        virtual VecUPtr<ISymbol> GetSymbolMT(const VecStr & symbolNames, const VecStr & periodNames = VecStr{}, const SetStr & blacklist = SetStr{}, bool useBlacklist = true) const = 0;
        virtual VecUPtr<ISymbol> GetSymbolPerMT(const EnjoLib::Array<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> & symbolPerNames) const = 0;

    protected:

    private:
};

#endif // IMAINTESTER_H
