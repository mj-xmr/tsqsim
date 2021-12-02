#include "EnumStringMapDataSrc.h"

#include "DataSrcType.h"

EnumStringMapDataSrc::EnumStringMapDataSrc()
{
    for (int i = 0; i <= int(DataSrcType::MONERO); ++i)
    {
        DataSrcType type = DataSrcType(i);
        switch (type) // Generate compiler warnings
        {
            case DataSrcType::FOREX_TESTER: Add(i, "FX"); break;
            case DataSrcType::MONERO:       Add(i, "XMR"); break;
        }
    }
}

EnumStringMapDataSrc::~EnumStringMapDataSrc()
{
    //dtor
}
