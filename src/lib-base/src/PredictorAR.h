#ifndef PREDICTORAR_H
#define PREDICTORAR_H

#include "PredictorBase.h"


class PredictorAR : public PredictorBase
{
    public:
        PredictorAR(const IDataProvider & dat, const EnjoLib::Str & name = "AR");
        virtual ~PredictorAR();

        EnjoLib::VecD PredictVec(const EnjoLib::VecD & data) const override;
        double PredictNext(const BufferDouble & datExpanding) const override;
        unsigned GetLags() const override;

    protected:

    private:
};

#endif // PREDICTORAR_H
