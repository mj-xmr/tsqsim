/***************************************************************
 * Author:    Szymon Ender ()
 * Created:   2010-11-21
 * Copyright: Szymon Ender ()
 * License:   GPL v.3
 **************************************************************/

#ifndef CARRIAGE_H_INCLUDED
#define CARRIAGE_H_INCLUDED

class Carriage
{
  public:
    Carriage();
    double GetPos() const;
    double GetVel() const;
    double GetPosPercent() const;
    double GetVelPercent() const;
    void SetPos( double posPercent );
    void SetVel( double velPercent );
    void Run( double t, double force );

  private:
    double m_pos;
    double m_vel;

    static const double c_mass;
    static const double c_g;
    static const double c_mi; // wsp tarcia
    static const double c_maxInputPos;
    static const double c_maxInputVel;
};

#endif // CARRIAGE_H_INCLUDED
