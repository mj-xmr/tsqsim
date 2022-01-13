#ifndef OPTIMIZERFACTORYABSTRACT_H
#define OPTIMIZERFACTORYABSTRACT_H

#include "IOptimizer.h"
#include <Template/CorradePointer.h>

class StartEnd;

class OptimizerFactoryAbstract
{
    public:
        OptimizerFactoryAbstract();
        virtual ~OptimizerFactoryAbstract();
        
        virtual CorPtr<IOptimizer> Create(const StartEnd & startEndFrame) const = 0;

    protected:

    private:
};

#endif // OPTIMIZERFACTORYABSTRACT_H
