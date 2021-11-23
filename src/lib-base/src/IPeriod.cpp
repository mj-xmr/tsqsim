#include "IPeriod.h"
#include "Buffer.h"

IPeriod::IPeriod(const ISymbol & sym)
: m_sym(sym)
{
    //ctor
}

IPeriod::~IPeriod()
{
    //dtor
}

const EnjoLib::VecF & IPeriod::GetBufData(const BufferType & type) const
{
    return GetBuf(type).GetData();
}
