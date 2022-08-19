#ifndef IINDICATORAGGREGATE_H
#define IINDICATORAGGREGATE_H

#include "IHasLen.h"
//#include <Util/Bool3State.hpp>
#include <Template/VecT.hpp>
#include <Template/ArrayFwd.hpp>
#include <Util/StrFwd.hpp>
#include <Util/Pair.hpp>
#include "Direction.h"
#include <3rdParty/stdfwd.hh>

class State;
class ISignal : public IHasLen
{
    public:
        ISignal();
        virtual ~ISignal();

        virtual int GetPosLastSignal(const State & st) const = 0;
        virtual int GetPosPrevSignal(const State & st) const = 0;
        virtual bool IsSignal(const State & st) const = 0;
        virtual bool IsSignalBetween(const State & st1, const State & st2) const = 0;
        virtual float GetValue(const State & st) const;
        virtual EnjoLib::VecT<int> GetSignalIndexes(Direction dir) const = 0;
        virtual EnjoLib::Pair<EnjoLib::VecT<int>, EnjoLib::VecT<int>> GetSignalIndexes() const = 0;
        virtual EnjoLib::Array<State> GetSignalStates() const = 0;
        virtual EnjoLib::Str GetSpecialText(const State & st) const;
        virtual float GetSpecialPrediction(const State & st) const { return 0; }
        virtual int GetSignalStart(const State & st) const = 0;

    protected:
        virtual bool IsSignalProt(const State & st) const = 0;
        virtual unsigned LenProt() const = 0;
        virtual bool UseCache() const = 0;
        virtual int GetSignalStartProt(const State & st) const = 0;
        //virtual bool UseCache() const {return false;}
        //bool UseCache() const override {return false;}
        //virtual float GetFilter() const {return 50;}

        virtual bool HandleCacheVector(const State & st, EnjoLib::VecT<int> & cache) const = 0;
        virtual int GetLastPosCacheVector(const State & st, EnjoLib::VecT<int> & cache) const = 0;
    private:

};

#endif // IINDICATORAGGREGATE_H
