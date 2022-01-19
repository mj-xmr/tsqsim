#include "PriceFilterSpreadMul.h"
#include "IDataProvider.h"
#include "IBufferCandles.h"
#include "Candle.h"
#include "CandleCalc.h"
#include "PriceFilterConfig.h"

#include <Math/MaxMinFind.hpp>
#include <STD/VectorCpp.hpp>

#include <Util/CoutBuf.hpp>
//#include <STD/Algorithm.hpp>

using namespace std;
using namespace EnjoLib;

PriceFilterSpreadMul::PriceFilterSpreadMul(){}

VecCan PriceFilterSpreadMul::Filter(const PriceFilterConfig & cfg, const IDataProvider & per) const
{
    const VecCan & canDef = per.GetCandles().GetDataVec();
    //return canDef; /// DISABLED
    LOGL << "PriceFilterSpreadMul::Filter() " << per.GetName() << Nl;
    if (cfg.spreadMulFilter <= 0)
    {
        return canDef;
    }

    const CandleCalc ccc;
    VecCan ret;
    EnjoLib::MaxMinFind<float> maxMinBody;
    EnjoLib::MaxMinFind<float> maxMinWick;
    for (int i = 0; i < int(canDef.size()); ++i) // Proper indexing
    {
        Candle cani = canDef.at(i);
        const int sti = per.GetCandles().ConvertIndex(i);
        const float limit = per.GetSpread(sti) * cfg.spreadMulFilter;
        const bool isReachedMax = maxMinBody.UpdateMax(cani.GetBodyMax());
        const bool isReachedMin = maxMinBody.UpdateMin(cani.GetBodyMin());
        maxMinWick.UpdateMax(cani.GetHigh());
        maxMinWick.UpdateMin(cani.GetLow());
        const float maxBodyDist = maxMinBody.GetMax() - maxMinBody.GetMin();
        if (maxBodyDist > limit)
        {
            cani.SetHigh(maxMinWick.GetMax());
            cani.SetLow (maxMinWick.GetMin());
            //if (false)
            {
                if (isReachedMax) {
                    cani.SetOpen(maxMinBody.GetMin());
                    cani.SetClose(maxMinBody.GetMax());
                }
                else if (isReachedMin) {
                    cani.SetOpen(maxMinBody.GetMax());
                    cani.SetClose(maxMinBody.GetMin());
                }
            }
            ret.push_back(cani);

            maxMinBody.Reset();
            maxMinWick.Reset();
        }
    }

    //std::reverse(ret.begin(), ret.end());
    //return canDef;
    return ret;
}

/*
VecCan PriceFilterSpreadMul::Filter(const PriceFilterConfig & cfg, const IDataProvider & per) const
{
    const VecCan & canDef = per.GetCandles().GetData();
    //return canDef; /// DISABLED
    cout << "PriceFilterSpreadMul::Filter() " << per.GetName() << endl;
    if (cfg.spreadMulFilter <= 0)
        return canDef;

    const CandleCalc ccc;
    VecCan ret;
    EnjoLib::MaxMinFind<float> maxMinBody;
    EnjoLib::MaxMinFind<float> maxMinWick;
    for (int i = canDef.size() - 1; i >= 0; --i)
    {
        Candle cani = canDef.at(i);
        const int sti = per.GetCandles().ConvertIndex(i);
        const float limit = per.GetSpread(sti) * cfg.spreadMulFilter;
        const bool isReachedMax = maxMinBody.UpdateMax(cani.GetBodyMax());
        const bool isReachedMin = maxMinBody.UpdateMin(cani.GetBodyMin());
        maxMinWick.UpdateMax(cani.GetHigh());
        maxMinWick.UpdateMin(cani.GetLow());
        const float maxBodyDist = maxMinBody.GetMax() - maxMinBody.GetMin();
        if (maxBodyDist > limit)
        {
            cani.SetHigh(maxMinWick.GetMax());
            cani.SetLow (maxMinWick.GetMin());
            //if (false)
            {
                if (isReachedMax) {
                    cani.SetOpen(maxMinBody.GetMax());
                    cani.SetClose(maxMinBody.GetMin());
                }
                else if (isReachedMin) {
                    cani.SetOpen(maxMinBody.GetMin());
                    cani.SetClose(maxMinBody.GetMax());
                }

            }

            ret.push_back(cani);


            maxMinBody.Reset();
            maxMinWick.Reset();
        }
    }

    std::reverse(ret.begin(), ret.end());
    //return canDef;
    return ret;
}
*/
