#ifndef PREDICTORFACTORY_H
#define PREDICTORFACTORY_H

#include "IPredictor.h"
#include <Template/CorradePointer.h>

enum class PredictorType;

class PredictorFactory
{
    public:
        PredictorFactory();
        virtual ~PredictorFactory();
        
        CorPtr<IPredictor> Create(const PredictorType & type) const;

    protected:

    private:
};

#endif // PREDICTORFACTORY_H
