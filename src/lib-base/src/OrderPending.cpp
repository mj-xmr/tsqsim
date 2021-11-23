#include "OrderPending.h"
#include <Util/StackTrace.hpp>

OrderPending::OrderPending(const State & st, float level, float capUsed)
: st(st)
, level(level)
, capUsed(capUsed)
{
    if (capUsed > 1)
    {
        throw EnjoLib::ExceptRuntimeError(STRACE_THROW("capUsed > 1 "));
    }

}

OrderPending::~OrderPending()
{
    //dtor
}
