#include "Buffer.h"
#include "BufferTpl.h"

#include <Template/CorradePointer.h>
#include <Math/SplineLin.hpp>
#include <Util/VecD.hpp>
#include <Util/Except.hpp>

using namespace EnjoLib;

Buffer::Buffer(const EnjoLib::VecF & v, const char * name)
//: m_buf(std::shared_ptr<BufferTpl<float>>(new BufferTpl<float>(v, name)))
//: m_buf(Corrade::Containers::Pointer<BufferTpl<float>>(new BufferTpl<float>(v, name)))
: m_data(v)
//, m_name(name ? name : "undefined") /// TODO: Transfer "undefined" to error handling ONLY
, m_name(name)
, m_cname(m_name.c_str())
{
}

Buffer::~Buffer(){}

EnjoLib::VecF Buffer::Stretch(int size) const
{
    VecD thisDouble;
    for(float val : GetData())
        thisDouble.push_back(val);
    SplineLin splineLin(thisDouble);
    const VecD & retDouble = splineLin.Scale(size);
    EnjoLib::VecF ret;
    for (double val : retDouble)
        ret.push_back(val);
    return ret;
}

float Buffer::operator[](unsigned i) const
{
    //return (*m_buf)[i];
    return BufferTpl<float>(m_data.Data(), m_cname)[i];
    //return this->operator[](i);
}

unsigned Buffer::ConvertIndex(unsigned i) const
{
    //return (*m_buf).ConvertIndex(i);
    return TradeUtilThin::ConvertIndex(i, m_data.size());
    //return BufferTpl<float>(m_data.Data(), m_name.c_str()).ConvertIndex(i);
}

float Buffer::operator[](const State & st) const
{
    return BufferTpl<float>(m_data.Data(), m_cname)[st];
}

EnjoLib::VecF Buffer::GetAfter(unsigned iFrom, unsigned num) const
{
    return BufferTpl<float>(m_data.Data(), m_name.c_str()).GetAfter(iFrom, num);
}

EnjoLib::VecF Buffer::GetBefore(unsigned iUntil, unsigned num) const
{
    return BufferTpl<float>(m_data.Data(), m_name.c_str()).GetBefore(iUntil, num);
}

//EnjoLib::VecF Buffer::GetData() const
const EnjoLib::VecF & Buffer::GetData() const
{
    return m_data;
    //return BufferTpl<float>(m_data.Data(), m_name.c_str()).GetData();
}

int Buffer::Len() const
{
    return BufferTpl<float>(m_data.Data(), m_name.c_str()).Len();
}
