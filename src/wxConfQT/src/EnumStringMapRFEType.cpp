#include "EnumStringMapRFEType.hpp"
#include "RFEType.h"

EnumStringMapRFEType::~EnumStringMapRFEType(){}
EnumStringMapRFEType::EnumStringMapRFEType()
{
    for (int i = 0; i <= int(RFEType::RFE_FAKE); ++i)
    {
        const RFEType type = RFEType(i);
        switch (type) // Generate compiler warnings
        {
            case RFEType::RFE_FULL:     Add(i, "RFE Full"); break;
            case RFEType::RFE_NELDER:   Add(i, "RFE Nelder"); break;
            case RFEType::RFE_PCA:      Add(i, "RFE PCA"); break;
            case RFEType::RFE_PCA_OPTI: Add(i, "RFE PCA Opti"); break;
            case RFEType::RFE_PCA_CUT:  Add(i, "RFE PCA Cut"); break;
            //case RFEType::RFE_REM_ERR:  Add(i, "RFE Rem Err"); break;
            case RFEType::RFE_FAKE:     Add(i, "RFE Fake"); break;
        }
    }
}
