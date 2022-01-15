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
        
        static const char * SCRIPT_NAME;

    protected:

    private:
};

#endif // PREDICTORRCUSTOM_H
