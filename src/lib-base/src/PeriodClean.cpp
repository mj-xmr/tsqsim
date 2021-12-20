#include "pch_base.h"

#include "PeriodClean.h"
#include "ISymbol.h"
#include "ConfigMan.h"
#include "ConfigTF2.h"
#include "PriceFilterType.h"
#include "IPriceFilter.h"
#include "PriceFilterFactory.h"
#include "Tick.h"
#include "TradeUtil.h"
#include "DataTech.h"
#include "IBufferCandles.h"
#include "BufferBool.h"
#include "BufferType.h"
#include "BufferTypeBool.h"
#include "BufferVecType.h"
#include "Buffer.h"
#include "ITicks.h"

#include <Util/Except.hpp>
#include <Util/PimplDeleter.hpp>
#include <Template/CorradePointer.h>
#include <Template/CacheRAMBare.hpp>
#include <Template/VectorViewable.hpp>
#include <Ios/Osstream.hpp>
#include <Util/CoutBuf.hpp>

#include <STD/VectorCpp.hpp>
#include <deque>

using namespace std;
using namespace EnjoLib;

struct PeriodClean::Impl
{
    Impl()
    : m_bufCan(m_candles)
    {
        
    }
    EnjoLib::VectorViewable<MaPeriods> m_maPeriods;
    VecCanView m_candles;
    BufferCandles m_bufCan;
};
PIMPL_DELETER(PeriodClean)

PeriodClean::PeriodClean(int numTicks, const ISymbol & sym)
: IPeriod(sym)
, m_numTicks(numTicks)
, m_symbolName(sym.GetName())
, m_mas(new EnjoLib::CacheRAMBare<int, EnjoLib::VecF>)
, m_impl(new Impl)
{
    m_usingTicks = gcfgMan.cfgTF2->SIM_USE_TICKS;
}

void PeriodClean::UpdateTech()
{
}

void PeriodClean::FilterPrice(const PriceFilterConfig & cfg)
{
    //cout << "PeriodClean::FilterPrice()\n";
    //FilterPricePriv(cfg, PRICE_FILTER_EMPTY_BARS); // Somehow worse
    FilterPricePriv(cfg, PRICE_FILTER_SPREAD_MUL);
}

void PeriodClean::FilterPricePriv(const PriceFilterConfig & cfg, const PriceFilterType & type)
{
    Corrade::Containers::Pointer<IPriceFilter> priceFilter = PriceFilterFactory().Create(type);
    const VecCan & canFiltered = priceFilter->Filter(cfg, *this);
    SetCandles(canFiltered);
}

void PeriodClean::CalcTech()
{
}

void PeriodClean::LimitData(int maxLatestBars)
{
    if (maxLatestBars == 0)
        return;
    if (maxLatestBars > int(GetImpl().m_candles.size()))
        maxLatestBars = GetImpl().m_candles.size();
    GetImplRW().m_candles.dat.erase(GetImplRW().m_candles.dat.begin(), GetImplRW().m_candles.dat.end() - maxLatestBars);
    m_data.Copy(GetImpl().m_bufCan.GetDataIter());
    LOGL << "PeriodClean::LimitData(): " << GetSymbolPeriodId() << ", Size now = " << GetImpl().m_candles.size() << EnjoLib::Nl;
}

void PeriodClean::FinalizeCandle()
{
    int tickDayMinutes = m_tickMod.GetDayMinute();
    if (tickDayMinutes % m_numTicks != 0 ) // A full period NOT achieved
    {
        FinalizeCandlePriv();
    }
}

int PeriodClean::GetNumTicks() const
{
    return m_numTicks;
}

int PeriodClean::GetNumSeconds() const
{
    int seconds = GetNumTicks() * 60;
    return seconds;
}

void PeriodClean::Feed(const EnjoLib::IIterableConst<Tick> & ticks, bool updateTech)
{
    for (const Tick & tick : ticks)
    {
        Feed(tick);
    }
}

