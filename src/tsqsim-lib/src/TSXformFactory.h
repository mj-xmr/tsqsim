#ifndef TSXFORMFACTORY_H
#define TSXFORMFACTORY_H

#include "ITSXform.h"
#include <Util/Str.hpp>
#include <Template/CorradePointer.h>

class TSXformFactory
{
    public:
        TSXformFactory();
        virtual ~TSXformFactory();
        
        CorPtr<ITSXform> Create(const EnjoLib::Str & name) const;

    protected:

    private:
};

#endif // TSXFORMFACTORY_H
