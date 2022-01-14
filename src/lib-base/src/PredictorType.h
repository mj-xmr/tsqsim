#ifndef PREDICTORTYPE_H
#define PREDICTORTYPE_H

enum class PredictorType
{
    PRED_BASELINE,
    PRED_BASELINE2,
    PRED_AR,
    PRED_SMAMA,
    PRED_ARMA,
#ifdef USE_R
    PRED_R_BASELINE,
    PRED_R_CUSTOM,
#endif
    PRED_DUMB,
    PRED_TEST,
    PRED_TRUE
};

#endif // PREDICTORTYPE_H
