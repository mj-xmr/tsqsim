#ifndef PredictorExperimental_H
#define PredictorExperimental_H

#include "IPredictor.h"


class PredictorExperimental : public IPredictor
{
    public:
        PredictorExperimental();
        virtual ~PredictorExperimental();

        EnjoLib::VecD Predict(const EnjoLib::VecD & data) const override;
        unsigned GetLags() const override;

    protected:

    private:
};

#endif // PredictorExperimental_H
