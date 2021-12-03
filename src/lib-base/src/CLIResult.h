#ifndef CLIRESULT_H
#define CLIRESULT_H

#include "ConfigSym.h"

struct CLIResult
{
    CLIResult(const ConfigSym & confSym)
    : m_confSym(confSym)
    {
        
    }
    
    ConfigSym m_confSym;
    
};

#endif // CLIRESULT_H
