#ifndef TSFUNPRINTALL_H
#define TSFUNPRINTALL_H

#include "TSFunBase.h"

class TSFunPrintAll : public TSFunBase
{
    public:
        TSFunPrintAll(const TSInput & tsin);
        virtual ~TSFunPrintAll();

        const char * GetName() const override { return "PrintAll"; }

    protected:
        TSRes OnDataPointProt(int idx) const override;
        TSRes Reconstruct(int idx, const EnjoLib::VecD & input, double prev) const override;

    private:
};

#endif // TSFUNPRINTALL_H
