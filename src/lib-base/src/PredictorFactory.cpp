#include "PredictorFactory.h"

#include "PredictorType.h"
#include "PredictorTrue.h"
#include "PredictorBaseline.h"
#include "PredictorDumb.h"
#include "PredictorRegression.h"


#include <Util/Except.hpp>

PredictorFactory::PredictorFactory(){}
PredictorFactory::~PredictorFactory(){}

CorPtr<IPredictor> PredictorFactory::Create(const PredictorType & type) const
{
    switch (type)
    {
        case PredictorType::PRED_REGRESSION:    return CorPtr<IPredictor>(new PredictorRegression());
        case PredictorType::PRED_BASELINE:      return CorPtr<IPredictor>(new PredictorBaseline());
        case PredictorType::PRED_DUMB:          return CorPtr<IPredictor>(new PredictorDumb());
        case PredictorType::PRED_TRUE:          return CorPtr<IPredictor>(new PredictorTrue());
    }
    throw EnjoLib::ExceptNotImpl("PredictorFactory(): Not implemented type");
}
