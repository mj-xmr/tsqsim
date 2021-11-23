#include "XYPairDir.h"
#include "Candle.h"

#include <Math/GeneralMath.hpp>
#include <Template/AlgoSTDThin.hpp>

using namespace EnjoLib;

XYPairDir::XYPairDir()
: XYPairDir(XY(0, 0), XY(0, 0), BUY)
{}
XYPairDir::XYPairDir(XY one, XY two, State st)
: XYPairDir(one, two, st.bullish)
{}

XYPairDir::XYPairDir(XY one, XY two, Direction dir)
: one(one), two(two), bullish(dir)
{}

XYPairDir::~XYPairDir()
{}

Candle XYPairDir::GetRange() const
{
    float mi = AlgoSTDThin().Min(one.y, two.y);
    float ma = AlgoSTDThin().Max(one.y, two.y);
    float mid = (mi + ma) / 2.0;
    Candle range(mid, mid, ma, mi);
    return range;
}

double XYPairDir::GetDiff(bool percent) const
{
    const double curr = one.y;
    const double prev = two.y; // flipped?

    const GeneralMath gmat;
    const double absol = gmat.AbsoluteChange(curr, prev);
    const double relat = gmat.RelativeChange(curr, prev);
    const double diff = percent ? relat : absol;
    return diff;
}

bool XYPairDir::IsValid() const
{
    return one.y && two.y && one.x && two.x;
}

bool XYPairDir::IsOtherInThis(const XYPairDir & tested) const
{
    const float refMax = AlgoSTDThin().Max(one.y,  two.y);
    const float refMin = AlgoSTDThin().Min(one.y,  two.y);
    const float tstMax = AlgoSTDThin().Max(tested.one.y, tested.two.y);
    const float tstMin = AlgoSTDThin().Min(tested.one.y, tested.two.y);

    bool cond = (tstMax < refMax && tstMin > refMin);
    return cond;
}
