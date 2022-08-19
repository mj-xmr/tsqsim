#include "EnumStringMapDataSrc.h"

#include <Util/Str.hpp>
#include "DataSrcType.h"

EnumStringMapDataSrc::EnumStringMapDataSrc()
{
    for (int i = 0; i <= int(DataSrcType::GENERATED); ++i)
    {
        DataSrcType type = DataSrcType(i);
        switch (type) // Generate compiler warnings
        {
            case DataSrcType::FOREX_TESTER: Add(i, "FX"); break;
            case DataSrcType::MONERO:       Add(i, "XMR"); break;
            case DataSrcType::GENERATED:    Add(i, "Gen"); break;
        }
    }
}

EnumStringMapDataSrc::~EnumStringMapDataSrc()
{
    //dtor
}
