#ifndef PREDICTORDUMB_H
#define PREDICTORDUMB_H

#include "IPredictor.h"


class PredictorDumb : public IPredictor
{
    public:
        PredictorDumb();
        virtual ~PredictorDumb();

        EnjoLib::VecD Predict(const EnjoLib::VecD & data, size_t idx, int horizon) const override;

    protected:

    private:
};

#endif // PREDICTORDUMB_H
