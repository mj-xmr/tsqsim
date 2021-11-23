#ifndef MAINTESTERMT_H
#define MAINTESTERMT_H

#include "typesVec.h"
#include "MainTester.h"

#include <Util/Tuple.hpp>

class ISymbol;

class MainTesterMT
{
    public:
        MainTesterMT();
        virtual ~MainTesterMT();

        using TupleIn = EnjoLib::Tuple<const MainTester *, EnjoLib::Str, VecStr>;
        static VecUPtr<ISymbol> GetSymbols(const stdfwd::vector<TupleIn> & inp, bool multiThreaded);

    protected:

    private:
};

#endif // MAINTESTERMT_H
