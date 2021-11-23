#include "pch_base.h"

#include "EstimUtil.h"
#include "IDataProvider.h"
#include "Candle.h"
#include "CandleCalc.h"
#include "IBufferCandles.h"
#include "BufferType.h"
#include "Buffer.h"
#include <Template/AlgoSTDThin.hpp>
#include <Template/CacheRAMBare.hpp>
#include <STD/VectorCpp.hpp>
#include <Util/Pair.hpp>
#include <Math/GeneralMath.hpp>

using namespace EnjoLib;

EstimUtil::~EstimUtil(){}
EstimUtil::EstimUtil(const IDataProvider & dat)
: m_dat(dat)
, m_cache(new CacheRAMBare<EnjoLib::Pair<int, int>, Array<XYd>>)
{
}

Array<XYd> EstimUtil::GetSamplesTargetsXY(int sooner, int later) const
{
    const int sizeMin = 4;
    if (sooner < later)
        AlgoSTDThin().Swap(sooner, later);
    if (sooner == 0)
        return Array<XYd>();

    const Array<XYd> & ret = GetPrice(sooner, later);
    //const Array<XYd> & ret = GetEMA(sooner, later);

    if (ret.size() < sizeMin)
    {
        return Array<XYd>();
    }
    return ret;
}

Array<XYd> EstimUtil::GetPrice(int sooner, int later) const
{
    const auto & key = EnjoLib::MakePair(sooner, later);
    if (m_cache->Has(key))
    {
        return m_cache->Get(key);
    }
    
    std::vector<XYd> ret;
    ret.reserve(abs(sooner - later));
    //const CandleCalc cc;
    const IBufferCandles & bufCan = m_dat.GetCandles();
    const int bufLen = bufCan.Len();
    for (int i = sooner; i >= later && i >= 0 && i < bufLen; --i)
    {
        const Candle & can = bufCan[i];
        //ret.push_back(XYd(i, can.GetHigh()));
        //ret.push_back(XYd(i, can.GetLow()));
        ret.emplace_back(XYd(i, can.GetClose())); // ?
        //ret.push_back(XYd(i, cc.GetMidPrice(can))); // ?
    }
    ret.shrink_to_fit();
    return m_cache->Add(key, ret);
}

Array<XYd> EstimUtil::GetEMA(int sooner, int later) const
{
    std::vector<XYd> ret;
    const Buffer & emaFast = m_dat.GetBuf(BUF_MA_FAST);
    for (int i = sooner; i >= later && i >= 0 && i < emaFast.Len(); --i)
    {
        ret.push_back(XYd(i, emaFast[i])); // ?
    }
    return ret;
}
