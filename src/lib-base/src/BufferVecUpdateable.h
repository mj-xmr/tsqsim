#ifndef BUFFERVECUPDATEABLE_H
#define BUFFERVECUPDATEABLE_H

//#include "Buffer.h"
#include "ITaAlgoVec.h"
#include <Template/SafePtr.hpp>
#include <Util/Str.hpp>
#include <Util/Pimpl.hpp>

class BufferVecUpdateable
{
    public:
        BufferVecUpdateable(const ITaAlgoVec * algo);
        virtual ~BufferVecUpdateable();

        void Calculate(const DataOCHL & data, const IDataProvider & per);
        void Update(const DataOCHL & data);
        const EnjoLib::Array<EnjoLib::VecF> & GetData() const;

    protected:

    private:
        EnjoLib::SafePtr<const ITaAlgoVec> m_algo;
        EnjoLib::Str m_name;
        
        PIMPL
};

#endif // BUFFERVECUPDATEABLE_H
