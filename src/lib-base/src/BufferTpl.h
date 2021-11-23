#ifndef BUFFERTPL_H
#define BUFFERTPL_H
       
#include "TradeUtilThin.h"
#include "Candle.h"
#include "State.h"
#include "ConfigMan.h"
#include "ConfigTF2.h"

#include <Util/StackTrace.hpp>
#include <STD/Vector.hpp>

#include <Util/Except.hpp>

#include <3rdParty/stdfwd.hh> 

class State;

template <class T> 
class BufferTpl
{
    public:
        /*
        BufferTpl(const std::vector<T> & data, const char * name = "undefined");
        
        virtual ~BufferTpl();

        constexpr T operator[](unsigned i) const;
        constexpr T operator[](const State & st) const;
        std::vector<T> GetBefore(unsigned iUntil, unsigned num) const;
        std::vector<T> GetAfter(unsigned iFrom, unsigned num) const;
        //std::vector<T> GetMiddle(unsigned i, unsigned num) const;
        constexpr int Len() const;
        constexpr const std::vector<T> & GetData() const;
        constexpr unsigned ConvertIndex(unsigned i) const;
        */

    BufferTpl(const std::vector<T> & data, const char * name = "undefined")
    : m_data(data)
    , m_len(data.size())
    , m_name(name)
    {}

    T operator[](unsigned i) const
    {
        //const unsigned ii = ConvertIndex(i); return m_data[ii]; // Speed test

        
        if (i >= m_len)
        {
            const EnjoLib::CharManipulations cman;
            const EnjoLib::Str msg = "Index '" +  cman.ToStr(int(i)) + "' is above size of '" + cman.ToStr((int)m_len) + "', class " + m_name + '\n';
            //std::cout << oss.str() << std::endl;
            throw EnjoLib::ExceptRuntimeError(STRACE_THROW(msg));
        }
        
        //if (i < 0) // unsigned can't be < 0
        {
            //throw std::range_error(STRACE_THROW("Index negative " + m_name));
        }
            
        //return *(m_data.end() - 1 - i);
        const unsigned idx = ConvertIndex(i);
        return m_data[idx];
        
    }

    T operator[](const State & st) const
    {
        return this->operator[](st.i);
    }

    constexpr unsigned ConvertIndex(unsigned i) const
    {
        return TradeUtilThin::ConvertIndex(i, m_len);
    }

    std::vector<T> GetAfter(unsigned iFrom, unsigned num) const
    {
        typename std::vector<T>::const_iterator itFrom = m_data.end() - iFrom;
        typename std::vector<T>::const_iterator itTo   = itFrom + num;
        if (itTo >= m_data.end())
            itTo = m_data.end() - 1;

        std::vector<T> ret(itFrom, itTo);
        return ret;
    }

    std::vector<T> GetBefore(unsigned iUntil, unsigned num) const
    {
        typename std::vector<T>::const_iterator itUntil = m_data.end() - iUntil;
        typename std::vector<T>::const_iterator itFrom  = itUntil - num;
        if (itFrom < m_data.begin())
            itFrom = m_data.begin();

        std::vector<T> ret(itFrom, itUntil);
        return ret;
    }

    constexpr const std::vector<T> & GetData() const
    {
        return m_data;
    }

    ~BufferTpl()
    {
    }
    constexpr int Len() const
    {
        return m_len;
        //return m_data.size();
    }


    protected:
    private:

        const std::vector<T> & m_data;
        const size_t m_len;
        const char * m_name;
};

#endif // BUFFERTPL_H
