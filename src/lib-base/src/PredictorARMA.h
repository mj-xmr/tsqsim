#ifndef PREDICTORARMA_H
#define PREDICTORARMA_H

#include "IPredictor.h"


class PredictorARMA : public IPredictor
{
    public:
        PredictorARMA();
        virtual ~PredictorARMA();

        EnjoLib::VecD Predict(const EnjoLib::VecD & data) const override;
        unsigned GetLags() const override;

    protected:

    private:
};

#endif // PREDICTORARMA_H
