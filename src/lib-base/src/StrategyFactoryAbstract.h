#ifndef STRATEGYFACTORYABS_H
#define STRATEGYFACTORYABS_H

#include <Template/CorradePointerFwd.h>

#include "IStrategy.h"
class StrategyType;

class IPeriod;
class ISymbol;
class LabelsMan;
class StrategyFactoryAbstract
{
    public:
                StrategyFactoryAbstract();
        virtual ~StrategyFactoryAbstract();
        virtual Corrade::Containers::Pointer<IStrategy> Create(const StrategyType & type, const IPeriod & period) const = 0;
        virtual Corrade::Containers::Pointer<IStrategy> CreateRetraceLabel(const IPeriod & period, const LabelsMan & labMan) const = 0;
        virtual Corrade::Containers::Pointer<IStrategy> CreatePair(const IPeriod & period, const IPeriod & periodCorr) const = 0;
};

#endif // STRATEGYFACTORYABS_H
