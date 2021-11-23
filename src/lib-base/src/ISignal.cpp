#include "ISignal.h"
#include "State.h"
#include "Candle.h"
#include "ConfigGlob.h"
#include <Util/StackTrace.hpp>

#include <Util/Str.hpp>

using namespace std;
ISignal::ISignal(){}
ISignal::~ISignal(){}

EnjoLib::Str ISignal::GetSpecialText(const State & st) const
 { return ""; }

float ISignal::GetValue(const State & st) const
{
    return 0;
}