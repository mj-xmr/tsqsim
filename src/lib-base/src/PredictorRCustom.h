#ifndef PREDICTORRCUSTOM_H
#define PREDICTORRCUSTOM_H

#include <PredictorBase.h>


class PredictorRCustom : public PredictorBase
{
    public:
        PredictorRCustom(const IDataProvider & dat);
        virtual ~PredictorRCustom();

        EnjoLib::VecD Predict(const EnjoLib::VecD & data) const override;
        unsigned GetLags() const override;

    protected:

    private:
};

#endif // PREDICTORRCUSTOM_H
