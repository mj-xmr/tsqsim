#include "EnumStringMapSimulType.h"
#include <SimulatorType.h>

EnumStringMapSimulType::EnumStringMapSimulType()
{
    for (int i = 0; i <= int(SimulatorType::SIMUL_STANDARD); ++i)
    {
        SimulatorType type = SimulatorType(i);
        switch (type) // Generate compiler warnings
        {
            case SimulatorType::SIMUL_STANDARD:     Add(i, "Std"); break;
            case SimulatorType::SIMUL_MT:           Add(i, "MT"); break;
            case SimulatorType::SIMUL_BET:          Add(i, "Bet"); break;
            case SimulatorType::SIMUL_DISCOVERY:    Add(i, "Discov"); break;
            case SimulatorType::SIMUL_MAX_PROFIT:   Add(i, "Max prof"); break;
            case SimulatorType::SIMUL_IN_SAMPLE:    Add(i, "In samp"); break;
            
            case SimulatorType::SIMUL_TEFO:         Add(i, "TeFo"); break;
        }
    }
}

EnumStringMapSimulType::~EnumStringMapSimulType()
{
    //dtor
}
