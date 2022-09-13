#ifndef STRATEGYFACTORYNAME_H
#define STRATEGYFACTORYNAME_H

class StrategyType;
#include <Util/StrFwd.hpp>
#include <3rdParty/stdfwd.hh>

class StrategyFactoryName
{
    public:
        StrategyFactoryName(){}
        virtual ~StrategyFactoryName(){}

        EnjoLib::Str Create(const StrategyType & type) const;
        StrategyType NameToType(const EnjoLib::Str & name) const;

    protected:

    private:
};

#endif // STRATEGYFACTORYNAME_H
