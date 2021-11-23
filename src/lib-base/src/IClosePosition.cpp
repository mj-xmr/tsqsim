#include "IClosePosition.h"
#include "IStrategy.h"

IClosePosition::IClosePosition(const IStrategy & strat)
: m_strat(strat)
{
    //ctor
}

IClosePosition::~IClosePosition()
{
    //dtor
}

unsigned IClosePosition::LenProt() const
{
    return m_strat.Len();
}
