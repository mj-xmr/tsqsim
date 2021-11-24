#ifndef TSFUNPRINTCUMUL_H
#define TSFUNPRINTCUMUL_H

#include "TSFunBase.h"

class TSFunPrintCumul : public TSFunBase
{
    public:
        TSFunPrintCumul(const TSInput & tsin);
        virtual ~TSFunPrintCumul();
        
    protected:
        TSRes OnDataPointProt(int idx) const override;

    private:
};

#endif // TSFUNPRINTCUMUL_H
