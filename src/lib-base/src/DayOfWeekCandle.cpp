#include "DayOfWeekCandle.h"
#include "Candle.h"

using namespace EnjoLib;
DayOfWeekCandle::DayOfWeekCandle(const Candle & can)
: DayOfWeek(can.GetYear(), can.GetMonth(), can.GetDay())
{}

DayOfWeekCandle::~DayOfWeekCandle()
{}
