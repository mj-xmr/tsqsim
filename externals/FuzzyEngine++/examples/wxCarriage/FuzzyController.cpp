/***************************************************************
 * Author:    Szymon Ender ()
 * Created:   2010-11-21
 * Copyright: Szymon Ender ()
 * License:   GPL v.3
 **************************************************************/

#include "FuzzyController.hpp"
#include <FuzzyEngine++/FuzzyBlockOfRules.hpp>


FuzzyController::FuzzyController() :
m_lingVarDistance("distance"),
m_lingVarVelocity("velocity"),
m_lingVarForce("force")
{
  // Warning! This is NOT a perfectly adjusted controller!
  double z = 1;
  m_lingVarDistance.add("-med", -2,  -2,  -z, 0);
  m_lingVarDistance.add("zero",   -z, 0, 0, z);
  m_lingVarDistance.add("+med",   0, z, 2, 2);

  z = 0.2;
  m_lingVarVelocity.add("-med",  -1, -1, -z, 0);
  m_lingVarVelocity.add("zero",  -z, 0, 0, z);
  m_lingVarVelocity.add("+med",   0, z, 1, 1);

  m_lingVarForce.add("-med", -5, -4, -4 , -3);
  m_lingVarForce.add("zero", -0.1,  0,    0,   0.1);
  m_lingVarForce.add("+med", 3,  4, 4, 5);

  m_fuzzyEngine.regist(&m_lingVarDistance);
  m_fuzzyEngine.regist(&m_lingVarVelocity);
  m_fuzzyEngine.regist(&m_lingVarForce);


  m_vRules.push_back("if distance is -med then force is +med");
  m_vRules.push_back("if distance is zero then force is zero");
  m_vRules.push_back("if distance is +med then force is -med");

  m_vRules.push_back("if distance is zero and velocity is zero then force is zero");

  m_vRules.push_back("if velocity is -med then force is +med");
  m_vRules.push_back("if velocity is zero then force is zero");
  m_vRules.push_back("if velocity is +med then force is -med");

  m_vRules.push_back("if distance is -med and velocity is -med then force is +med");
  m_vRules.push_back("if distance is zero then force is zero");
  m_vRules.push_back("if distance is +med and velocity is +med then force is -med");

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

double FuzzyController::GetOutputForce() throw(std::exception)
{
  double ret = 0;
 // try
  {
    ret = m_lingVarForce.defuzzify();
  }
 // catch (NoRulesFiredException & e)
  {
 //   std::cout << "Exception 2: " << e.what() << std::endl;
  }
  return ret;
}

void FuzzyController::Reset()
{
  m_fuzzyEngine.reset();
}
