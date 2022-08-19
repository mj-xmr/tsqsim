#ifndef IESTIMATOR_H
#define IESTIMATOR_H

#include <Util/VecFwd.hpp>

class IEstimator
{
    public:
        IEstimator();
        virtual ~IEstimator(); 

        virtual void AddSampleTarget(const EnjoLib::VecD & samples, double target) = 0;
        
        virtual void Train() = 0;
        virtual double Predict(const EnjoLib::VecD & x) const = 0;

    protected:
        virtual void Clear() = 0;
    private:

};

#endif // IESTIMATOR_H
