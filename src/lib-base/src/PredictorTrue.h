#ifndef PREDICTORTRUE_H
#define PREDICTORTRUE_H

#include "PredictorBase.h"

/// True predictor simply uses the real value of the series, exactly as it should be predicted
class PredictorTrue : public PredictorBase
{
    public:
        PredictorTrue(const IDataProvider & dat);
        virtual ~PredictorTrue();

        EnjoLib::VecD PredictVec(const EnjoLib::VecD & data) const override;
        double PredictNext(const BufferDouble & datExpanding) const override;
        unsigned GetLags() const override;

    protected:

    private:
};

#endif // PREDICTORTRUE_H
