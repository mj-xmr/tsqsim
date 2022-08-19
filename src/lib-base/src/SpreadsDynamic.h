#ifndef SPREADSDYNAMIC_H
#define SPREADSDYNAMIC_H

#include <Util/StrFwd.hpp>
#include <Util/Pimpl.hpp>

class SpreadsDynamic
{
    public:
        SpreadsDynamic();
        virtual ~SpreadsDynamic(){}

        double GetSpread(const EnjoLib::Str & symbolName, double currentPrice) const;

    protected:

    private:
        PIMPL
};

#endif // SPREADSDYNAMIC_H
