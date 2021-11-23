#ifndef OPTITYPE_H
#define OPTITYPE_H

enum class OptiType
{
    OPTI_TYPE_NONE,
    OPTI_TYPE_FIND,
    OPTI_TYPE_USE
};

enum class OptiMethod
{
    OPTI_METHOD_GRID,
    OPTI_METHOD_MONTECARLO,
    OPTI_METHOD_NELDER
};

#endif // OPTITYPE_H
