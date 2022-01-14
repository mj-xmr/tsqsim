#ifndef PREDICTORRBASELINE_H
#define PREDICTORRBASELINE_H

#include <PredictorBase.h>


class PredictorRBaseline : public PredictorBase
{
    public:
        PredictorRBaseline(const IDataProvider & dat);
        virtual ~PredictorRBaseline();

        EnjoLib::VecD Predict(const EnjoLib::VecD & data) const override;
        unsigned GetLags() const override;

    protected:

    private:
};

#endif // PREDICTORRBASELINE_H
