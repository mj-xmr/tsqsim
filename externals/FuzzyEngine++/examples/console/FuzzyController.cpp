#include <iostream>
#include "FuzzyController.hpp"
#include <FuzzyEngine++/FuzzyBlockOfRules.hpp>

FuzzyController::FuzzyController() :
m_lingVarDistance("distance"),
m_lingVarVelocity("velocity"),
m_lingVarTime("time")
{
  // Warning! This is NOT a perfectly adjusted controller!
  double z = 35.0;
  m_lingVarDistance.add("-big",   -180, -180, -180, -90);
  m_lingVarDistance.add("-med",   -180, -90,  -90, -z);
  m_lingVarDistance.add("-small", -90,  -z,  -z, 0);
  m_lingVarDistance.add("zero",   -z, 0, 0, z);
  m_lingVarDistance.add("+small", 0,  z,  z, 90);
  m_lingVarDistance.add("+med",   z, 90, 90, 180);
  m_lingVarDistance.add("+big",   90, 180, 180, 180);

  m_lingVarVelocity.add("zero", 0,  0, 0, 0.1);
  m_lingVarVelocity.add("small", 0,  0.2, 0.2, 0.5);
  m_lingVarVelocity.add("med",   0.2, 0.5, 0.5, 1);
  m_lingVarVelocity.add("big",   0.5, 1, 1, 1);

  m_lingVarTime.add("-big",   -1, -0.9, -0.9, -0.7);
  m_lingVarTime.add("-med",   -0.9, -0.5, -0.5, -0.1);
  m_lingVarTime.add("-small", -0.2, -0.05, -0.05 , 0);
  m_lingVarTime.add("zero",   -0.1,  0,    0,   0.1);
  m_lingVarTime.add("+small", 0,   0.05, 0.05, 0.2);
  m_lingVarTime.add("+med",   0.3, 0.4, 0.4, 0.5);
  m_lingVarTime.add("+big",   0.7, 0.9, 0.9, 1);

  m_fuzzyEngine.regist(&m_lingVarDistance);
  m_fuzzyEngine.regist(&m_lingVarVelocity);
  m_fuzzyEngine.regist(&m_lingVarTime);

  m_vRules.push_back("if distance is +small and velocity is big then time is +small");
  m_vRules.push_back("if distance is +med   and velocity is big then time is +med");
  m_vRules.push_back("if distance is +big   and velocity is big then time is +med");

  m_vRules.push_back("if distance is +small and velocity is med then time is +small");
  m_vRules.push_back("if distance is +med   and velocity is med then time is +med");
  m_vRules.push_back("if distance is +big   and velocity is med then time is +big");

  m_vRules.push_back("if distance is +small and velocity is small then time is +med");
  m_vRules.push_back("if distance is +med   and velocity is small then time is +big");
  m_vRules.push_back("if distance is +big   and velocity is small then time is +big");


  m_vRules.push_back("if distance is -small and velocity is big then time is -small");
  m_vRules.push_back("if distance is -med   and velocity is big then time is -small");
  m_vRules.push_back("if distance is -big   and velocity is big then time is -med");

  m_vRules.push_back("if distance is -small and velocity is med then time is -small");
  m_vRules.push_back("if distance is -med   and velocity is med then time is -med");
  m_vRules.push_back("if distance is -big   and velocity is med then time is -big");

  m_vRules.push_back("if distance is -small and velocity is small then time is -med");
  m_vRules.push_back("if distance is -med   and velocity is small then time is -big");
  m_vRules.push_back("if distance is -big   and velocity is small then time is -big");

  // faster version - use only if your rules don't change on the fly
  m_fuzzyBlockOfRules = new FuzzyBlockOfRules(m_vRules);
  m_fuzzyEngine.regist(m_fuzzyBlockOfRules);
  m_fuzzyBlockOfRules->parseBlock();
}

FuzzyController::~FuzzyController()
{
  delete m_fuzzyBlockOfRules;
}

void FuzzyController::Evaluate() throw(std::exception)
{
    // slower. Use only if you change the rules on the fly
//      for ( std::vector <std::string>::const_iterator it = m_vRules.begin(); it != m_vRules.end(); ++it )
//      {
//        m_fuzzyEngine.evaluateRule( *it );
//      }

    // faster
    //std::cout << fuzzyBlockOfRules.evaluateBlockText() << "\n";
    // or even faster:
    m_fuzzyBlockOfRules->evaluateBlock();
}

void FuzzyController::SetInputPosition( double pos )
{
  m_lingVarDistance.setInputValue(pos);
}

void FuzzyController::SetInputVelocity( double vel )
{
  m_lingVarVelocity.setInputValue(vel);
}

double FuzzyController::GetOutputTime()
{
  double ret = 0;
  try
  {
    ret = m_lingVarTime.defuzzify();
  }
  catch (NoRulesFiredException & e)
  {
    std::cout << "Exception 2: " << e.what() << std::endl;
  }
  return ret;
}

void FuzzyController::Reset()
{
  m_fuzzyEngine.reset();
}
