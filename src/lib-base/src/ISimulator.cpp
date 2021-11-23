#include "ISimulator.h"
#include <Util/Str.hpp>
#include <Util/CoutBuf.hpp>

using namespace std;

ISimulator::ISimulator()
{
    //ctor
}

ISimulator::~ISimulator()
{
    //dtor
}

EnjoLib::Str ISimulator::ModelToStr() const
{
    LOGL << "ISimulator::ModelToStr() Empty body\n";
    return "";
}


ISimulatorBet::ISimulatorBet()
{
    //ctor
}

ISimulatorBet::~ISimulatorBet()
{
    //dtor
}
