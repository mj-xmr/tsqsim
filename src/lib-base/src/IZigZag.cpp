#include "IZigZag.h"
#include "XYSignalAdapter.h"
#include "IDataProvider.h"
#include "Candle.h"
#include "CandleCalc.h"
#include "IBufferCandles.h"

#include <Util/StackTrace.hpp>
#include <STD/VectorCpp.hpp>

#include <Math/GeneralMath.hpp>



using namespace std;

IZigZag::IZigZag(const IDataProvider & period)
: m_period(period)
, m_bufCan(period.GetCandles())
{}
IZigZag::~IZigZag(){}

EnjoLib::Array<XYPairDir> IZigZag::GetPlotXY() const
{
    return XYSignalAdapter().GetPlotXY(*this, *this);
}

float IZigZag::GetLengthAbs(const State & st) const
{
    const XYPairDir & xypair = GetPrevCurrXY(st);
    float valDiff = EnjoLib::GeneralMath().Fabs(xypair.one.y - xypair.two.y);
    //cout << "IndiZigZagHigh::GetLengthAbs() y1 = " << xypair.one.y << ", y2 = " << xypair.two.y << endl;
    return valDiff;
}

float IZigZag::GetExtrValue(const State & st) const
{
    int i = GetExtrIndex(st);
    if (st.bullish)
        return m_bufCan[i].GetHigh();
    else
        return m_bufCan[i].GetLow();
}

float IZigZag::CalcAngle(const State & st, bool now) const
{
    XYPairDir xypair = GetPrevCurrXY(st);
    if (now)
        xypair = XYPairToNow(st, xypair);

    float xDiff = EnjoLib::GeneralMath().Fabs(xypair.two.x - xypair.one.x);
    if (xDiff == 0)
        return 0;
    float ang = (xypair.two.y - xypair.one.y) / xDiff;
    return ang;
}

float IZigZag::CalcGain(const State & st, bool now) const
{
    XYPairDir xypair = GetPrevCurrXY(st);
    if (now)
        xypair = XYPairToNow(st, xypair);
    //cout << "Curr i = " << xypair.two.x << endl;
    //cout << "xypair.two.x = " << xypair.two.x << ", xypair.one.x = " << xypair.one.x << endl;
    //cout << "xypair.two.y = " << xypair.two.y << ", xypair.one.y = " << xypair.one.y << endl;
    float gain = (xypair.two.y - xypair.one.y);
    return gain;
}

XYPairDir IZigZag::XYPairToNow(const State & st, const XYPairDir & xyp) const
{
    const int   idxNow = st.i;
    const float valNow = m_period.GetClose(idxNow);
    return XYPairDir(xyp.two, XY(idxNow, valNow), st);
}

int IZigZag::GetExtrIndex(const State & st) const
{
    return GetExtrIndex(st, *this);
}

int IZigZag::GetExtrIndex(const State & st, const ISignal & sig) const
{
    int posThis = sig.GetPosLastSignal(st);
    if (posThis < 0)
        posThis = Len() - 1;
    int posInve = sig.GetPosLastSignal(st.Shift(posThis).Next().Invert());
    if (posInve < 0)
        posInve = Len() - 1;

    CandleCalc ccc;
    const IBufferCandles & bufCan = m_period.GetCandles();
    //PairInt minMax = ccc.GetMinMaxSlowFract(st.Shift(posInve), st.Shift(posThis), m_indiFud);
    PairInt minMax = ccc.GetMinMaxSlow(st.Shift(posInve), st.Shift(posThis), bufCan); // Much better!

    int pos = st.bullish ? minMax.one : minMax.two;
    return pos;
}

float IZigZag::GetExtrValueIdx(const State & st, int iExtr) const
{
    const Candle & can = m_period.GetCandles()[iExtr];
    //return can.GetExtrBody(st);
    return can.GetExtr(st);
}
