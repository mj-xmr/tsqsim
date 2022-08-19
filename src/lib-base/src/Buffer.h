#ifndef BUFFER_H
#define BUFFER_H

//#include "typesVec.h"
#include <Util/VecFwd.hpp>
#include <Util/StrConst.hpp>

class State;
//template<class T> class BufferTpl;
/// Easy read-only vector wrapper
class Buffer
{
    public:
        Buffer(const EnjoLib::VecF & v, const char * name = nullptr);
        virtual ~Buffer();

        EnjoLib::VecF Stretch(int size) const;

        // From BufferTpl
        float operator[](unsigned i) const;
        float operator[](const State & st) const;
        EnjoLib::VecF GetBefore(unsigned iUntil, unsigned num) const;
        EnjoLib::VecF GetAfter(unsigned iFrom, unsigned num) const;
        //std::vector<T> GetMiddle(unsigned i, unsigned num) const;
        int Len() const;
        const EnjoLib::VecF & GetData() const;
        unsigned ConvertIndex(unsigned i) const;

    protected:
    private:
        const EnjoLib::VecF & m_data;
        //EnjoLib::Str m_name;
        EnjoLib::StrConst m_name;
        const char * m_cname;
        //EnjoLib::SafePtr<BufferTpl<float>> m_buf;
        //std::shared_ptr<BufferTpl<float>> m_buf;
        //const BufferTpl<float> & m_buf;
};

#endif // BUFFER_H
