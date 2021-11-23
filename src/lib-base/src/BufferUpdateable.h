#ifndef BUFFERUPDATEABLE_H
#define BUFFERUPDATEABLE_H

#include "Buffer.h"
#include "ITaAlgo.h"
#include <Template/SafePtr.hpp>
#include <Util/VecF.hpp>
#include <3rdParty/stdfwd.hh>


class BufferUpdateable
{
    public:
        BufferUpdateable(const ITaAlgo * algo);
        virtual ~BufferUpdateable();

        void Calculate(const DataOCHL & data);
        void Update(const DataOCHL & data);
        Buffer GetBuf() const;
        const EnjoLib::VecF & GetData() const;

    protected:

    private:
        EnjoLib::VecF m_data;

        EnjoLib::SafePtr<const ITaAlgo> m_algo;
        EnjoLib::Str m_name;
};

#endif // BUFFERUPDATEABLE_H
