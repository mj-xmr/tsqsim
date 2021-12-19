#ifndef PREDICTORBASELINE_H
#define PREDICTORBASELINE_H

#include "IPredictor.h"

/// Baseline predictor simply uses the previous value of the series
class PredictorBaseline : public IPredictor
{
    public:
        PredictorBaseline();
        virtual ~PredictorBaseline();
        
        EnjoLib::VecD Predict(const EnjoLib::VecD & data, size_t idx, int horizon) const override;

    protected:

    private:
};

#endif // PREDICTORBASELINE_H
