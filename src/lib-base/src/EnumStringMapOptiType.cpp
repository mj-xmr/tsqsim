#include "EnumStringMapOptiType.h"
#include <OptiType.h>
#include <OptiGoalType.h>

EnumStringMapOptiType::~EnumStringMapOptiType(){}
EnumStringMapOptiType::EnumStringMapOptiType()
{
    for (int i = 0; i <= int(OptiType::OPTI_TYPE_USE); ++i)
    {
        OptiType type = OptiType(i);
        switch (type) // Generate compiler warnings
        {
            case OptiType::OPTI_TYPE_NONE:  Add(i, "None"); break;
            case OptiType::OPTI_TYPE_FIND:  Add(i, "Find"); break;
            case OptiType::OPTI_TYPE_USE:   Add(i, "Use");  break;
        }
    }
}

EnumStringMapOptiMethod::~EnumStringMapOptiMethod(){}
EnumStringMapOptiMethod::EnumStringMapOptiMethod()
{
    for (int i = 0; i <= int(OptiMethod::OPTI_METHOD_NELDER); ++i)
    {
        OptiMethod type = OptiMethod(i);
        switch (type) // Generate compiler warnings
        {
            case OptiMethod::OPTI_METHOD_GRID:       Add(i, "Grid");        break;
            case OptiMethod::OPTI_METHOD_MONTECARLO: Add(i, "MonteCarlo");  break;
            case OptiMethod::OPTI_METHOD_NELDER:     Add(i, "Nelder");      break;
        }
    }
}

EnumStringMapOptiGoalType::~EnumStringMapOptiGoalType(){}
EnumStringMapOptiGoalType::EnumStringMapOptiGoalType()
{
    for (int i = 0; i <= int(OptiGoalType::SUM); ++i)
    {
        OptiGoalType type = OptiGoalType(i);
        switch (type) // Generate compiler warnings
        {
            case OptiGoalType::BALANCED:        Add(i, "Balanced");        break;
            case OptiGoalType::EXPERIMENTAL:    Add(i, "Experim");        break;
            case OptiGoalType::SHARPE:          Add(i, "Sharpe");        break;
            case OptiGoalType::PROFIT_FACTOR:   Add(i, "Prof. fac");        break;
            //case OptiGoalType::PROC:            return CorPtr<IOptiGoal>(new OptiGoalSum);
            case OptiGoalType::SUM:             Add(i, "Sum");        break;
            case OptiGoalType::MEDIAN:          Add(i, "Median");        break;
        }
    }
}
