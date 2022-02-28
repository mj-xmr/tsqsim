#include "SimulatorTSFactoryImpl.h"
#include "SimulatorTS.h"

SimulatorTSFactoryImpl::SimulatorTSFactoryImpl(const TSInput & tsin, const ITSFun & fun)
: m_tsin(tsin)
, m_fun(fun)
{
    //ctor
}

SimulatorTSFactoryImpl::~SimulatorTSFactoryImpl()
{
    //dtor
}

CorPtr<ISimulator> SimulatorTSFactoryImpl::Create(const EnjoLib::Str & params) const
{
    return  CorPtr<ISimulator> (new SimulatorTS(m_tsin, m_fun));
}
