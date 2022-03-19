#include "PredictorFactory.h"

#include "PredictorType.h"
#include "PredictorTrue.h"
#include "PredictorExperimental.h"
#include "PredictorBaseline.h"
#include "PredictorDumb.h"
#include "PredictorAR.h"
#include "PredictorSMAMA.h"
#include "PredictorARMA.h"
#include "PredictorRBaseline.h"
#include "PredictorRCustom.h"
#include "PredictorPyCustom.h"

#include <Util/Except.hpp>

PredictorFactory::PredictorFactory(){}
PredictorFactory::~PredictorFactory(){}

/*
CorPtr<IPredictor> PredictorFactory::Create(const PredictorType & type) const
{
    switch (type)
    {
        case PredictorType::PRED_AR:            return CorPtr<IPredictor>(new PredictorAR());
        case PredictorType::PRED_SMAMA:         return CorPtr<IPredictor>(new PredictorSMAMA());
        case PredictorType::PRED_ARMA:          return CorPtr<IPredictor>(new PredictorARMA());
        case PredictorType::PRED_BASELINE:      return CorPtr<IPredictor>(new PredictorBaseline());
        case PredictorType::PRED_BASELINE2:     return CorPtr<IPredictor>(new PredictorBaseline2());
        case PredictorType::PRED_TEST:          return CorPtr<IPredictor>(new PredictorExperimental());
        case PredictorType::PRED_DUMB:          return CorPtr<IPredictor>(new PredictorDumb());
        case PredictorType::PRED_TRUE:          return CorPtr<IPredictor>(new PredictorTrue());
    }
    throw EnjoLib::ExceptNotImpl("PredictorFactory(): Not implemented type");
}
*/

CorPtr<IPredictor> PredictorFactory::Create(const IDataProvider & dat, const PredictorType & type) const
{
    switch (type)
    {
        case PredictorType::PRED_AR:            return CorPtr<IPredictor>(new PredictorAR(dat));
        case PredictorType::PRED_SMAMA:         return CorPtr<IPredictor>(new PredictorSMAMA(dat));
        case PredictorType::PRED_ARMA:          return CorPtr<IPredictor>(new PredictorARMA(dat));
        case PredictorType::PRED_BASELINE:      return CorPtr<IPredictor>(new PredictorBaseline(dat));
        case PredictorType::PRED_BASELINE2:     return CorPtr<IPredictor>(new PredictorBaseline2(dat));
        case PredictorType::PRED_R_BASELINE:    return CorPtr<IPredictor>(new PredictorRBaseline(dat));
        case PredictorType::PRED_R_CUSTOM:      return CorPtr<IPredictor>(new PredictorRCustom(dat));
        case PredictorType::PRED_PY_CUSTOM:     return CorPtr<IPredictor>(new PredictorPyCustom(dat));
        case PredictorType::PRED_TEST:          return CorPtr<IPredictor>(new PredictorExperimental(dat));
        case PredictorType::PRED_DUMB:          return CorPtr<IPredictor>(new PredictorDumb(dat));
        case PredictorType::PRED_TRUE:          return CorPtr<IPredictor>(new PredictorTrue(dat));
    }
    throw EnjoLib::ExceptNotImpl("PredictorFactory(): Not implemented type");
}
