#ifndef PREDICTORDUMB_H
#define PREDICTORDUMB_H

#include "PredictorBase.h"


class PredictorDumb : public PredictorBase
{
    public:
        PredictorDumb(const IDataProvider & dat);
        virtual ~PredictorDumb();

        EnjoLib::VecD Predict(const EnjoLib::VecD & data) const override;
        unsigned GetLags() const override;

    protected:

    private:
};

#endif // PREDICTORDUMB_H
