#include "ISimulator.h"

#include <Statistical/Assertions.hpp>
#include <Util/Str.hpp>
#include <Util/CoutBuf.hpp>

using namespace std;

ISimulator::ISimulator()
{
}

ISimulator::~ISimulator()
{
}

EnjoLib::Str ISimulator::ModelToStr() const
{
    LOGL << "ISimulator::ModelToStr() Empty body\n";
    return "";
}

/*
ISimulator * ISimulator::CloneRaw() const
{
    EnjoLib::Assertions::Throw("Unimplemented", "ISimulator::CloneRaw()");
    return nullptr;
}
*/

ISimulatorBet::ISimulatorBet()
{
    //ctor
}

ISimulatorBet::~ISimulatorBet()
{
    //dtor
}
