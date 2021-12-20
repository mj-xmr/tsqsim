#ifndef TICKPROVIDERXMR_H
#define TICKPROVIDERXMR_H

#include "TicksProviderBinary.h"
#include "typesStr.h"

class TicksProviderXMR : public TicksProviderBinary /// TODO: Consider composition instead of inheritance
{
    public:
        TicksProviderXMR();
        virtual ~TicksProviderXMR();

        //CorPtr<ITicks> GetTicks(const EnjoLib::Str & symbolName, const ConfigSym * confSym = nullptr) const override;
        //CorPtr<ITicks> GetPeriod(const EnjoLib::Str & symbolName, const EnjoLib::Str & periodName) const override;

        static VecStr ConvertStat(const VecStr & raw);
        static EnjoLib::Str ConvertStatSingle(const EnjoLib::Str & line);

    protected:
        VecStr Convert(const VecStr & raw) const override;

    private:
};

#endif // TICKPROVIDERXMR_H
