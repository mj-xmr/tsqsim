#ifndef IPARAMS1_H
#define IPARAMS1_H

#include <Util/Str.hpp>

class ISimulatorAccum;
class ISymbol;
class IPeriod;
class StrategyType;

class IParams
{
    public:
        IParams();
        virtual ~IParams();

        virtual ISimulatorAccum * GetAccum() const = 0;
        virtual const IPeriod & GetPeriod() const = 0;
        virtual const StrategyType & GetStrategy() const = 0;
        virtual const ISymbol & GetSymbol() const = 0;
        virtual EnjoLib::Str operator()() const = 0;
        virtual EnjoLib::Str GetName() const = 0;

        EnjoLib::Str ToStr() const;

    protected:

    private:
};

#endif // IPARAMS1_H
