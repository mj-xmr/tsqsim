#ifndef PREDICTORDUMB_H
#define PREDICTORDUMB_H

#include "PredictorBase.h"


class PredictorDumb : public PredictorBase
{
    public:
        PredictorDumb(const IDataProvider & dat);
        virtual ~PredictorDumb();

        EnjoLib::VecD PredictVec(const EnjoLib::VecD & data) const override;
        double PredictNext(const BufferDouble & datExpanding) const override;
        unsigned GetLags() const override;

    protected:

    private:
};

#endif // PREDICTORDUMB_H
