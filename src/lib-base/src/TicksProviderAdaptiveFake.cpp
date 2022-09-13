#include "TicksProviderAdaptiveFake.h"

#include "TicksProviderFake.h"
#include "ITicks.h"

TicksProviderAdaptiveFake::TicksProviderAdaptiveFake(){}
TicksProviderAdaptiveFake::~TicksProviderAdaptiveFake(){}


CorPtr<ITicks> TicksProviderAdaptiveFake::GetTicks(const EnjoLib::Str & symbolName, const ConfigSym * confSym) const
{
    return CorPtr<ITicks>(TicksProviderFake().GetTicks(symbolName, confSym).release());
}
CorPtr<ITicks> TicksProviderAdaptiveFake::GetPeriod(const EnjoLib::Str & symbolName, const EnjoLib::Str & periodName) const
{
    return CorPtr<ITicks>(TicksProviderFake().GetPeriod(symbolName, periodName).release());
}
