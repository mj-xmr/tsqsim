#include "XYSignalAdapter.h"
#include "XYPairDir.h"
#include "StateFactory.h"
#include "SignalBase.h"
#include "IHasXYPair.h"
#include <Template/CorradePointer.h>
#include <STD/VectorCpp.hpp>

XYSignalAdapter::XYSignalAdapter(){}
XYSignalAdapter::~XYSignalAdapter(){}

EnjoLib::Array<XYPairDir> XYSignalAdapter::GetPlotXY(const ISignal & sig, const IHasXYPair & ihxy) const
{
    std::vector<XYPairDir> ret;
    const StateFactory fact;
    for (int i = 0; i < sig.Len(); ++i)
    {
        const State stBull = *fact.Create(BUY, i);
        const State stBear = *fact.Create(SELL, i);
        if (sig.IsSignal(stBull))
        {
            XYPairDir el = ihxy.GetPrevCurrXY(stBull);
            if (el.one.y == 0 || el.two.y == 0)
                continue;
            ret.push_back(el);
        }
        else
        if (sig.IsSignal(stBear))
        {
            XYPairDir el = ihxy.GetPrevCurrXY(stBear);
            if (el.one.y == 0 || el.two.y == 0)
                continue;
            ret.push_back(el);
        }
    }
    return ret;
}
