#ifndef TSFUNTXT_H
#define TSFUNTXT_H

#include "TSFunBase.h"
#include "ITSXform.h"
#include <Template/CorradePointer.h>

#include <STD/Vector.hpp>

class ITSXform;
class TSFunTxt : public TSFunBase
{
    public:
        TSFunTxt(const TSInput & tsin);
        virtual ~TSFunTxt();

        const char * GetName() const override { return "TSFunTxt"; }

    protected:
        TSRes OnDataPointProt(int idx) const override;
        TSRes Reconstruct(int idx, const EnjoLib::VecD & input, double prev) const override;

        unsigned LenProt() const override;

    private:

        std::vector<CorPtr<ITSXform>> m_xforms;
};

#endif // TSFUNTXT_H
