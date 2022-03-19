#ifndef PREDICTORPYCUSTOM_H
#define PREDICTORPYCUSTOM_H

#include <PredictorBase.h>


class PredictorPyCustom : public PredictorBase
{
    public:
        PredictorPyCustom(const IDataProvider & dat);
        virtual ~PredictorPyCustom();
        
        EnjoLib::VecD PredictVec(const EnjoLib::VecD & data) const override;
        double PredictNext(const BufferDouble & datExpanding) const override;
        unsigned GetLags() const override;
        
        bool IsCustomScript() const override;

    protected:
        EnjoLib::VecD ExePython(const EnjoLib::VecD & data, bool movingWindow = true) const;

    private:
};

#endif // PREDICTORPYCUSTOM_H
