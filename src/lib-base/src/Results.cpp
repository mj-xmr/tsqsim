#include "Results.h"

using namespace EnjoLib;

ResultCandle::~ResultCandle(){}
ResultCandle::ResultCandle(const Candle & value, bool status)
: Result<Candle>(value, status)
{}

ResultState::~ResultState(){}
ResultState::ResultState(const State & value, bool status)
: Result<State>(value, status)
{}
