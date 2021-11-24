#ifndef TSFUNPRINTALL_H
#define TSFUNPRINTALL_H

#include "TSFunBase.h"

class TSFunPrintAll : public TSFunBase
{
    public:
        TSFunPrintAll(const TSInput & tsin);
        virtual ~TSFunPrintAll();
        
    protected:
        TSRes OnDataPointProt(int idx) const override;

    private:
};

#endif // TSFUNPRINTALL_H