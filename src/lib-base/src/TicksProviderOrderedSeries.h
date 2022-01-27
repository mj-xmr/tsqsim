#ifndef TICKSPROVIDERORDEREDSERIES_H
#define TICKSPROVIDERORDEREDSERIES_H

#include <TicksProviderBinary.h>

class Candle;

class TicksProviderOrderedSeries : public TicksProviderBinary
{
    public:
        TicksProviderOrderedSeries();
        virtual ~TicksProviderOrderedSeries();

        static VecStr ConvertStat(const VecStr & raw);
        static EnjoLib::Str ConvertStatSingle(const Candle & line);

        VecStr Convert(const VecStr & raw) const override;

    protected:

    private:
};

#endif // TICKSPROVIDERORDEREDSERIES_H
