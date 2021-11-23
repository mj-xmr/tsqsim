#include "PeriodRandomizer.h"
#include "IPeriod.h"
#include "IBufferCandles.h"
#include "ITicks.h"
#include "Tick.h"
#include <Math/GeneralMath.hpp>
#include <Math/RandomMath.hpp>
#include <Template/AlgoSTDThin.hpp>
#include <Math/GeneralMath.hpp>
#include <random>
#include <functional>

using namespace std;
using namespace EnjoLib;

PeriodRandomizer::~PeriodRandomizer(){}
PeriodRandomizer::PeriodRandomizer(const IPeriod & per, int seed)
: m_sym(per.GetSymbol())
, m_per(per)
{
    RandomMath().RandSeed(seed);
}

static bool randomBool() {
    static auto gen = std::bind(std::uniform_int_distribution<>(0,1),std::default_random_engine());
    return gen();
}

void PeriodRandomizer::SetInvertOn()
{
	m_invertOn = true;
}

CorPtr<ITicks> PeriodRandomizer::Randomize(float percent, bool tryInvert) const
{
    const GeneralMath gmat;
    // Corrade::Containers::Pointer<IPeriod> per = m_perFact.Create(m_per.GetNumTicks(), m_sym);
    const CorPtr<ITicks> & ticks = m_per.GetCandles().ToTicks();
    const vector<Tick> & ticksOrig = ticks->GetTicks3();
    CorPtr<ITicks> ticksNew;
    const Tick & tifkFirst = ticksOrig.at(0);
    bool invert = tryInvert ? randomBool() : false;
	if (m_invertOn)
	{
		invert = tryInvert;
	}
    for (size_t i = 0; i < ticksOrig.size(); ++i)
    {
        if (i == 0)
        {
            const Tick & tickOrig = ticksOrig.at(i);
            Tick tickNew = tickOrig;
            if (invert) {
                InverseTick(&tickNew, tifkFirst);
            }
            UpdateTick(&tickNew, percent);

            ticksNew->Add(tickNew);
        }
        else
        {
            const Tick & tickOrigPrev = ticksOrig.at(i-1);
            const Tick & tickOrigCurr = ticksOrig.at(i);
            const Tick & tickNewPrev = ticksNew->GetTicks3().at(i-1);
            const float randOpenAdj = tickNewPrev.close - tickOrigPrev.close;

            Tick tickNew = tickOrigCurr;
            tickNew.open += randOpenAdj;

            if (invert) {
                InverseTick(&tickNew, tifkFirst);
            }
            UpdateTick(&tickNew, percent);

            ticksNew->Add(tickNew);
        }
    }
    //per->Feed(ticksNew);
    //per->CalcTech();
    return ticksNew;
    //return per;
}

void PeriodRandomizer::UpdateTick(Tick * tickNew, float percent) const
{
    const float diffHiLo = tickNew->hi - tickNew->lo;
    tickNew->close += CalcRandAdj(diffHiLo, percent);
    tickNew->hi += CalcRandAdj(diffHiLo, percent);;
    tickNew->lo += CalcRandAdj(diffHiLo, percent);;

    if (tickNew->hi < AlgoSTDThin().Max(tickNew->close, tickNew->open))
        tickNew->hi = AlgoSTDThin().Max(tickNew->close, tickNew->open);
    if (tickNew->lo > AlgoSTDThin().Min(tickNew->close, tickNew->open))
        tickNew->lo = AlgoSTDThin().Min(tickNew->close, tickNew->open);
}

void PeriodRandomizer::InverseTick(Tick * tickNew, const Tick & tifkFirst) const
{
    const float diffHi = EnjoLib::GeneralMath().Fabs(tickNew->hi - tickNew->close);
    const float diffLo = EnjoLib::GeneralMath().Fabs(tickNew->lo - tickNew->close);
    tickNew->close = -(tickNew->close - tifkFirst.close) + tifkFirst.close;
    //tickNew->open =  -(tickNew->open  - tifkFirst.close) + tifkFirst.close;
    tickNew->hi = tickNew->close + diffLo;
    tickNew->lo = tickNew->close - diffHi;

    if (tickNew->hi < AlgoSTDThin().Max(tickNew->close, tickNew->open))
        tickNew->hi = AlgoSTDThin().Max(tickNew->close, tickNew->open);
    if (tickNew->lo > AlgoSTDThin().Min(tickNew->close, tickNew->open))
        tickNew->lo = AlgoSTDThin().Min(tickNew->close, tickNew->open);
}

float PeriodRandomizer::CalcRandAdj(float diffHiLo, float percent) const
{
    const RandomMath gmat;
    const float rand = gmat.Rand(-percent, percent);
    const float randAdj = rand * diffHiLo;
    return randAdj;
}
