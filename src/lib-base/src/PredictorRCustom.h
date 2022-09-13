#ifndef PREDICTORRCUSTOM_H
#define PREDICTORRCUSTOM_H

#include <PredictorBase.h>


class PredictorRCustom : public PredictorBase
{
    public:
        PredictorRCustom(const IDataProvider & dat);
        virtual ~PredictorRCustom();

        EnjoLib::VecD PredictVec(const EnjoLib::VecD & data) const override;
        double PredictNext(const BufferDouble & datExpanding) const override;
        unsigned GetLags() const override;
        
        bool IsCustomScript() const override;

    protected:

    private:
};

#endif // PREDICTORRCUSTOM_H
