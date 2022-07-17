#ifndef TICKPROVIDERXMR_H
#define TICKPROVIDERXMR_H

#include "TicksProviderBinary.h"
#include "typesStr.h"

class TicksProviderXMR : public TicksProviderBinary
{
    public:
        TicksProviderXMR();
        virtual ~TicksProviderXMR();

        static VecStr ConvertStat(const VecStr & raw);
        static EnjoLib::Str ConvertStatSingle(const EnjoLib::Str & line);

        VecStr Convert(const VecStr & raw) const override;

    protected:


    private:
};

#endif // TICKPROVIDERXMR_H
