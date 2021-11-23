/***************************************************************
 * Author:    Szymon Ender ()
 * Created:   2010-11-21
 * Copyright: Szymon Ender ()
 * License:   GPL v.3
 **************************************************************/

#ifndef FUZZYCONTROLLER_HPP_INCLUDED
#define FUZZYCONTROLLER_HPP_INCLUDED

#include <stdexcept>
#include <FuzzyEngine++/FuzzyEngine++.hpp>
class FuzzyBlockOfRules;

class FuzzyController
{
  public:
    FuzzyController();
    FuzzyController( double pos, double vel );
    virtual ~FuzzyController();

    void SetInputPosition( double pos );
    void SetInputVelocity( double vel );
    double GetOutputForce() throw(std::exception);

    void Reset();
    void Evaluate() throw(std::exception);

  private:
    void Init();

    FuzzyEngine m_fuzzyEngine;

    std::vector <std::string> m_vRules;

    FuzzyBlockOfRules * m_fuzzyBlockOfRules;

    LinguisticVariable m_lingVarDistance;
    LinguisticVariable m_lingVarVelocity;
    LinguisticVariable m_lingVarForce;
};

#endif // FUZZYCONTROLLER_HPP_INCLUDED
