#ifndef IZIGZAG_H
#define IZIGZAG_H

#include "SignalBase.h"
#include "IHasXYPair.h"

class IBufferCandles;
class IDataProvider;

class IZigZag : public SignalBase, public IHasXYPair
{
    public:
        IZigZag(const IDataProvider & period);
        virtual ~IZigZag();

        EnjoLib::Array<XYPairDir> GetPlotXY() const override;
        float GetLengthAbs(const State & st) const;
        float GetExtrValue(const State & st) const;
        float CalcAngle(const State & st, bool now) const;
        float CalcGain(const State & st, bool now) const;
        XYPairDir XYPairToNow(const State & st, const XYPairDir & xyp) const;

        virtual int GetExtrIndex(const State & st) const;
        float GetExtrValueIdx(const State & st, int iExtr) const;

        const IDataProvider & GetPer() const { return m_period; }


        const IDataProvider & m_period;
        const IBufferCandles & m_bufCan;

    protected:
        int GetExtrIndex(const State & st, const ISignal & sig) const;

    private:


};

#endif // IZIGZAG_H
