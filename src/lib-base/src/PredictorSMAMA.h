#ifndef PREDICTORSMAMA_H
#define PREDICTORSMAMA_H

#include "PredictorBase.h"


class PredictorSMAMA : public PredictorBase
{
    public:
        PredictorSMAMA(const IDataProvider & dat);
        virtual ~PredictorSMAMA();

        EnjoLib::VecD Predict(const EnjoLib::VecD & data) const override;
        unsigned GetLags() const override;

    protected:

    private:
        OptiVarF m_lagMine;
};

#endif // PREDICTORMA_H
