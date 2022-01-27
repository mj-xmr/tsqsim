#ifndef TICKPROVIDERFACTORY_H
#define TICKPROVIDERFACTORY_H

#include <Template/CorradePointerFwd.h>
#include "ITicksProvider.h"

enum class TickProviderType
{
    ARCHIVER,
    SMALL,
    XMR,
    GENERATED,
    XMR_FAKE,
    ADAPTIVE_FAKE,
    ADAPTIVE
};

class TickProviderFactory
{
    public:
        TickProviderFactory();
        virtual ~TickProviderFactory();

        Corrade::Containers::Pointer<ITicksProvider> Create(TickProviderType type) const;

    protected:
    private:
};

#endif // TICKPROVIDERFACTORY_H
