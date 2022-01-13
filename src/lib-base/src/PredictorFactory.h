#ifndef PREDICTORFACTORY_H
#define PREDICTORFACTORY_H

#include "IPredictor.h"
#include <Template/CorradePointer.h>

class IDataProvider;
enum class PredictorType;

class PredictorFactory
{
    public:
        PredictorFactory();
        virtual ~PredictorFactory();
        
        //CorPtr<IPredictor> Create(const PredictorType & type) const;
        //CorPtr<IPredictor> CreateOpti(const IDataProvider & dat, const PredictorType & type) const;
        CorPtr<IPredictor> Create(const IDataProvider & dat, const PredictorType & type) const;

    protected:

    private:
};

#endif // PREDICTORFACTORY_H
