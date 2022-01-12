#ifndef OPTIHIGH_H
#define OPTIHIGH_H

#include <Util/Str.hpp>

class ISymbol;
class IPeriod;
class OptimizerBase;
class ISimulator;
class IOptimizable;
class SimulatorFactoryAbstract;
class OptimizerFactoryAbstract;

class OptiHigh
{
    public:
        OptiHigh();
        virtual ~OptiHigh();
        
        EnjoLib::Str WalkForwardOptiIndiv(const ISymbol & sym, const IPeriod & per, int iprogress, int totalSize, const OptimizerFactoryAbstract & optiFact, 
                                          ISimulator & sim, const SimulatorFactoryAbstract & simFact 
                                          /// TODO: Decide if the simulator should hold data, then factory isn't needed, or:
                                          /// pass a specific data holder, then the factory is needed, but the simulator isn't.
                                          ) const;

    protected:

    private:
};

#endif // OPTIHIGH_H
