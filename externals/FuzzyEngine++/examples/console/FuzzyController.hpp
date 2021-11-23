#ifndef FUZZYCONTROLLER_HPP_INCLUDED
#define FUZZYCONTROLLER_HPP_INCLUDED

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
    double GetOutputTime();

    void Reset();
    void Evaluate() throw(std::exception);

  private:
    void Init();

    FuzzyEngine m_fuzzyEngine;

    std::vector <std::string> m_vRules;
    FuzzyBlockOfRules * m_fuzzyBlockOfRules;

    LinguisticVariable m_lingVarDistance;
    LinguisticVariable m_lingVarVelocity;
    LinguisticVariable m_lingVarTime;
};

#endif // FUZZYCONTROLLER_HPP_INCLUDED
