#include "BufferVecUpdateable.h"
#include "Util/StackTrace.hpp"
#include <Util/PimplDeleter.hpp>

#include <typeinfo>

struct BufferVecUpdateable::Impl
{
    EnjoLib::Array<EnjoLib::VecF> m_data;
};

BufferVecUpdateable::~BufferVecUpdateable(){}
BufferVecUpdateable::BufferVecUpdateable(const ITaAlgoVec * algo)
: m_algo(algo)
, m_name(typeid(*algo).name())
, m_impl(new Impl())
{
}
PIMPL_DELETER(BufferVecUpdateable)

void BufferVecUpdateable::Calculate(const DataOCHL & data, const IDataProvider & per)
{
    try
    {
        m_impl->m_data = m_algo->Calculate(data, per);
    }
    catch (std::exception & ex)
    {
        throw EnjoLib::ExceptRuntimeError(m_name +": Calculate Caught:\n" + ex.what());
    }
}

void BufferVecUpdateable::Update(const DataOCHL & data)
{
    // TODO
}

const EnjoLib::Array<EnjoLib::VecF> & BufferVecUpdateable::GetData() const
{
    return m_impl->m_data;
}
