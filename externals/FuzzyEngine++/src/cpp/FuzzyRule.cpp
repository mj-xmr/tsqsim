//Fuzzy engine for Java 0.1a
//Copyright (C) 2000  Edward S. Sazonov (esazonov youknowwhAT usa POT com)
//Fuzzy engine for C++ 0.1a
//Copyright (C) 2010  Szymon "Enjo" Ender (ender-sz youknowwhAT go2 POT pl)

//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General License
//as published by the Free Software Foundation; either version 2
//of the License, or (at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General License for more details.

//You should have received a copy of the GNU General License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#include <stack>
#include <sstream>

#include "../include/FuzzyEngine++/FuzzyRule.hpp"

std::string FuzzyRule::evaluateRuleText()// throw(EvaluationException)
{
	//Final result
	double accumulatedResult = 1.0;

	//Nesting Stack
	std::stack< StackElement > nestingStack;

	//Flags
	bool flagAND = false;
	bool flagOR = false;

	//Output string
	std::string out;

	//Evaluate
  std::vector< FuzzyExpression >::iterator it = leftPartExpressions.begin();
  while ( it != leftPartExpressions.end() )
  {
    FuzzyExpression & tempExpression = (*it);

	    //Extract flags
	    flagAND = tempExpression.flagAND;
	    flagOR = tempExpression.flagOR;

	    //If nesting up
	    for(int i=0; i<tempExpression.nestingUp; i++)
	    	{
			//Nesting
			nestingStack.push(StackElement(accumulatedResult,flagAND,flagOR));
			flagAND=flagOR=false;
			accumulatedResult = 0.0;
	    	}

	    //Evaluate expression
	    double tempResult = 0.0;
	    try
	    {
	    	tempResult = tempExpression.evaluateExpression();

	    	//Add to output string
	    	out+=tempExpression.getTextExpression();
	    	std::stringstream ssbuf;
	    	ssbuf << tempResult;
			std::string s = ssbuf.str();
			out += "(" + s.substr(0,s.length() > 3 ? 4 : 3) + ") ";
	    }
	    catch(std::exception & e)
	    {
		    //Add exception handling
		    //printf("Exception: "+e.what());
		    throw EvaluationException(e.what());
	    }


	    //If AND / OR / STORE operations
	    if(!flagAND && !flagOR)
	    	accumulatedResult = tempResult;
	    if(flagAND && !flagOR)
			accumulatedResult = accumulatedResult > tempResult ? tempResult : accumulatedResult;
	    if(!flagAND && flagOR)
			accumulatedResult = accumulatedResult < tempResult ? tempResult : accumulatedResult;

		//If nesting down
		for(int i=0; i<tempExpression.nestingDown; i++)
			{
			StackElement & tempSE = nestingStack.top();
			nestingStack.pop();
			flagAND = tempSE.flagAND;
			flagOR = tempSE.flagOR;

	 	    if(flagAND && !flagOR)
				accumulatedResult = accumulatedResult > tempSE.accumulatedResult ?
					tempSE.accumulatedResult : accumulatedResult;
	   		if(!flagAND && flagOR)
				accumulatedResult = accumulatedResult < tempSE.accumulatedResult ?
					tempSE.accumulatedResult : accumulatedResult;
			}

    ++it;
  }


	evaluationResult = accumulatedResult;

	//Reset the flag
	flagRuleFired = false;

	//Execute assignments
	it = rightPartExpressions.begin();
  while ( it != rightPartExpressions.end() )
  {
	    FuzzyExpression & tempExpression = (*it);

      try
      {
        double temp = tempExpression.executeExpression(evaluationResult,getLabel());
        //Add to output string
          out+=tempExpression.getTextExpression();
        std::stringstream ssbuf;
        ssbuf << temp;
        std::string s = ssbuf.str();
        out+="(" + s.substr(0,s.length() > 3 ? 4 : 3) + ") ";

        if(temp>0.0)	flagRuleFired = true;

      }
      catch(std::exception & e)
      {
        //Add exception handling
        //System.out.println("Exception: "+e.getMessage());
        throw EvaluationException(e.what());
      }
      ++it;
		}
	return out;
}
/**
 * Evaluate left part and execute right part of a pre-parsed rule.
 * Changes value of the private variable evaluationResult.
 * This call will set flagRuleFired to true if any expression fires.
 */
