#include "BufferBool.h"
#include "BufferTpl.h"

BufferBool::BufferBool(const VecB & v, const char * name)
: m_data(v)
, m_name(name ? name : "undefined")
{
    //ctor
}

BufferBool::~BufferBool()
{
    //dtor
}

bool BufferBool::operator[](unsigned i) const
{
    //return (*m_buf)[i];
    return BufferTpl<bool>(m_data, m_name.c_str())[i];
}

unsigned BufferBool::ConvertIndex(unsigned i) const
{
    //return (*m_buf).ConvertIndex(i);
    return BufferTpl<bool>(m_data, m_name.c_str()).ConvertIndex(i);
}

bool BufferBool::operator[](const State & st) const
{
    return BufferTpl<bool>(m_data, m_name.c_str())[st];
}

VecB BufferBool::GetAfter(unsigned iFrom, unsigned num) const
{
    return BufferTpl<bool>(m_data, m_name.c_str()).GetAfter(iFrom, num);
}

VecB BufferBool::GetBefore(unsigned iUntil, unsigned num) const
{
    return BufferTpl<bool>(m_data, m_name.c_str()).GetBefore(iUntil, num);
}

const VecB & BufferBool::GetData() const
{
    return BufferTpl<bool>(m_data, m_name.c_str()).GetData();
}

int BufferBool::Len() const
{
    return BufferTpl<bool>(m_data, m_name.c_str()).Len();
}
