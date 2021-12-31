#ifndef IPREDICTOR_H
#define IPREDICTOR_H

#include <Util/VecD.hpp>

class ITSFun;

class IPredictor
{
    public:
        IPredictor();
        virtual ~IPredictor();

        //double PredictNext(const EnjoLib::VecD & orig, const EnjoLib::VecD & data, size_t idx) const;
        virtual EnjoLib::VecD Predict(const EnjoLib::VecD & data) const = 0;
        virtual unsigned GetLags() const = 0;
        //virtual EnjoLib::VecD Predict(const EnjoLib::VecD & orig, const EnjoLib::VecD & data, int horizon) const = 0;
        
        static const double ERROR;

    protected:

    private:
};

#endif // IPREDICTOR_H
