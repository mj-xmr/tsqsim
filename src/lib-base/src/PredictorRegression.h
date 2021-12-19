#ifndef PREDICTORREGRESSION_H
#define PREDICTORREGRESSION_H

#include "IPredictor.h"


class PredictorRegression : public IPredictor
{
    public:
        PredictorRegression();
        virtual ~PredictorRegression();

        EnjoLib::VecD Predict(const EnjoLib::VecD & data, size_t idx, int horizon) const override;

    protected:
        EnjoLib::VecD Erratic(const EnjoLib::VecD & data, size_t idx, int horizon) const;

    private:
};

#endif // PREDICTORREGRESSION_H
