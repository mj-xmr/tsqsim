#ifndef PREDICTORSMAMA_H
#define PREDICTORSMAMA_H

#include "PredictorBase.h"


class PredictorSMAMA : public PredictorBase
{
    public:
        PredictorSMAMA(const IDataProvider & dat);
        virtual ~PredictorSMAMA();

        EnjoLib::VecD PredictVec(const EnjoLib::VecD & data) const override;
        double PredictNext(const BufferDouble & datExpanding) const override;
        unsigned GetLags() const override;

    protected:

    private:
        OptiVarF m_lagMine;
};

#endif // PREDICTORMA_H
