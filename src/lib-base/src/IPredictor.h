#ifndef IPREDICTOR_H
#define IPREDICTOR_H

#include "IOptimizable.h"
#include "IHasLen.h"
#include <Util/VecD.hpp>

class BufferDouble;

/**
Predicts the next data points in a series.
*/
class IPredictor : public IOptimizable, public IHasLen
{
    public:
        IPredictor();
        virtual ~IPredictor();

        /**
        Predict the whole series. Index 0 = the earliest bar.

        Works by looping the PredictNext method.
        */
        EnjoLib::VecD Predict(const EnjoLib::VecD & data) const;

        /**
        Predict the next element. Index 0 = the latest bar.

        Aims to deliver a controlled experiment, eliminating the look-ahead bias.
        */
        virtual double PredictNext(const BufferDouble & datExpanding) const = 0;

        /**
        Predict the whole series, optimized. Index 0 = the earliest bar.

        You may provide the implementation if you know how to predict the whole series,
        without imposing a look-ahead bias. Otherwise the Predict() function shall be used.
        */
        virtual EnjoLib::VecD PredictVec(const EnjoLib::VecD & data)  const;

        /**
        Return the max lag of the predictor. The assumption is, that before there's enough data,
        the predictor cannot return anything else than @ERROR.
        */
        virtual unsigned GetLags() const = 0;

        virtual EnjoLib::VecD AssertNoLookaheadBiasGetVec(const EnjoLib::VecD & data) const;
        virtual void AssertNoLookaheadBias(const EnjoLib::VecD & data, const EnjoLib::VecD & predVec) const;
        
        virtual bool IsCustomScript() const;

        /// The error returned when there's not enough data for the prediction yet.
        static const double ERROR;

    protected:

    private:
};

#endif // IPREDICTOR_H
