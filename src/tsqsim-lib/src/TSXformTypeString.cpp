#include "TSXformTypeString.h"

#include "TSXformType.h"

TSXformTypeString::~TSXformTypeString(){}
TSXformTypeString:: TSXformTypeString()
{
    for (int i = 0; i <= int(TSXformType::END); ++i)
    {
        TSXformType type = TSXformType(i);
        switch (type) // Generate compiler warnings
        {
            case TSXformType::DIFF:     Add(i, "diff"); break;
            case TSXformType::FABS:     Add(i, "fabs"); break;
            case TSXformType::SQRT:     Add(i, "sqrt"); break;
            case TSXformType::SQRTS:    Add(i, "sqrts"); break;
            case TSXformType::LOGS:     Add(i, "logs"); break;
            case TSXformType::ADD:      Add(i, "add"); break;
            //case TSXformType::POW:      Add(i, "pow"); break;
            case TSXformType::END:      Add(i, "end"); break;
        }
    }
}
