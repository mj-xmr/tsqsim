#include "State.h"
#include "Candle.h"
#include <Util/Except.hpp>
#include <Util/Pair.hpp>

#include <STD/Iostream.hpp>

using namespace std;
//using namespace EnjoLib;

/// TODO: new / copy operations are the bottleneck! Just take the data from the candles

State::State(Direction bullish, int ii)
    : bullish(bullish)
    , i(ii)
    //, m_can(Corrade::Containers::Pointer<Candle>(new Candle()))
    //, m_tick(Corrade::Containers::Pointer<Candle>(new Candle()))
    {}
    
/*
State::State(const State & state)
{
    Copy(state);
}

State & State::operator=(const State & state)
{
    Copy(state);
    return *this;
}

void State::Copy(const State & state)
{
    this->bullish = state.bullish;
    this->i = state.i;
    //this->m_can = Candle(*state.m_can);
    this->m_can = Corrade::Containers::Pointer<Candle>(new Candle(*state.m_can));
    this->m_tick = Corrade::Containers::Pointer<Candle>(new Candle(*state.m_tick));
    //this->m_tick =  Candle(*state.m_tick);
}
*/
State::~State(){}

State State::Next(bool inverse) const
{
    return Shift(i+1, inverse);
}

State State::Shift(int ii, bool inverse) const
{
    if (ii < 0)
        throw EnjoLib::ExceptInvalidArg("Negative i!");
    State st(*this);
    st.i = ii;
    if (inverse)
        st = Invert();
    return st;
}

State State::Invert() const
{
    State st(*this);
    st.bullish = static_cast<Direction>(!st.bullish);
    return st;
}

void State::SetCandle(const Candle & can)
{
    //this->can = SharedPtr<Candle>(new Candle(can));
    //m_can = std::shared_ptr<Candle>(new Candle(can));
    //m_can = can;
    //m_can = Corrade::Containers::Pointer<Candle>(new Candle(can));
    m_can = can.price;
}

void State::SetTick(const Candle & can)
{
    //this->tick = SharedPtr<Candle>(new Candle(can));
    //this->m_tick = std::shared_ptr<Candle>(new Candle(can));
    //m_tick = can;
    //m_tick = Corrade::Containers::Pointer<Candle>(new Candle(can));
    m_tick = can.price;
}

Candle State::GetCandle() const
{
    return m_can;
}

Candle State::GetTick() const
{
    return m_tick;
}

void State::operator ++()
{
    *this = this->Next();
}

bool State::operator ==(const State& other) const
{
    return i == other.i && bullish == other.bullish;
}

bool State::operator < (const State& other) const
{
    return EnjoLib::MakePair(i, bullish) < EnjoLib::MakePair(other.i, other.bullish);
}

ostream& operator<<(ostream& os, const State& st)
{
    os << "(" << st.bullish << ", " << st.i << ")";
    return os;
}

EnjoLib::Ostream& operator<<(EnjoLib::Ostream& os, const State& st)
{
    os << "(" << st.bullish << ", " << st.i << ")";
    return os;
}
