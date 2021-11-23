#include "IHasCandlesAccess.h"
#include "Candle.h"
#include "IBufferCandles.h"

IHasCandlesAccess::IHasCandlesAccess(const IBufferCandles & bufCan)
: Open(0)
, Close(1)
, High(2)
, Low(3)
{
    for (int i = 0; i < bufCan.Len(); ++i)
    {
        const Candle & c = bufCan[i];
        Open.m_data.push_back(c.GetOpen());
        Close.m_data.push_back(c.GetClose());
        High.m_data.push_back(c.GetHigh());
        Low.m_data.push_back(c.GetLow());
    }
}

IHasCandlesAccess::~IHasCandlesAccess(){}

float VecHiding::operator[] (const State & st) const
{
    const Candle & can = st.GetCandle();
    if (can.IsDataValid())
    {
        switch (type)
        {
            case 0:
                return can.GetOpen();
            case 1:
                return can.GetClose();
            case 2:
                return can.GetHigh();
            case 3:
                return can.GetLow();
        }

    }

    return m_data[st.i];
}
