#ifndef MAINTESTERUTIL_H
#define MAINTESTERUTIL_H

#include <3rdParty/stdfwd.hh>
#include <Util/Str.hpp>
#include <Template/UniquePtrVecFwd.hpp>

class ConfigTF2;
class ConfigSym;
class ISymbol;
class ITicksProvider;
class ITicks;

class MainTesterUtil
{
    public:
        MainTesterUtil(const ConfigTF2 * confTF2, ISymbol * sym, std::ostream & log);
        virtual ~MainTesterUtil(){}

        void RestoreTicks(const ITicksProvider * tickProvider, const ConfigSym * confSym) const;
        void FilterBySpread() const;
        CorPtr<ITicks> Filter(EnjoLib::Str symbolName, const ITicks & ticks, const ConfigSym * confSym) const;
        static STDFWD::vector<ISymbol*> SortISymbolsGrowing(const STDFWD::vector<ISymbol*> & vecSyms);


    protected:

    private:
        const ConfigTF2 * m_confTF2 = nullptr;
        ISymbol * m_sym = nullptr;
        std::ostream & m_log;
};

#endif // MAINTESTERUTIL_H
