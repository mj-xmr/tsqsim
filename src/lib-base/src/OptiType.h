#ifndef OPTITYPE_H
#define OPTITYPE_H

enum class OptiType
{
    OPTI_TYPE_NONE,
    OPTI_TYPE_USE,
    OPTI_TYPE_FIND,
    OPTI_TYPE_XVALID
};

enum class OptiMethod
{
    OPTI_METHOD_GRID,
    OPTI_METHOD_MONTECARLO,
    OPTI_METHOD_BISECTION
};

#endif // OPTITYPE_H