void PeriodClean::Feed(const Tick & tick, bool updateTech)
{
    const double prevClose = m_tickMod.close;
    m_tickMod = tick;
    if (prevClose != 0)
    {
        m_tickMod.open = prevClose;
    }
    if (not tick.IsValid())
        return;
    m_currCandle.UpdateHighLow(m_tickMod); // used to be tick, but it messed up the opening of the next candle
    ++m_currTick;

    int tickDayMinutes = tick.GetDayMinute();
    const int minute = tick.minute;
    const int hour = tick.hour;
    const int day = tick.day;

    const bool exceededDay = day != m_dayPrev && m_dayPrev > 0;
    const bool exceededMinute = minute < m_minutePrev && m_minutePrev >= 0 && minute > 0 && hour != m_hourPrev;
    if (exceededMinute || exceededDay)
    {
        const TradeUtil tut;
        // A full period bar was missing. We have to improvise
        m_tickMod.minute = 0;
        if (exceededDay)
        {
            /// FIXME
            //m_tickMod.YYYYMMDDhhmmss = tut.DateZeroHour(tick.YYYYMMDDhhmmss());
            m_tickMod.hour = 0;
        }
        else
        {
            /// FIXME
            //m_tickMod.YYYYMMDDhhmmss = tut.DateZeroMinute(tick.YYYYMMDDhhmmss());
        }

        tickDayMinutes = m_tickMod.GetDayMinute();
    }
    if (tickDayMinutes % m_numTicks == 0 ) // A full period achieved
    //if (true ) // A full period achieved
    {
        FinalizeCandlePriv(updateTech);
    }
    m_minutePrev = minute;
    m_hourPrev = hour;
    m_dayPrev = day;
}

void PeriodClean::FinalizeCandlePriv(bool updateTech)
{
    //if (m_currTick == m_numTicks) // End of previous accumulation. If condition not met, ignore this candle
    {
        m_currCandle.SetClose(m_tickMod);
        GetImplRW().m_candles.dat.push_back(m_currCandle);
        m_data.Add(m_currCandle);
        if (updateTech)
        {
            UpdateTech();
        }
    }
    m_currTick = 0;
    m_currCandle = Candle();
    m_currCandle.SetOpen(m_tickMod);
    //m_opensNext.push_back(tick.open);
}

void PeriodClean::FeedFromLower(const Tick & tick, int periodRatio)
{
    m_currCandle.UpdateHighLow(tick); // Valid every time
    ++m_currTick;
    if (m_currTick == periodRatio) // A full period achieved (maybe shifted)
    {
        //if (m_currTick == m_numTicks) // End of previous accumulation. If condition not met, ignore this candle
        {
            m_currCandle.SetClose(tick);
            GetImplRW().m_candles.dat.push_back(m_currCandle);
            m_data.Add(m_currCandle);
        }
        m_currTick = 0;
        m_currCandle = Candle();
        m_currCandle.SetOpen(tick);
        m_currCandle.UpdateHighLow(tick);
    }
}

DataTech PeriodClean::GetTech(int numBack, int n) const
{
    DataTech tech;
    return tech;
}

DataOCHL PeriodClean::GetData(int numBack, int n) const
{
    DataOCHL data;
    if (n <= 0)
        n = numBack;
    data.Copy(BufferCandles(GetImpl().m_candles).GetBefore(numBack, n));
    return data;
}

DataTech PeriodClean::GetTechDate(DateInt dateStart, int n) const
{
    DataTech tech;
    return tech;
}

DataOCHL PeriodClean::GetDataDate(DateInt dateStart, int n) const
{
    DataOCHL data;
    return data;
}

DateInt PeriodClean::GetDateStart(int numBack) const
{
    return GetImpl().m_candles.at(GetImpl().m_candles.size() - numBack).GetDate();
}
DateInt PeriodClean::GetDateEnd(int numBack, int n) const
{
    if (n <= 0)
        n = numBack;
    return GetImpl().m_candles.at(GetImpl().m_candles.size() - numBack + n - 1).GetDate();
}

