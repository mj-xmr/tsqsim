#ifndef TSFUNXFORM_H
#define TSFUNXFORM_H

#include "TSFunBase.h"

class TSFunXForm : public TSFunBase
{
    public:
        TSFunXForm(const TSInput & tsin);
        virtual ~TSFunXForm();

    protected:
        TSRes OnDataPointProt(int idx) const override;
        TSRes Reconstruct(int idx, const EnjoLib::VecD & input, double prev) const override;

        unsigned LenProt() const override;

    private:
};

#endif // TSFUNXFORM_H