void FuzzyRule::evaluateRule()// throw(EvaluationException)
{
	//Final result
	double accumulatedResult = 1.0;

	//Nesting Stack
	std::stack< StackElement >nestingStack;

	//Flags
	bool flagAND = false;
	bool flagOR = false;

	//Evaluate
  std::vector< FuzzyExpression >::iterator it = leftPartExpressions.begin();
  while ( it != leftPartExpressions.end() )
  {
    FuzzyExpression & tempExpression = (*it);

	    //Extract flags
	    flagAND = tempExpression.flagAND;
	    flagOR = tempExpression.flagOR;

	    //If nesting up
	    for(int i=0; i<tempExpression.nestingUp; i++)
	    	{
			//Nesting
			nestingStack.push(StackElement(accumulatedResult,flagAND,flagOR));
			flagAND=flagOR=false;
			accumulatedResult = 0.0;
	    	}

	    //Evaluate expression
	    double tempResult = 0.0;
	    try
	    {
	    	tempResult = tempExpression.evaluateExpression();

	    }
	    catch(std::exception & e)
	    {
		    //Add exception handling
		    //System.out.println("Exception: "+e.getMessage());
		    throw EvaluationException(e.what());
	    }


	    //If AND / OR / STORE operations
	    if(!flagAND && !flagOR)
	    	accumulatedResult = tempResult;
	    if(flagAND && !flagOR)
			accumulatedResult = accumulatedResult > tempResult ? tempResult : accumulatedResult;
	    if(!flagAND && flagOR)
			accumulatedResult = accumulatedResult < tempResult ? tempResult : accumulatedResult;

		//If nesting down
		for(int i=0; i<tempExpression.nestingDown; i++)
			{
			StackElement & tempSE = nestingStack.top();
			nestingStack.pop();
			flagAND = tempSE.flagAND;
			flagOR = tempSE.flagOR;

	 	    if(flagAND && !flagOR)
				accumulatedResult = accumulatedResult > tempSE.accumulatedResult ?
					tempSE.accumulatedResult : accumulatedResult;
	   		if(!flagAND && flagOR)
				accumulatedResult = accumulatedResult < tempSE.accumulatedResult ?
					tempSE.accumulatedResult : accumulatedResult;
			}

			++it;
		}

	evaluationResult = accumulatedResult;

	//Reset the flag
	flagRuleFired = false;

	//Execute assignments
	it = rightPartExpressions.begin();
  while ( it != rightPartExpressions.end() )
  {
	    FuzzyExpression & tempExpression = (*it);


		    try
		    {
	 	   		if(tempExpression.executeExpression(evaluationResult,getLabel())>0.0)
	 	   			flagRuleFired = true;
	  	  	}
	   		catch(std::exception & e)
	    	{
		    //Add exception handling
		    //System.out.println("Exception: "+e.getMessage());
		    throw EvaluationException(e.what());
	    	}

      ++it;
		}
}
/**
 * Returns the result of the left part evaluation.
 * @return double
 */
double FuzzyRule::getEvaluationResult()
{
	return evaluationResult;
}
/**
 * Return this rule's label.
 * @return java.lang.String
 */
std::string FuzzyRule::getLabel() {
	return label;
}
/**
 * Returns the java.lang.Vector containing all expression for the left part of the rule.
 * @return java.util.Vector
 */
std::vector< FuzzyExpression > & FuzzyRule::getLeftPartExpressions() {
	return leftPartExpressions;
}
/**
 * Returns the java.lang.Vector containing all expression for the right part of the rule.
 * @return java.util.Vector
 */
std::vector< FuzzyExpression > & FuzzyRule::getRightPartExpressions()
{
	return rightPartExpressions;
}
/**
 * Returns true if the rule fired (during executeRule call).
 * @return boolean
 */
bool FuzzyRule::isRuleFired()
{
	return flagRuleFired;
}
/**
 * Constructor.
 * @param lb This rule label (java.lang.String).
 */
FuzzyRule::FuzzyRule(std::string lb)
{
	label = lb;
	flagRuleFired = false;
}
/**
 * Set label for this rule.
 * @param newLabel java.lang.String
 */
void FuzzyRule::setLabel(std::string newLabel)
{
	label = newLabel;
	flagRuleFired = false;
	evaluationResult = 0;
}
/**
 * Constructor.
 */
FuzzyRule::FuzzyRule()
{
  flagRuleFired = false;
  evaluationResult = 0;
}
