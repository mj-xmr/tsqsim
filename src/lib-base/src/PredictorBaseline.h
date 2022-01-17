#ifndef PREDICTORBASELINE_H
#define PREDICTORBASELINE_H

#include "PredictorBase.h"

/// Baseline predictor simply uses the previous value of the series
class PredictorBaseline : public PredictorBase
{
    public:
        PredictorBaseline(const IDataProvider & dat);
        virtual ~PredictorBaseline();

        //EnjoLib::VecD PredictVec(const EnjoLib::VecD & data) const override;
        double PredictNext(const BufferDouble & datExpanding) const override;
        unsigned GetLags() const override;

    protected:

    private:
};

class PredictorBaseline2 : public PredictorBaseline
{
    public:
        PredictorBaseline2(const IDataProvider & dat);
        virtual ~PredictorBaseline2();
        unsigned GetLags() const override;

    protected:

    private:
};

#endif // PREDICTORBASELINE_H
