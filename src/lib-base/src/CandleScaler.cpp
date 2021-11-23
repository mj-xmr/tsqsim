#include "CandleScaler.h"
#include "Candle.h"

#include <Math/GeneralMath.hpp>
#include <Systems/Point.hpp>
#include <Util/StackTrace.hpp>
#include <Template/VectorViewable.hpp>

using namespace std;
using namespace EnjoLib;

CandleScaler::CandleScaler(){}
CandleScaler::~CandleScaler(){}

EnjoLib::VecF CandleScaler::Scale(const IterCan & vc, unsigned n) const
{
    const GMat gmat;
    EnjoLib::VecF ret, in;
    if (vc.empty())
        return ret;

    // Prepare input data
    in.push_back(vc.at(0).GetOpen()); // First element is the open
    for (const Candle & c : vc)
        in.push_back(c.GetClose()); // The other elements are simply closes

    const float deltaRet = (in.size()-1) / float(n-1); // Length of the new window
    if (deltaRet <= 0)
        throw EnjoLib::ExceptRuntimeError(STRACE_THROW("deltaRet <= 0"));

    for (unsigned i = 0; i < n; ++i)
    {
        const double pos = deltaRet * i;
        float val;
        if (gmat.Fmod(pos,1) == 0)
            val = in.at(pos); // A fixed integer point
        else
        {
            const int i1 = int(pos); // Between two fixed points of the original
            const int i2 = i1 + 1;
            const Point p1(i1, in.at(i1));
            const Point p2(i2, in.at(i2));
            val = gmat.LinearInterpol(pos, p1, p2);
        }
        ret.push_back(val);
    }

    return ret;
}
