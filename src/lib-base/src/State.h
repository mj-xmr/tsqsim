#ifndef STATE_H
#define STATE_H

#include "Direction.h"
#include <Ios/Osstream.hpp>
#include <3rdParty/stdfwd.hh>
//#include "Candle.h"
//#include <3rdParty/stdfwd.hh>
//#include <Template/SafePtr.hpp>

//#include <Template/SharedPtr.hpp>
class Candle;

#include "PriceData.h"
//#include "Candle.h"
struct State
{
    State(Direction bullish = SELL, int ii = -1);
    //State(const State & state);
    //State & operator=(const State & state);
    virtual ~State();

    State Next(bool inverse = false) const;
    State Shift(int ii, bool inverse = false) const;
    State Invert() const;
    void SetCandle(const Candle & can);
    void SetTick(const Candle & can);
    Candle GetCandle() const;
    Candle GetTick() const;
    void operator ++();
    bool operator ==(const State& other) const;
    bool operator < (const State& other) const;
    friend std::ostream& operator<<(std::ostream& os, const State& st);
    friend EnjoLib::Ostream& operator<<(EnjoLib::Ostream& os, const State& st);

    Direction bullish;
    int i;

private:
    //void Copy(const State & state);
    //EnjoLib::SafePtr<Candle> m_can, m_tick;
    PriceData m_can, m_tick;
    //EnjoLib::SharedPtr<Candle> m_can, m_tick;
    //std::shared_ptr<Candle> m_can, m_tick; // This crashes
    //Candle m_can, m_tick;
};

#define ST const State & st

#endif // STATE_H
