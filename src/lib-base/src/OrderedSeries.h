#ifndef ORDEREDSERIES_H
#define ORDEREDSERIES_H

#include "PeriodClean.h"
#include <Util/VecD.hpp>

class OrderedSeries : public PeriodClean
{
    public:
        OrderedSeries(const ISymbol & sym);
        virtual ~OrderedSeries();
        
        void FeedVal(double val);
        void FeedVals(const EnjoLib::VecD & vals);

    protected:

    private:
};

#endif // ORDEREDSERIES_H
