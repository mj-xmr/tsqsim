#ifndef PERIODFACTORYABSTRACT_H
#define PERIODFACTORYABSTRACT_H

#include <Template/CorradePointerFwd.h>

class IPeriod;
class ISymbol;
class PeriodFactoryAbstract
{
    public:
        PeriodFactoryAbstract();
        virtual ~PeriodFactoryAbstract();

        virtual Corrade::Containers::Pointer<IPeriod> Create(int minutes, const ISymbol & sym) const = 0;
        //EnjoLib::UniquePtr<IPeriod> Copy(const IPeriod & sym) const;
        Corrade::Containers::Pointer<IPeriod> Copy(const IPeriod & sym) const;

    protected:

    private:
};

#endif // PERIODFACTORYABSTRACT_H
