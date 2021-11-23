#ifndef PRICEFILTERSPREADMUL_H
#define PRICEFILTERSPREADMUL_H

#include "IPriceFilter.h"


class PriceFilterSpreadMul : public IPriceFilter
{
    public:
        PriceFilterSpreadMul();
        virtual ~PriceFilterSpreadMul(){}

        VecCan Filter(const PriceFilterConfig & cfg, const IDataProvider & per) const override;

    protected:

    private:
};

#endif // PRICEFILTERSPREADMUL_H
