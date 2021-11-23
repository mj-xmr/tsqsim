#ifndef IPRICEFILTER_H
#define IPRICEFILTER_H

#include "typesVec.h"
//#include <3rdParty/stdfwd.hh>

class Candle;
class IDataProvider;
class PriceFilterConfig;

class IPriceFilter
{
    public:
        IPriceFilter();
        virtual ~IPriceFilter(){}

        virtual VecCan Filter(const PriceFilterConfig & cfg, const IDataProvider & per) const = 0;

    protected:

    private:
};

#endif // IPRICEFILTER_H
