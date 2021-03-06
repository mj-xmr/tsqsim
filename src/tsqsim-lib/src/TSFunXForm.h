#ifndef TSFUNXFORM_H
#define TSFUNXFORM_H

#include "TSFunBase.h"

class TSFunXForm : public TSFunBase
{
    public:
        TSFunXForm(const TSInput & tsin);
        virtual ~TSFunXForm();

        const char * GetName() const override { return "TSFunXForm"; }

    protected:
        TSRes OnDataPointProt(int idx) const override;
        //TSRes Reconstruct(int idx, const EnjoLib::VecD & input, const EnjoLib::VecD & lost) const override;
        EnjoLib::VecD ReconstructVec(const EnjoLib::VecD & input, const EnjoLib::Matrix & lost) const override;

        unsigned LenProt() const override;

    private:
};

#endif // TSFUNXFORM_H
