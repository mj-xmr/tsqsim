#ifndef PERIODRANDOMIZER_H
#define PERIODRANDOMIZER_H

#include "types.h"

#include <Template/CorradePointer.h>

class Tick;
class ITicks;
class IPeriod;
class ISymbol;
class PeriodFactoryAbstract;
class PeriodRandomizer
{
    public:
        PeriodRandomizer(const IPeriod & per, int seed = 0);
        virtual ~PeriodRandomizer();

        //EnjoLib::SafePtr<IPeriod> Randomize(float percent, bool tryInvert = true) const;
        CorPtr<ITicks> Randomize(float percent, bool tryInvert = true) const;
	void SetInvertOn();
    protected:

    private:
        void InverseTick(Tick * tickNew, const Tick & tifkFirst) const;
        void UpdateTick(Tick * tickNew, float percent) const;
        float CalcRandAdj(float diffHiLo, float percent) const;

        const ISymbol & m_sym;
        const IPeriod & m_per;
	bool m_invertOn = false;
};

#endif // PERIODRANDOMIZER_H
