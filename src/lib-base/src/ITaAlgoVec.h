#ifndef ITAALGOVEC_H
#define ITAALGOVEC_H

#include "typesVec.h"
#include <Template/Array.hpp>

class DataOCHL;
class IDataProvider;

class ITaAlgoVec
{
    public:
        ITaAlgoVec();
        virtual ~ITaAlgoVec();

        virtual EnjoLib::Array<EnjoLib::VecF> Calculate(const DataOCHL & data, const IDataProvider & per) const = 0;
        
        static EnjoLib::Array<EnjoLib::VecF> VecDiffsBetweenEach(const EnjoLib::Array<EnjoLib::VecF> & vec);
        static EnjoLib::Array<EnjoLib::VecF> VecDiffsSpeed(const EnjoLib::Array<EnjoLib::VecF> & vec);
        static EnjoLib::Array<EnjoLib::VecF> VecLogs(const EnjoLib::Array<EnjoLib::VecF> & vec);

    protected:

    private:
};

#endif // ITAALGOVEC_H
