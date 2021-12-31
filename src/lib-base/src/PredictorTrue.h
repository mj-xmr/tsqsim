#ifndef PREDICTORTRUE_H
#define PREDICTORTRUE_H

#include "IPredictor.h"

/// True predictor simply uses the real value of the series, exactly as it should be predicted
class PredictorTrue : public IPredictor
{
    public:
        PredictorTrue();
        virtual ~PredictorTrue();

        EnjoLib::VecD Predict(const EnjoLib::VecD & data) const override;
        unsigned GetLags() const override;

    protected:

    private:
};

#endif // PREDICTORTRUE_H
