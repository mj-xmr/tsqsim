#include "EnumStringMapRDEType.hpp"
#include "RDEType.h"

EnumStringMapRDEType::EnumStringMapRDEType()
{
    for (int i = 0; i <= int(RDEType::RDE_NONE); ++i)
    {
        RDEType type = RDEType(i);
        switch (type) // Generate compiler warnings
        {
            case RDEType::RDE_AUTO:     Add(i, "RDE Auto"); break;
            case RDEType::RDE_LABELS:   Add(i, "RDE Labs"); break;
            case RDEType::RDE_NONE:     Add(i, "RDE Off"); break;
        }
    }
}

EnumStringMapRDEType::~EnumStringMapRDEType()
{
    //dtor
}
