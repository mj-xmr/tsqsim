#ifndef CLOSEPOSITIONFACTORYABS_H
#define CLOSEPOSITIONFACTORYABS_H

#include <Template/CorradePointerFwd.h>

#include "IClosePosition.h"
class IStrategy;

enum class ClosePositionType
{
	CLPOS_DUMMY,
	CLPOS_INVERSE,
	CLPOS_OSCI,
	CLPOS_UNIV_OSCI,
	CLPOS_FX_BOOK,
	CLPOS_MA_CROSS,
	CLPOS_LET_TP_RUN,
	CLPOS_AGGR,
	CLPOS_MACD,
	CLPOS_STRAT,
	CLPOS_STRAT_ALT,
	CLPOS_ALWAYS
};

class ClosePositionFactoryAbstract
{
	public:

	virtual Corrade::Containers::Pointer<IClosePosition> Create(const ClosePositionType & type, const IStrategy & strat) const = 0;
};

#endif // CLOSEPOSITIONFACTORYABS_H
