#ifndef ISIMULATORTS_H
#define ISIMULATORTS_H

#include "ISimulator.h"

#include <Util/VecFwd.hpp>

enum class PredictorOutputType;

class ISimulatorTS : public ISimulator
{
    public:
        ISimulatorTS();
        virtual ~ISimulatorTS();

        //virtual void Collect() = 0;
        //virtual double GetChangeAverage(int hour) const = 0;
        //virtual double GetChangeAverageMean() const = 0;

        virtual const EnjoLib::VecD & GetOutputSeries(const PredictorOutputType & type) const = 0;
        virtual float GetScorePred() const = 0;
        virtual float GetScoreStationarity() const = 0; /// TODO: Make a separate simulator for stationarity?
        virtual void SetSilent() = 0;
        virtual void PrintOpti() const = 0;

    protected:


    private:
};

#endif // ISIMULATORTS_H
