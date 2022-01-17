#include "TicksProviderFactory.h"

#include <Util/Except.hpp>
#include <Util/Str.hpp>
#include <Template/CorradePointer.h>

#include "TicksProviderBinary.h"
#include "TicksProviderXMR.h"
#include "TicksProviderFake.h"
#include "TicksProviderGenerated.h"

TickProviderFactory::TickProviderFactory()
{
    //ctor
}

TickProviderFactory::~TickProviderFactory()
{
    //dtor
}

Corrade::Containers::Pointer<ITicksProvider> TickProviderFactory::Create(TickProviderType type) const
{
    switch (type)
    {
    case TickProviderType::ARCHIVER:
        return Corrade::Containers::Pointer<ITicksProvider>(new TicksProviderBinary());
    case TickProviderType::SMALL:
        return Corrade::Containers::Pointer<ITicksProvider>(new TicksProviderFake());
    case TickProviderType::GENERATED:
        return Corrade::Containers::Pointer<ITicksProvider>(new TicksProviderGenerated());
    case TickProviderType::XMR_FAKE:
        return Corrade::Containers::Pointer<ITicksProvider>(new TicksProviderXMRFake());
    case TickProviderType::XMR:
        return Corrade::Containers::Pointer<ITicksProvider>(new TicksProviderXMR());
    }
    throw EnjoLib::ExceptRuntimeError("Not handled type ");
}
