#ifndef ABSTRACTS_H
#define ABSTRACTS_H

#include "Direction.h"

class IPeriod;
class MasAdapter;
class MaPeriods;
class IStrategy;
class State;
class Candle;

class Abstracts
{
    public:
        Abstracts(const IPeriod & period);
        virtual ~Abstracts();


        virtual int AbstractGetLastPosSignalStoch(const State & st) const = 0;
        virtual int AbstractGetLastPosSignalSmooth(const State & st) const = 0;
        virtual int AbstractGetLastPosSignalMas(const State & st) const = 0;
        virtual int AbstractGetLastPosSignalFractalUp(const State & st) const = 0;
        virtual int AbstractGetLastPosSignalFractalDown(const State & st) const = 0;

        virtual bool AbstractIsBullishHiddenDivergence(int i, bool potential = false) const = 0;
        virtual bool AbstractIsBearishHiddenDivergence(int i, bool potential = false) const = 0;
        virtual bool AbstractIsHiddenDivergence(const State & st, bool potential = false) const = 0;
        virtual float AbstractGetMaDiff(int i) const = 0;
        virtual int AbstractGetSmoothLastPeak(int i) const = 0;
        virtual int AbstractGetSmoothLastTrough(int i) const = 0;
        virtual float AbstractGetSpreadProfit(int i) const = 0;
        virtual float AbstractGetSmoothLine(int i) const = 0;
        virtual float AbstractGetMainLine(int i) const = 0;
        virtual float AbstractGetMaSlow(int i) const = 0;
        virtual float AbstractGetMaFast(int i) const = 0;
        virtual float AbstractGetMa(int i, int period) const = 0;
        virtual MaPeriods AbstractGetMaps(int i) const = 0;
        virtual float AbstractGetLow(int i) const = 0;
        virtual float AbstractGetHigh(int i) const = 0;
        virtual float AbstractGetClose(int i) const = 0;
        virtual float AbstractGetOpen(int i) const = 0;
        // virtual float AbstractAbs(float in) const = 0;
        virtual float AbstractMax(float one, float two) const = 0;
        virtual float AbstractMin(float one, float two) const = 0;
        virtual Direction AbstractInverseDirection(Direction dir) const = 0;

        virtual bool AbstractIsSignalStoch(const State & st, bool potential = false, float filter = 0) const = 0;
        virtual bool AbstractIsSignalSmooth(const State & st, bool potential = false, float filter = 0) const = 0;
        virtual bool AbstractIsSignalStochAny(const State & st, bool potential = false, float filter = 0) const = 0;
        virtual bool AbstractIsSignalStochUpDown(const State & st) const = 0;
        virtual bool AbstractIsSignalMas(const State & st) const = 0;
        virtual bool AbstractIsSignalStdDevRelative(int i) const = 0;
        virtual bool AbstractIsSignalStdDevCross(const State & st) const = 0;
        virtual bool AbstractIsSignalFractalUp(const State & st) const = 0;
        virtual bool AbstractIsSignalFractalDown(const State & st) const = 0;


        //virtual bool AbstractIsSignalPinbar(const State & st) const = 0;

        virtual float GetPullbackExtremePrice(const State & st) const = 0;
        virtual float GetBeforePullbackPrice(const State & st) const = 0;
        virtual float GetPriceMaRelationBeforeSig(const State & st) const = 0;

        virtual bool IsBuy(unsigned shift) const = 0;
        virtual bool IsInDir(unsigned shift, Direction bullish) const = 0;
        virtual unsigned Len() const = 0;

        //
        virtual float GetMaValue(int period, int i) const = 0;
        virtual int GetMaMin() const = 0;
        virtual int GetMaMax() const = 0;

        virtual const Candle GetCandle(int i) const = 0;

    protected:
        const IPeriod & m_period;
    private:
        //Abstracts(const Abstracts & other);

};

#endif // ABSTRACTS_H
