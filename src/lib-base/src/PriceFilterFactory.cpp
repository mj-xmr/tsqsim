#include "PriceFilterFactory.h"
#include "PriceFilterType.h"
#include "IPriceFilter.h"
#include "PriceFilterSpreadMul.h"
#include "PriceFilterEmptyBars.h"
#include <Template/CorradePointer.h>
#include <Util/Except.hpp>

PriceFilterFactory::PriceFilterFactory(){}

Corrade::Containers::Pointer<IPriceFilter> PriceFilterFactory::Create(const PriceFilterType & type) const
{
    IPriceFilter * filter = nullptr;
    switch (type.GetType())
    {
        case PRICE_FILTER_EMPTY_BARS:       filter = new PriceFilterEmptyBars(); break;
        case PRICE_FILTER_SPREAD_MUL:       filter = new PriceFilterSpreadMul(); break;
    }
    if (filter == nullptr)
        throw EnjoLib::ExceptInvalidArg("PriceFilterFactory::Create(): Not defined the filter");

    return Corrade::Containers::Pointer<IPriceFilter>(filter);
}
