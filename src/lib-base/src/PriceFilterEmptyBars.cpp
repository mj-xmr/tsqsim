#include "PriceFilterEmptyBars.h"
#include "IDataProvider.h"
#include "IBufferCandles.h"
#include "Candle.h"
//#include "CandleCalc.h"
#include "PriceFilterConfig.h"
#include "ConfigMan.h"
#include "ConfigTF2.h"
#include <STD/VectorCpp.hpp>
#include <Util/CoutBuf.hpp>

using namespace std;

PriceFilterEmptyBars::PriceFilterEmptyBars(){}
PriceFilterEmptyBars::~PriceFilterEmptyBars(){}

VecCan PriceFilterEmptyBars::Filter(const PriceFilterConfig & cfg, const IDataProvider & per) const
{
    const VecCan & canDef = per.GetCandles().GetDataVec();
    VecCan canRet;
    for (const Candle & can : canDef)
    {
        if (not can.IsDataValid())
        {
            continue;
        }

        if (can.IsDataUnchanging())
        {
            //cout << "All equal = " << can.GetOpen() << ", " << can.GetClose()<< endl;
            continue;
        }
        canRet.push_back(can);
    }
    const int sizeDiff = canDef.size() - canRet.size();
    if (not gcfgMan.cfgTF2->NETWORKED)
    {
        if (sizeDiff != 0)
        {
            LOGL << "Filtered " << sizeDiff << " unchanged bars\n";
        }
    }
    return canRet;
}
