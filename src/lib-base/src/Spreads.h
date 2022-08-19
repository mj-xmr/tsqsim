#ifndef SPREADS_H
#define SPREADS_H

#include <3rdParty/stdfwd.hh>
#include <Util/StrFwd.hpp>
#include <Util/Pimpl.hpp>

class Spreads
{
    public:
        Spreads();
        virtual ~Spreads();
        float GetSpread(const EnjoLib::Str & symbolName, double currentPrice) const;
    protected:
    private:
        PIMPL
};

#endif // SPREADS_H
