/***************************************************************
 * Author:    Szymon Ender ()
 * Created:   2010-11-21
 * Copyright: Szymon Ender ()
 * License:   GPL v.3
 **************************************************************/

#include "Carriage.h"

const double Carriage::c_mass = 10;
const double Carriage::c_g = 9.81;
const double Carriage::c_mi = 0.3;
const double Carriage::c_maxInputPos = 2;
const double Carriage::c_maxInputVel = 1;


Carriage::Carriage()
{
  m_pos = m_vel = 0;
}

double Carriage::GetPos() const
{
  return m_pos;
}

double Carriage::GetVel() const
{
  return m_vel;
}

double Carriage::GetPosPercent() const
{
  return GetPos() / c_maxInputPos;
}

double Carriage::GetVelPercent() const
{
  return GetVel() / c_maxInputVel;
}

void Carriage::SetPos( double posPercent )
{
  m_pos = posPercent * c_maxInputPos;
}

void Carriage::SetVel( double velPercent )
{
  m_vel = velPercent * c_maxInputVel;
}

void Carriage::Run( double t, double force )
{
  t /= 1000; // convert to seconds
  m_vel += force / c_mass * t;
  double friction = c_mi * m_vel;
  m_vel -= friction * t;
  m_pos += m_vel * t;

  const double velDisspiation = 0.75;
  if ( m_pos > c_maxInputPos)
  {
    m_vel = - m_vel * velDisspiation; // bounce
    m_pos = c_maxInputPos;
  }

  if ( m_pos < -c_maxInputPos)
  {
    m_vel = - m_vel * velDisspiation;
    m_pos = -c_maxInputPos;
  }

}


