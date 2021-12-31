#ifndef TSFUNPRINTCUMUL_H
#define TSFUNPRINTCUMUL_H

#include "TSFunBase.h"

class TSFunPrintCumul : public TSFunBase
{
    public:
        TSFunPrintCumul(const TSInput & tsin);
        virtual ~TSFunPrintCumul();

        const char * GetName() const override { return "TSFunPrintCumul"; }

    protected:
        TSRes OnDataPointProt(int idx) const override;
        TSRes Reconstruct(int idx, const EnjoLib::VecD & input, const EnjoLib::VecD & lost) const override;

    private:
};

#endif // TSFUNPRINTCUMUL_H
