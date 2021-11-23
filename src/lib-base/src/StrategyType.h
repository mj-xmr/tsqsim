#ifndef STRATEGYTYPE_H_INCLUDED
#define STRATEGYTYPE_H_INCLUDED

#include <Util/EnumClassWrapper.hpp>

namespace StrategyFactory
{
    enum class Type : int;
};

// Saves compilation time on new enum members
class StrategyType : public EnjoLib::EnumClassWrapper<StrategyFactory::Type>
{
public:
    using EnumClassWrapper::EnumClassWrapper; // Constructor inheritance
};


#endif // STRATEGYTYPE_H_INCLUDED
