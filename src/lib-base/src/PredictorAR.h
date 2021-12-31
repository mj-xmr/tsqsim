#ifndef PREDICTORAR_H
#define PREDICTORAR_H

#include "IPredictor.h"


class PredictorAR : public IPredictor
{
    public:
        PredictorAR();
        virtual ~PredictorAR();

        EnjoLib::VecD Predict(const EnjoLib::VecD & data) const override;
        unsigned GetLags() const override;

    protected:

    private:
};

#endif // PREDICTORAR_H
