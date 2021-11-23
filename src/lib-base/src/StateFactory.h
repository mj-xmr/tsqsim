#ifndef STATEFACTORY_H
#define STATEFACTORY_H

#include "State.h"
#include "Direction.h"
#include <Template/CorradePointerFwd.h>

class StateFactory
{
    public:
        StateFactory();
        virtual ~StateFactory();

        static Corrade::Containers::Pointer<State> Create(Direction bullish, int iii);

    protected:

    private:
};

#endif // STATEFACTORY_H
