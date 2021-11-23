#include "StateFactory.h"
#include <Template/CorradePointer.h>

StateFactory::StateFactory()
{
    //ctor
}

StateFactory::~StateFactory()
{
    //dtor
}

Corrade::Containers::Pointer<State> StateFactory::Create(Direction bullish, int iii)
{
    return Corrade::Containers::Pointer<State>(new State(bullish, iii));
}
