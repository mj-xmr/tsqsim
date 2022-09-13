#include "EnumStringMapDistType.hpp"
#include <Util/Str.hpp>
#include "DTWDistType.h"

EnumStringMapDistType::EnumStringMapDistType()
{
    for (int i = 0; i <= int(DTWDistType::KNNType); ++i)
    {
        DTWDistType type = DTWDistType(i);
        switch (type) // Generate compiler warnings
        {
            case DTWDistType::KNNType:     Add(i, "Dist KNN"); break;
            case DTWDistType::DTWType:     Add(i, "Dist DTW"); break;
        }
    }
}

EnumStringMapDistType::~EnumStringMapDistType()
{
    //dtor
}
