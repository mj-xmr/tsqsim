#include "TSXformTypeString.h"
#include "TSXformType.h"

#include <Util/Str.hpp>

TSXformTypeString::~TSXformTypeString(){}
TSXformTypeString:: TSXformTypeString()
{
    for (int i = 0; i <= int(TSXformType::END); ++i)
    {
        TSXformType type = TSXformType(i);
        switch (type) // Generate compiler warnings
        {
            case TSXformType::ORIG:     Add(i, "orig"); break;
            case TSXformType::DIFF:     Add(i, "diff"); break;
            case TSXformType::FABS:     Add(i, "fabs"); break;
            case TSXformType::SQRTS:    Add(i, "sqrt"); break;
            case TSXformType::LOGS:     Add(i, "log"); break;
            case TSXformType::ADD:      Add(i, "add"); break;
            case TSXformType::MUL:      Add(i, "mul"); break;
            case TSXformType::DIV:      Add(i, "div"); break;
            //case TSXformType::POW:      Add(i, "pow"); break;
            case TSXformType::END:      Add(i, "end"); break;
        }
    }
}
