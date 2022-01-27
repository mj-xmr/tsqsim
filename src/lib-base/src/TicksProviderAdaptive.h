#ifndef TICKSPROVIDERADAPTIVE_H
#define TICKSPROVIDERADAPTIVE_H

#include <TicksProviderBinary.h>

enum class TicksFormat;

class TicksProviderAdaptive : public TicksProviderBinary
{
    public:
        TicksProviderAdaptive();
        virtual ~TicksProviderAdaptive();

    protected:
        CorPtr<TicksProviderBinary> Create(const TicksFormat & format) const;
        VecStr Convert(const VecStr & raw) const override;

    private:
};

#endif // TICKSPROVIDERADAPTIVE_H
