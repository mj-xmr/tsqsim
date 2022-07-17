#ifndef ISIMULATOR_H
#define ISIMULATOR_H

#include "StartEnd.h"
#include "Direction.h"
#include <Util/VecD.hpp>
#include <Template/IIterable.hpp>
#include <3rdParty/stdfwd.hh>

class IOptimizable;
class ISimulatorAccum;
class ISimulObserver;
class SvmWrapperProb;
class MatplotSimResultsMT;
class OptiVarF;

class ISimulator
{
    public:
        ISimulator();
        virtual ~ISimulator();

        virtual ISimulator * CloneRaw() const = 0; /// TODO: Make pure virtual
        virtual void Run() = 0;
        virtual void RunRaw(const StartEnd & startEndFrame = StartEnd()) {}
        /// Used to close all open positions in optimization
        virtual void Finalize(){}
        virtual void Iter(int i, const Direction * dir = nullptr) {}
        //virtual void ReinitOptiVars(const EnjoLib::IIterable<OptiVarF *> & opti){}
        virtual void ReinitOptiVars(const EnjoLib::VecD & optiVars){}

        void SetAccumulator(ISimulatorAccum * accum) { m_accum = accum; }
        void SetMatplotMT(MatplotSimResultsMT * mpMT) { m_mpMT = mpMT; }
        void SetSimulObserver(ISimulObserver * observer) { m_observer = observer; }
        void SetSvm(SvmWrapperProb * svm) { m_svm = svm; }

        virtual EnjoLib::Str ModelToStr() const;

    protected:

        ISimulatorAccum * m_accum = nullptr;
        MatplotSimResultsMT * m_mpMT = nullptr;
        ISimulObserver * m_observer = nullptr;
        SvmWrapperProb * m_svm = nullptr;

    private:
};

class ISimulatorBet : public ISimulator
{
    public:
        ISimulatorBet();
        virtual ~ISimulatorBet();

        virtual void Collect() = 0;
        virtual double GetChangeAverage(int hour) const = 0;
        virtual double GetChangeAverageMean() const = 0;
};

#endif // ISIMULATOR_H
