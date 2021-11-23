#ifndef TAKEPROFITFACTORYABS_H
#define TAKEPROFITFACTORYABS_H

#include <Template/CorradePointerFwd.h>

#include "ITakeProfit.h"

enum class TakeProfitType
{
	TP_DUMMY,
	TP_FIXED,
	TP_HILO,
	TP_HILO_CANDLE,
	TP_LONG_WICK,
	TP_STRAT
};

class TakeProfitFactoryAbstract
{
	public:
	virtual Corrade::Containers::Pointer<ITakeProfit> Create(const TakeProfitType & type) const = 0;
};

#endif // TAKEPROFITFACTORYABS
