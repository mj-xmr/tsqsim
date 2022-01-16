#include "BufferDouble.h"
#include "BufferTpl.h"

BufferDouble::BufferDouble(const EnjoLib::VecD & v, const char * name)
: m_data(v)
, m_name(name ? name : "undefined")
{
    //ctor
}

BufferDouble::~BufferDouble()
{
    //dtor
}

double BufferDouble::operator[](unsigned i) const
{
    //return (*m_buf)[i];
    return BufferTpl<double>(m_data.Data(), m_name.c_str())[i];
}

unsigned BufferDouble::ConvertIndex(unsigned i) const
{
    //return (*m_buf).ConvertIndex(i);
    return BufferTpl<double>(m_data.Data(), m_name.c_str()).ConvertIndex(i);
}

double BufferDouble::operator[](const State & st) const
{
    return BufferTpl<double>(m_data.Data(), m_name.c_str())[st];
}

EnjoLib::VecD BufferDouble::GetAfter(unsigned iFrom, unsigned num) const
{
    return BufferTpl<double>(m_data.Data(), m_name.c_str()).GetAfter(iFrom, num);
}

EnjoLib::VecD BufferDouble::GetBefore(unsigned iUntil, unsigned num) const
{
    return BufferTpl<double>(m_data.Data(), m_name.c_str()).GetBefore(iUntil, num);
}

const EnjoLib::VecD & BufferDouble::GetData() const
{
    return m_data;
}

int BufferDouble::Len() const
{
    return BufferTpl<double>(m_data.Data(), m_name.c_str()).Len();
}
