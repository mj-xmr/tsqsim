#ifndef TSFUNFACTORY_H
#define TSFUNFACTORY_H

#include "ITSFun.h"
#include "TSFunType.h"
#include <Template/CorradePointer.h>

class TSInput;

class TSFunFactory
{
    public:
        TSFunFactory();
        virtual ~TSFunFactory();
        
        CorPtr<ITSFun> Create(const TSInput & tsin, const TSFunType & type) const;

    protected:

    private:
};

#endif // TSFUNFACTORY_H
