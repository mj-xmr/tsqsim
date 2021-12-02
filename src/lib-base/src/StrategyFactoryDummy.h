#ifndef STRATEGYFACTORYDUMMY_H
#define STRATEGYFACTORYDUMMY_H

#include "IStrategy.h"
#include "StrategyFactoryAbstract.h"
class StrategyType;

class IPeriod;
class ISymbol;
class LabelsMan;
class StrategyFactoryDummy : public StrategyFactoryAbstract
{
    public:
        StrategyFactoryDummy();
        virtual ~StrategyFactoryDummy();
    Corrade::Containers::Pointer<IStrategy> Create(const StrategyType & type, const IPeriod & period) const override;
    Corrade::Containers::Pointer<IStrategy> CreateRetraceLabel(const IPeriod & period, const LabelsMan & labMan) const override;
    Corrade::Containers::Pointer<IStrategy> CreatePair(const IPeriod & period, const IPeriod & periodCorr) const override;
};

#endif // STRATEGYFACTORY_H
