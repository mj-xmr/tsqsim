#ifndef PREDICTORRBASELINE_H
#define PREDICTORRBASELINE_H

#include <PredictorBase.h>


class PredictorRBaseline : public PredictorBase
{
    public:
        PredictorRBaseline(const IDataProvider & dat);
        virtual ~PredictorRBaseline();

        EnjoLib::VecD PredictVec(const EnjoLib::VecD & data) const override;
        double PredictNext(const BufferDouble & datExpanding) const override;
        unsigned GetLags() const override;
        
        static const char * SCRIPT_NAME;
        //static const char * FUNCTION_NAME;
        
        bool IsCustomScript() const override;

    protected:

    private:
};

#endif // PREDICTORRBASELINE_H
