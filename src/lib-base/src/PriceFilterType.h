#ifndef PRICEFILTERTYPE_H
#define PRICEFILTERTYPE_H

#include <Util/EnumClassWrapper.hpp>

enum PriceFilterTypeEnum
{
    PRICE_FILTER_EMPTY_BARS,
    PRICE_FILTER_SPREAD_MUL,
};

// Saves compilation time on new enum members
class PriceFilterType : public EnjoLib::EnumClassWrapper<PriceFilterTypeEnum>
{
public:
    using EnumClassWrapper::EnumClassWrapper; // Constructor inheritance
};

#endif // PRICEFILTERTYPE_H
