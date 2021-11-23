#ifndef ITAALGO_H
#define ITAALGO_H

#include "typesVec.h"

namespace EnjoLib
{
    class VecF ;
    class VecD;
}

class DataOCHL;
class IDataProvider;
class ITaAlgo
{
    public:
        ITaAlgo();
        virtual ~ITaAlgo();

        virtual EnjoLib::VecF Calculate(const DataOCHL & data) const = 0;
        virtual EnjoLib::VecF Update(const DataOCHL & data) const;

        static void UpdateVecLeading0(EnjoLib::VecF * vec);
        static EnjoLib::VecD Vec2VecD(const EnjoLib::VecF & vec);
        static EnjoLib::VecF  VecD2Vec(const EnjoLib::VecD & vec);
        static EnjoLib::VecD VecDDiffs(const EnjoLib::VecD & vec);
        static EnjoLib::VecF  VecDiffs (const EnjoLib::VecF & vec);
        static EnjoLib::VecF  VecLogSigned (const EnjoLib::VecF & vec);

    protected:

    private:
};

#endif // ITAALGO_H
