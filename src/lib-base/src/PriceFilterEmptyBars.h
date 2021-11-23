#ifndef PRICEFILTEREMPTYBARS_H
#define PRICEFILTEREMPTYBARS_H

#include "IPriceFilter.h"

class PriceFilterEmptyBars : public IPriceFilter
{
    public:
        PriceFilterEmptyBars();
        virtual ~PriceFilterEmptyBars();

        VecCan Filter(const PriceFilterConfig & cfg, const IDataProvider & per) const override;

    protected:

    private:
};

#endif // PRICEFILTEREMPTYBARS_H
