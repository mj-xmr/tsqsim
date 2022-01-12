#include "OptiVarVec.h"

#include <Util/PimplCopier.hpp>
#include <Util/PimplDeleter.hpp>
#include <STD/VectorCpp.hpp>

#include <initializer_list>

using OptiVarVecInternal = std::vector<OptiVarF *>;

struct OptiVarVec::Impl
{
    Impl(){}
    Impl(const std::initializer_list<OptiVarF *> & invec) : vec(invec) {}
    OptiVarVecInternal vec;
};

PIMPL_COPIER(OptiVarVec)
PIMPL_DELETER(OptiVarVec)

OptiVarVec::~OptiVarVec(){}
OptiVarVec::OptiVarVec()
: m_impl(new Impl())
{
    
}

OptiVarVec::OptiVarVec(const std::initializer_list<OptiVarF *> & invec)
: m_impl(new Impl(invec))
{    
}

void OptiVarVec::Add(OptiVarF * var)
{
    GetImplRW().vec.push_back(var);
}

std::vector<OptiVarF *> & OptiVarVec::VecRW()
{
    return GetImplRW().vec;
}

EnjoLib::Array<OptiVarF *> OptiVarVec::Vec() const
{
    return GetImpl().vec;
}

void OptiVarVec::Reinit(EnjoLib::Array<OptiVarF *> & vopti)
{
    VecRW().clear();
    for (OptiVarF * v : vopti)
        VecRW().push_back(v);
}

int OptiVarVec::size() const
{
    return GetImpl().vec.size();
}

/*
OptiVarVec::iterator OptiVarVec::begin()          {return iterator(&GetImpl()->dat[0]);}
OptiVarVec::iterator OptiVarVec::end()            {return iterator(&GetImpl()->dat[size()]);}
OptiVarVec::const_iterator OptiVarVec::begin() const    {return const_iterator(&m_impl->dat[0]);}
OptiVarVec::const_iterator OptiVarVec::end()   const    {return const_iterator(&m_impl->dat[size()]);}
OptiVarVec::const_iterator OptiVarVec::cbegin() const   {return begin();}
OptiVarVec::const_iterator OptiVarVec::cend()   const   {return end();}
*/