/*
// Buggy:
Buffer PeriodClean::GetMaUsedFast() const
{
    return Buffer(m_maUsedFast);
}
Buffer PeriodClean::GetMaUsedSlow() const
{
    return Buffer(m_maUsedSlow);
}
*/
Buffer PeriodClean::GetMa(int period) const
{
    return Buffer(m_mas->Get(period), "GetMa");
    //return m_maSlow.GetBuf();
}
const IBufferCandles & PeriodClean::GetCandles() const
{
    return GetImpl().m_bufCan;
    //return BufferCandles(GetImpl().m_candles);
}
/*
BufferCandles PeriodClean::GetCandles2() const
{
    return BufferCandles(GetImpl().m_candles2);
}
BufferCandles PeriodClean::GetCandles4() const
{
    return BufferCandles(GetImpl().m_candles4);
}
BufferCandles PeriodClean::GetCandles8() const
{
    return BufferCandles(GetImpl().m_candles8);
}
*/

float PeriodClean::GetSpread(int sti) const
{
    return m_sym.GetSpread(GetClose(sti));
}
float PeriodClean::GetLeverage() const
{
    return m_leverages.GetLeverage(GetSymbolName());
}

const EnjoLib::Array<EnjoLib::VecF> & PeriodClean::GetBufVec(const BufferVecType & type) const
{
    EnjoLib::Osstream oss;
    oss << "Not handled buffer type: " << (int)type.GetType() << Nl;
    throw EnjoLib::ExceptRuntimeError(oss.str());
}

Buffer PeriodClean::GetBuf(const BufferType & type) const
{
    return Buffer(EnjoLib::VecF(Len()), "PeriodClean::GetBuf");
    EnjoLib::Osstream oss;
    oss << "Not handled buffer type: " << (int)type.GetType() << Nl;
    throw EnjoLib::ExceptRuntimeError(oss.str());
}

BufferBool PeriodClean::GetBufBool(const BufferTypeBool & type) const
{
    return VecB(Len());
    EnjoLib::Osstream oss;
    oss << "Not handled bool buffer type: " << (int)type.type << Nl;
    throw EnjoLib::ExceptRuntimeError(oss.str());
}

int PeriodClean::Len() const
{
    return GetCandles().Len();
}

void PeriodClean::SetCandles(const std::deque<Candle> & candles)
{
    GetImplRW().m_candles = VecCan(candles.size());
    std::copy(candles.begin(), candles.end(), GetImplRW().m_candles.dat.begin());
    m_data.Copy(GetImpl().m_candles);
}
void PeriodClean::SetCandles(const VecCan & candles)
{
    GetImplRW().m_candles = candles;
    m_data.Copy(GetImpl().m_candles);
}
void PeriodClean::SetCandles(const std::deque<Tick> & candles)
{
    VecCan vcan;
    for (const Tick & t : candles)
    {
        if (not t.IsValid())
            continue;
        vcan.push_back(t.ToCandle());
        //Feed(t);
    }

    SetCandles(vcan);
}

EnjoLib::Str PeriodClean::GetSymbolPeriodId(char delim) const
{
    return GetSymbolName() + delim + GetName();
}

float PeriodClean::GetClose(int i) const
{
    return GetCandles()[i].GetClose();
}

bool PeriodClean::IsMetaTrader() const
{
    return m_sym.IsMetaTrader();
}

EnjoLib::Str PeriodClean::GetName() const
{
    return TradeUtil().MinutesToPeriodName(GetNumTicks());
}

const SRVisibleData & PeriodClean::GetSRVisible(Direction dir) const 
{ 
    throw EnjoLib::ExceptNotImpl(); 
}

EnjoLib::View<MaPeriods> PeriodClean::GetMaUsedPeriods() const { return GetImpl().m_maPeriods; };
const VecCanView & PeriodClean::CanData() const {  return GetImpl().m_candles; };
VecCan & PeriodClean::CanData() {  return GetImplRW().m_candles.dat; };

