#include "BufferUpdateable.h"
#include "Util/StackTrace.hpp"
#include <STD/VectorCpp.hpp>
#include <typeinfo>


BufferUpdateable::~BufferUpdateable(){}
BufferUpdateable::BufferUpdateable(const ITaAlgo * algo)
: m_algo(algo)
, m_name(typeid(*algo).name())
{
}

void BufferUpdateable::Calculate(const DataOCHL & data)
{
    try
    {
        m_data = m_algo->Calculate(data);
    }
    catch (std::exception & ex)
    {
        throw EnjoLib::ExceptRuntimeError(m_name +": Calculate Caught:\n" + ex.what());
    }
}

void BufferUpdateable::Update(const DataOCHL & data)
{
    const EnjoLib::VecF & dataUpdated = m_algo->Update(data);
    if (dataUpdated.empty())
        return;
    const float val = dataUpdated.at(dataUpdated.size() - 1);
    if (!m_data.empty())
    {
        m_data.DataRW().erase(m_data.Data().begin());
    }
    m_data.push_back(val);
}

Buffer BufferUpdateable::GetBuf() const
{
    return Buffer(m_data, m_name.c_str());
}

const EnjoLib::VecF & BufferUpdateable::GetData() const
{
    return m_data;
}
