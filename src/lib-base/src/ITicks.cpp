#include "ITicks.h"
#include "Ticks.h"

ITicks::~ITicks(){}

CorPtr<ITicks> ITicks::Create()
{
    return CorPtr<ITicks>(new Ticks);
}