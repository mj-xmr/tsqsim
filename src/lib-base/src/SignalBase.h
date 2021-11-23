#ifndef SIGNALBASE_H
#define SIGNALBASE_H

#include <ISignal.h>
#include "State.h"
#include <Template/SafePtrFast.hpp>
#include <Template/VecT.hpp>
//#include <vector>
//#include <mutex>

namespace std
{
    class mutex;
}

struct SignalBaseImpl;
class SignalBase : public ISignal
{
    public:
        SignalBase();
        virtual ~SignalBase();

        int GetPosLastSignal(const State & st) const override;
        int GetPosPrevSignal(const State & st) const override;
        bool IsSignal(const State & st) const override;
        bool IsSignalBetween(const State & st1, const State & st2) const override;
        int Len() const override;
        EnjoLib::VecT<int> GetSignalIndexes(Direction dir) const override;
        EnjoLib::Pair<EnjoLib::VecT<int>, EnjoLib::VecT<int>> GetSignalIndexes() const override;
        EnjoLib::Array<State> GetSignalStates() const override;
        int GetSignalStart(const State & st) const override;
        
        SignalBase & operator = (const SignalBase & other);

    protected:
        virtual bool UseCache() const override;
        bool HandleCacheVector(const State & st, EnjoLib::VecT<int> & cache) const override;
        int GetLastPosCacheVector(const State & st, EnjoLib::VecT<int> & cache) const override;
        virtual int GetSignalStartProt(const State & st) const override;

    private:

        void Init(Direction dir) const;
        EnjoLib::Str GetClassName() const;
        
        mutable EnjoLib::SafePtrFast<SignalBaseImpl> m_pimp;

        mutable int m_len = 0;
        mutable bool m_inited = false;
        //mutable EnjoLib::SafePtr<std::mutex> m_mutexBuy, m_mutexSell; // Could be making problems? Doesn't appear to be
        //mutable std::mutex m_mutexBuy, m_mutexSell; // Original
};

#endif // SIGNALBASE_H
