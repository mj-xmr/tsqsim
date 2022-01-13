#ifndef PredictorExperimental_H
#define PredictorExperimental_H

#include "PredictorBase.h"


class PredictorExperimental : public PredictorBase
{
    public:
        PredictorExperimental(const IDataProvider & dat);
        virtual ~PredictorExperimental();

        EnjoLib::VecD Predict(const EnjoLib::VecD & data) const override;
        unsigned GetLags() const override;

    protected:

    private:
};

#endif // PredictorExperimental_H
