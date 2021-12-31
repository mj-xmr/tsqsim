#ifndef PREDICTORSMAMA_H
#define PREDICTORSMAMA_H

#include "IPredictor.h"


class PredictorSMAMA : public IPredictor
{
    public:
        PredictorSMAMA();
        virtual ~PredictorSMAMA();

        EnjoLib::VecD Predict(const EnjoLib::VecD & data) const override;
        unsigned GetLags() const override;

    protected:

    private:
};

#endif // PREDICTORMA_H
