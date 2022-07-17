#include "PredictorBase.h"
#include "OptiVarVec.h"
#include "IDataProvider.h"
#include <Template/Array.hpp>

#include <STD/VectorCpp.hpp>

PredictorBase::PredictorBase(const IDataProvider & dat, const EnjoLib::Str & lagName)
: m_dat(dat)
, m_optiFloats(new OptiVarVec())
, m_lagMain(dat, "LAG_" + lagName, true, 10, 1, 150, 1)
{
    AddOptiVar(m_lagMain);
}

PredictorBase::~PredictorBase()
{
    //dtor
}

int PredictorBase::Len() const
{
    return m_dat.Len() - GetLags();
}

const IDataProvider & PredictorBase::GetDat() const
{
    return m_dat;
}

OptiVarVec & PredictorBase::GetOptiFloatRW()
{
    return *m_optiFloats;
    //return m_optiFloats;
}

OptiVarVec PredictorBase::GetOptiFloat()
{
    return *m_optiFloats;
    //return m_optiFloats;
}


void PredictorBase::AddOptiVars(IOptimizable & iopt)
{
    for (auto v : iopt.GetOptiFloat().Vec())
        AddOptiVar(*v);
}

void PredictorBase::AddOptiVar(OptiVarF & var)
{
    GetOptiFloatRW().VecRW().push_back(&var);
    //m_optiFloats.push_back(&var);
}

const OptiVarF & PredictorBase::GetLag1() const
{
    return m_lagMain;
}
