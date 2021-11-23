#ifndef MAINTESTER_H
#define MAINTESTER_H

#include "IMainTester.h"
#include "ITicks.h"
#include "TicksProviderFactory.h"

#include <Template/SafePtr.hpp>
#include <Template/UniquePtrVecFwd.hpp>

#include <3rdParty/stdfwd.hh>

#include <STD/Set.hpp>
#include <3rdParty/stdfwd.hh>
#include <mutex>
#include <atomic>

class ISymbol;
class ConfigSym;
class ConfigTF2;
//class Ticks;
class ITicksProvider;
class SymbolFactoryAbstract;
class MainTester : public IMainTester
{
    public:
        //typedef VecStr VecStr;
        //typedef std::set<EnjoLib::Str> SetStr;

        virtual ~MainTester();
        void SetFake() override;
        void SetProvider(const TickProviderType & provType) override;

        CorPtr<ISymbol> GetSymbol(EnjoLib::Str symbol, const VecStr & periodNames = VecStr()) const override;
        VecUPtr<ISymbol> GetSymbolMT(const VecStr & symbolNames, const VecStr & periodNames = VecStr{}, const SetStr & blacklist = SetStr{}, bool useBlacklist = true) const override;
        VecUPtr<ISymbol> GetSymbolPerMT(const EnjoLib::Array<EnjoLib::Pair<EnjoLib::Str, EnjoLib::Str>> & symbolPerNames) const override;


        static CorPtr<ISymbol> GetSymbolStatic(int id, const MainTester * instance, const EnjoLib::Str & symbolName, const VecStr & periodNames);

    protected:
        friend class IMainTester;
        MainTester(const SymbolFactoryAbstract & symFact, const ConfigTF2 * m_confTF2, const ConfigSym * confSym = nullptr, bool verbose = true);

    private:
        void ArchiveSymbol(EnjoLib::Str symbolName, const ITicksProvider * tickProvider) const;
        bool IsMultithreaded(const VecStr & symbolNames) const;
        bool IsPeriodMissing(EnjoLib::Str symbolName) const;


        const ConfigTF2 * m_confTF2;
        const ConfigSym * m_confSym;

        static std::mutex m_counterMutex;
        static std::atomic<bool> m_isReady;
        static int m_counter;

        const SymbolFactoryAbstract & m_symFact;
        std::ostream & m_log;
        TickProviderType m_tickProvType = TickProviderType::ARCHIVER;
        mutable EnjoLib::Str lastSymbol, lastPeriod;
        mutable CorPtr<ITicks> m_cacheTicks;

};

#endif // MAINTESTER_H
