#ifndef BUFFERBOOL_H
#define BUFFERBOOL_H

#include "typesVec.h"
#include <Util/StrConst.hpp>

class BufferBool// : public BufferTpl<bool>
{
    public:
        BufferBool(const VecB & v, const char * name = nullptr);
        virtual ~BufferBool();

        // From BufferTpl
        bool operator[](unsigned i) const;
        bool operator[](const State & st) const;
        VecB GetBefore(unsigned iUntil, unsigned num) const;
        VecB GetAfter(unsigned iFrom, unsigned num) const;
        //STDFWD::vector<T> GetMiddle(unsigned i, unsigned num) const;
        int Len() const;
        const VecB & GetData() const;
        unsigned ConvertIndex(unsigned i) const;

    protected:
    private:
        const VecB & m_data;
        EnjoLib::StrConst m_name;
};

#endif // BUFFERBOOL_H
