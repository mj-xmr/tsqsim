#include "pch_base.h"

#include "BufferCandles.h"
#include "TradeUtilThin.h"
#include "ITicks.h"
#include "Tick.h"
#include "Candle.h"
#include "BufferTpl.h"

#include <Ios/Osstream.hpp>
#include <Util/Str.hpp>
#include <Util/StackTrace.hpp>
#include <Template/VectorViewable.hpp>

#include <STD/VectorCpp.hpp>
#include <STD/Algorithm.hpp>

using namespace std;

static const char * m_nameCan = "Candles";

BufferCandles::~BufferCandles(){}
BufferCandles::BufferCandles(const VecCanView & v)
: m_data(v)
{
}

static bool CompareCandles(const Candle & first, const Candle & second)
{
    return first.GetDate() < second.GetDate();
}

static VecCan::const_iterator GetIterator(const BufferCandles & bufCan, DateInt date, bool secure = true)
{
    if (secure)
    {
        if (!bufCan.HasCandle(date))
        {
            EnjoLib::Osstream oss; oss << "Candle not found. Use HasCandle first! DateInt = " << date;
            throw EnjoLib::ExceptRuntimeError(STRACE_THROW(oss.str()));
        }
    }

    Candle dateCarrier;
    dateCarrier.SetDate(date);
    return std::lower_bound(bufCan.GetDataVec().begin(), bufCan.GetDataVec().end(), dateCarrier, CompareCandles);
}

bool BufferCandles::HasCandle(DateInt date) const
{
    Candle dateCarrier;
    dateCarrier.SetDate(date);
    const VecCan & d = GetDataVec();
    return std::binary_search(d.begin(), d.end(), dateCarrier, CompareCandles);
    
    for (const Candle & can : m_data)
    {
        if (can.GetDate() == date)
        {
            return true;
        }
    }
    return false;
}

const Candle & BufferCandles::GetCandle(DateInt date) const
{
    auto it = GetIterator(*this, date);
    return *it;
}

long BufferCandles::GetIndexSti(DateInt date) const
{
    auto it = GetIterator(*this, date);
    long dist = -std::distance(GetDataVec().end(), it) - 1;
    return dist;
}

long BufferCandles::GetIndexStiPrev(DateInt date) const
{
    auto it = GetIterator(*this, date, false);
    long dist = -std::distance(GetDataVec().end(), it);
    return dist;
}

const Candle & BufferCandles::GetNearestCandle(DateInt date) const
{
    auto it = GetIterator(*this, date, false);
    if (it == GetDataVec().end())
    {
        EnjoLib::Osstream oss; oss << "GetNearestCandle(): Candle not found. Use HasNearestCandle first! DateInt = " << date;
        throw EnjoLib::ExceptRuntimeError(STRACE_THROW(oss.str()));
    }
    return *it;
}

bool BufferCandles::HasNearestCandle(DateInt date) const
{
    auto it = GetIterator(*this, date, false);
    return it != GetDataVec().end();
}

const Candle & BufferCandles::GetExactOrNearestCandle(DateInt date) const
{
    if (HasCandle(date))
        return GetCandle(date);
    return GetNearestCandle(date);
}

CorPtr<ITicks> BufferCandles::ToTicks() const
{
    const VecCan & d = GetDataVec();

    CorPtr<ITicks> t = ITicks::Create();
    for (const Candle & c : d)
    {
        t->Add(c.ToTick());
    }
    return t;
}



/*
Candle BufferCandles::operator[](unsigned i) const
{
    return m_buf[i];
}

Candle BufferCandles::operator[](const State & st) const
{
    return m_buf[st];
}

unsigned BufferCandles::ConvertIndex(unsigned i) const
{
    return m_buf.ConvertIndex(i);
}

VecCan BufferCandles::GetAfter(unsigned iFrom, unsigned num) const
{
    return m_buf.GetAfter(iFrom, num);
}

VecCan BufferCandles::GetBefore(unsigned iUntil, unsigned num) const
{
    return m_buf.GetBefore(iUntil, num);
}

const VecCan & BufferCandles::GetData() const
{
    return m_buf.GetData();
}

int BufferCandles::Len() const
{
    return m_buf.Len();
}
*/
Candle BufferCandles::operator[](unsigned i) const
{
    return BufferTpl<Candle>(m_data.dat, m_nameCan)[i];
}

unsigned BufferCandles::ConvertIndex(unsigned i) const
{
    return TradeUtilThin::ConvertIndex(i, m_data.size());
    //return (*m_buf).ConvertIndex(i);
    //return BufferTpl<Candle>(m_data.dat, m_nameCan).ConvertIndex(i);
}

Candle BufferCandles::operator[](const State & st) const
{
    //return BufferTpl<Candle>(m_data.dat, m_nameCan)[st];
    return this->operator[](st.i);
}

VecCan BufferCandles::GetAfter(unsigned iFrom, unsigned num) const
{
    return BufferTpl<Candle>(m_data.dat, m_nameCan).GetAfter(iFrom, num);
}

VecCan BufferCandles::GetBefore(unsigned iUntil, unsigned num) const
{
    return BufferTpl<Candle>(m_data.dat, m_nameCan).GetBefore(iUntil, num);
}

const VecCan & BufferCandles::GetDataVec() const
{
    return BufferTpl<Candle>(m_data.dat, m_nameCan).GetData();
}

const IterCan & BufferCandles::GetDataIter() const
{
    return m_data;
}

int BufferCandles::Len() const
{
    return BufferTpl<Candle>(m_data.dat, m_nameCan).Len();
}

