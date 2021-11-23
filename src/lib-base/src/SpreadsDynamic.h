#ifndef SPREADSDYNAMIC_H
#define SPREADSDYNAMIC_H

#include <Util/Str.hpp>
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
