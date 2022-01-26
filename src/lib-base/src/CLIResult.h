#ifndef CLIRESULT_H
#define CLIRESULT_H

#include "ConfigSym.h"
#include "ConfigTS.h"

struct CLIResult
{
    CLIResult(const ConfigSym & confSym, const ConfigTS & confTS)
    : m_confSym(confSym)
    , m_confTS(confTS)
    {

    }

    ConfigSym m_confSym;
    ConfigTS m_confTS;

};

#endif // CLIRESULT_H
