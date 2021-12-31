#ifndef PREDICTOROUTPUTTYPE_H
#define PREDICTOROUTPUTTYPE_H


enum class PredictorOutputType
{
    SERIES,
    PREDICTION,
    BASELINE,
    RECONSTRUCTION,
    RECONSTRUCTION_PRED,
    RECONSTRUCTION_PRED_BASELINE
};

#endif // PREDICTOROUTPUTTYPE_H