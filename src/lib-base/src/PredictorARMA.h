#ifndef PREDICTORARMA_H
#define PREDICTORARMA_H

#include "PredictorBase.h"
#include "PredictorAR.h"

class PredictorARMA : public PredictorBase
{
    public:
        PredictorARMA(const IDataProvider & dat);
        virtual ~PredictorARMA();

        //EnjoLib::VecD PredictVec(const EnjoLib::VecD & data) const override;
        double PredictNext(const BufferDouble & datExpanding) const override;
        unsigned GetLags() const override;

    protected:

    private:
        PredictorAR m_predAR;
};

#endif // PREDICTORARMA_H
