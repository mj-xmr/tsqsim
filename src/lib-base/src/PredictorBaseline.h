#ifndef PREDICTORBASELINE_H
#define PREDICTORBASELINE_H

#include "IPredictor.h"

/// Baseline predictor simply uses the previous value of the series
class PredictorBaseline : public IPredictor
{
    public:
        PredictorBaseline();
        virtual ~PredictorBaseline();

        EnjoLib::VecD Predict(const EnjoLib::VecD & data) const override;
        unsigned GetLags() const override;

    protected:

    private:
};

class PredictorBaseline2 : public PredictorBaseline
{
    public:
        PredictorBaseline2();
        virtual ~PredictorBaseline2();
        unsigned GetLags() const override;

    protected:

    private:
};

#endif // PREDICTORBASELINE_H