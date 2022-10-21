#include "TicksProviderFactory.h"

#include <Util/Except.hpp>
#include <Util/Str.hpp>
#include <Template/CorradePointer.h>

#include "TicksProviderBinary.h"
#include "TicksProviderXMR.h"
#include "TicksProviderFake.h"
#include "TicksProviderGenerated.h"
#include "TicksProviderAdaptive.h"
#include "TicksProviderAdaptiveFake.h"
#include "TicksProviderTxtAdHoc.h"

TickProviderFactory::TickProviderFactory(){}
TickProviderFactory::~TickProviderFactory(){}

CorPtr<ITicksProvider> TickProviderFactory::Create(TickProviderType type) const
{
    switch (type)
    {
    case TickProviderType::ARCHIVER:
        return CorPtr<ITicksProvider>(new TicksProviderAdaptive());
    case TickProviderType::SMALL:
        return CorPtr<ITicksProvider>(new TicksProviderFake());
    case TickProviderType::GENERATED:
        return CorPtr<ITicksProvider>(new TicksProviderGenerated());
    case TickProviderType::XMR_FAKE:
        return CorPtr<ITicksProvider>(new TicksProviderXMRFake());
    case TickProviderType::XMR:
    //   return CorPtr<ITicksProvider>(new TicksProviderAdaptive());
        return CorPtr<ITicksProvider>(new TicksProviderXMR());
    case TickProviderType::DATA_FILE:
        return CorPtr<ITicksProvider>(new TicksProviderTxtAdHoc());    
    case TickProviderType::ADAPTIVE:
        return CorPtr<ITicksProvider>(new TicksProviderAdaptive());
    case TickProviderType::ADAPTIVE_FAKE:
        return CorPtr<ITicksProvider>(new TicksProviderAdaptiveFake());
    }
    throw EnjoLib::ExceptRuntimeError("Not handled type ");
}
