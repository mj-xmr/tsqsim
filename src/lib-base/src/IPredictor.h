#ifndef IPREDICTOR_H
#define IPREDICTOR_H

#include <Util/VecD.hpp>

class IPredictor
{
    public:
        IPredictor();
        virtual ~IPredictor();
        
        double PredictNext(const EnjoLib::VecD & data, size_t idx) const;
        EnjoLib::VecD PredictNextVec(const EnjoLib::VecD & data) const;
        virtual EnjoLib::VecD Predict(const EnjoLib::VecD & data, size_t idx, int horizon) const = 0;

    protected:

    private:
};

#endif // IPREDICTOR_H
