#include "CtplWrapStatic.h"
#include <Util/ThreadWrap.hpp>

CtplWrapStatic::~CtplWrapStatic(){}
CtplWrapStatic::CtplWrapStatic()
{
    //bool multiThreaded = gcfgMan.cfgTF->INDIVIDUAL_SYMBOL == 1 || gcfg.IS_QT;
    m_numCores = EnjoLib::ThreadWrap::GetConcurrency();
}

bool CtplWrapStatic::IsMT() const
{
    if (m_single)
    {
        return true;
    }
    return GetNumCores() > 1;
}

bool CtplWrapStatic::IsReversed() const
{
    return m_reversed;
}

short CtplWrapStatic::GetNumCores() const
{
    return m_numCores;
}

void CtplWrapStatic::SetMT(bool mtt)
{
    m_single = !mtt;
}

void CtplWrapStatic::SetSingle()
{
    m_single = true;
}

/// Will be faster, when the last elements take the longest processing time
void CtplWrapStatic::SetReversed()
{
    m_reversed = true;
}

void CtplWrapStatic::SetNumCores(short numCores)
{
    m_numCores = numCores;
}
