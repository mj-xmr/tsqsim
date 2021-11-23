#include "BufferTpl.h"
/*
#include "TradeUtil.h"
#include "Candle.h"
#include "State.h"
#include "ConfigMan.h"
#include "ConfigTF2.h"

#include <Util/StackTrace.hpp>

#include <Util/Except.hpp>



template <class T>
BufferTpl<T>::BufferTpl(const std::vector<T> & data, const char * name)
: m_data(data)
, m_name(name ? name : "undefined")
{}

template <class T>
constexpr T BufferTpl<T>::operator[](unsigned i) const
{
    //const unsigned ii = ConvertIndex(i); return m_data[ii]; // Speed test

    
    if (i >= m_data.size())
    {
        EnjoLib::Osstream oss;
        oss << "Index '" << i << "' is above size of '" << m_data.size() << "', class " << m_name;
        std::cout << oss << std::endl;
        throw std::range_error(STRACE_THROW(oss));
    }
    
    //if (i < 0) // unsigned can't be < 0
    {
        //throw std::range_error(STRACE_THROW("Index negative " + m_name));
    }
        
    //return *(m_data.end() - 1 - i);
    const unsigned idx = ConvertIndex(i);
    return m_data[idx];
}

template <class T>
constexpr T BufferTpl<T>::operator[](const State & st) const
{
    return this->operator[](st.i);
}

template <class T>
constexpr unsigned BufferTpl<T>::ConvertIndex(unsigned i) const
{
    return TradeUtil::ConvertIndex(i, m_data.size());
    //return TradeUtil().ConvertIndex(i, m_data.size());
}

template <class T>
std::vector<T> BufferTpl<T>::GetAfter(unsigned iFrom, unsigned num) const
{
    typename std::vector<T>::const_iterator itFrom = m_data.end() - iFrom;
    typename std::vector<T>::const_iterator itTo   = itFrom + num;
    if (itTo >= m_data.end())
        itTo = m_data.end() - 1;

    std::vector<T> ret(itFrom, itTo);
    return ret;
}

template <class T>
std::vector<T> BufferTpl<T>::GetBefore(unsigned iUntil, unsigned num) const
{
    typename std::vector<T>::const_iterator itUntil = m_data.end() - iUntil;
    typename std::vector<T>::const_iterator itFrom  = itUntil - num;
    if (itFrom < m_data.begin())
        itFrom = m_data.begin();

    std::vector<T> ret(itFrom, itUntil);
    return ret;
}

template <class T>
constexpr const std::vector<T> & BufferTpl<T>::GetData() const
{
    return m_data;
}

template <class T>
BufferTpl<T>::~BufferTpl()
{
}

template <class T>
constexpr int BufferTpl<T>::Len() const
{
    return m_data.size();
}
*/
//template class BufferTpl<bool>;
//template class BufferTpl<float>;
//template class BufferTpl<double>;
//template class BufferTpl<Candle>;
