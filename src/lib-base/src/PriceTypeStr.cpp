#include "PriceTypeStr.h"
#include "PriceType.h"

#include <Util/Str.hpp>

PriceTypeStr::PriceTypeStr()
{
    for (int i = 0; i <= int(PriceType::TYPICAL); ++i)
    {
        const PriceType type = PriceType(i);
        switch (type) // Generate compiler warnings
        {
            case PriceType::CLOSE:          Add(i, "Close"); break;
            case PriceType::OPEN:           Add(i, "Open"); break;
            case PriceType::LOW:            Add(i, "Low"); break;
            case PriceType::HIGH:           Add(i, "High"); break;
            case PriceType::WEIGHTED_CLOSE: Add(i, "Weighted close"); break;
            case PriceType::TYPICAL:        Add(i, "Typical"); break;
        }
    }
}

PriceTypeStr::~PriceTypeStr()
{
}
