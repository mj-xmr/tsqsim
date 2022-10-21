#ifndef TICKPROVIDERXMR_H
#define TICKPROVIDERXMR_H

#include "TicksProviderBinary.h"
#include "typesStr.h"

class TicksProviderXMR : public TicksProviderBinary
{
    public:
        TicksProviderXMR();
        virtual ~TicksProviderXMR();

        VecStr ConvertStat(const VecStr & raw) const;
        //static EnjoLib::Str ConvertStatSingle(const EnjoLib::Str & line);

        EnjoLib::Str ConvertSingle(const EnjoLib::Str & line) const override;
        VecStr Convert(const VecStr & raw) const override;

    protected:


    private:
};

#endif // TICKPROVIDERXMR_H
