#include "PredictorTypeStr.h"
#include "PredictorType.h"

#include <Util/Str.hpp>

PredictorTypeStr::PredictorTypeStr()
{
    for (int i = 0; i <= int(PredictorType::PRED_TRUE); ++i)
    {
        const PredictorType type = PredictorType(i);
        switch (type) // Generate compiler warnings
        {
            case PredictorType::PRED_BASELINE:      Add(i, "Baseline"); break;
            case PredictorType::PRED_BASELINE2:     Add(i, "Baseline 2"); break;
            case PredictorType::PRED_AR:            Add(i, "AR"); break;
            case PredictorType::PRED_SMAMA:         Add(i, "SmaMA"); break;
            case PredictorType::PRED_ARMA:          Add(i, "ARMA"); break;
            case PredictorType::PRED_R_BASELINE:    Add(i, "R-Baseline"); break;
            case PredictorType::PRED_R_CUSTOM:      Add(i, "R-Custom"); break;
            case PredictorType::PRED_PY_CUSTOM:     Add(i, "Py-Custom"); break;
            case PredictorType::PRED_TRUE:          Add(i, "True"); break;
            case PredictorType::PRED_TEST:          Add(i, "Test"); break;
            case PredictorType::PRED_DUMB:          Add(i, "Dumb"); break;
        }
    }
}

PredictorTypeStr::~PredictorTypeStr()
{
    //dtor
}
