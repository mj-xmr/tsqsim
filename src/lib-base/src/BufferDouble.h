#ifndef BUFFERDOUBLE_H
#define BUFFERDOUBLE_H

#include "typesVec.h"
#include <Util/VecD.hpp>
#include <Util/StrConst.hpp>

class BufferDouble
{
    public:
        BufferDouble(const EnjoLib::VecD & v, const char * name = nullptr);
        virtual ~BufferDouble();

        // From BufferTpl
        EnjoLib::FP operator[](unsigned i) const;
        EnjoLib::FP operator[](const State & st) const;
        EnjoLib::VecD GetBefore(unsigned iUntil, unsigned num) const;
        EnjoLib::VecD GetAfter(unsigned iFrom, unsigned num) const;
        //STDFWD::vector<T> GetMiddle(unsigned i, unsigned num) const;
        int Len() const;
        const EnjoLib::VecD & GetData() const;
        unsigned ConvertIndex(unsigned i) const;

    protected:
    private:
        const EnjoLib::VecD & m_data;
        EnjoLib::StrConst m_name;
};

#endif // BUFFERDOUBLE_H
