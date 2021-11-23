#ifndef PRICEFILTERFACTORY_H
#define PRICEFILTERFACTORY_H

#include "IPriceFilter.h"
#include <Util/EnumClassWrapper.hpp>
#include <Template/CorradePointerFwd.h>

//class PriceFilterType;
//template<class T>
class PriceFilterType;

class PriceFilterFactory
{
    public:
        PriceFilterFactory();
        virtual ~PriceFilterFactory(){}

        Corrade::Containers::Pointer<IPriceFilter> Create(const PriceFilterType & type) const;

    protected:

    private:
};

#endif // PRICEFILTERFACTORY_H
