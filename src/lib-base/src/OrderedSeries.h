#ifndef ORDEREDSERIES_H
#define ORDEREDSERIES_H

#include "PeriodClean.h"
#include <Util/VecFwd.hpp>

class OrderedSeries : public PeriodClean
{
    public:
        OrderedSeries(const ISymbol & sym);
        virtual ~OrderedSeries();
        
        void FeedVal(double open, double close, double high, double low);
        void FeedVal(double val);
        void FeedVals(const EnjoLib::VecD & vals);

    protected:

    private:
};

#endif // ORDEREDSERIES_H
