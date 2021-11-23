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

#include "../include/FuzzyEngine++/FuzzyExpression.hpp"

double FuzzyExpression::evaluateExpression()// throw( EvaluationException )
{
	double result = 0.0;

	//Perform evaluation
	//if(LV!=null && MF!=null) // FIXME
	if( ! MF.empty() )
		result = LV->is(MF);
	else
		throw EvaluationException(" - Missing linguistic variable or membership function: ");

	if(result == -1)
 		 throw EvaluationException(" - Unable to perform fuzzy evaluation: ");

	//Apply hedges if needed
	std::vector <Hedge*>::iterator it = hedges.begin();
	while ( it != hedges.end() )
  {
      result = (*it)->hedgeIt(result);
      ++it;
  }

	return result;
}
/**
 * Execute this fuzzy expression with the given value and label.
 * @param value Double result of the last fired expression.
 * @param label String label of this rule.
 * @exception engine.RulesParsingException This exception is thrown
 * if an error occurs during evaluation.
 */
double  FuzzyExpression::executeExpression(double value, std::string label)// throw(EvaluationException)
{
	double temp = value;

	//Apply hedges if needed
  std::vector <Hedge*>::iterator it = hedges.begin();
	while ( it != hedges.end() )
  {
      temp = (*it)->hedgeIt(temp);
      ++it;
  }

	//Perform evaluation
	//if(LV!=null && MF!=null) // FIXME
	if( ! MF.empty() )
		{
		if(temp>0.0)
			{
			try	{
				LV->set(label, MF, temp);
				}
			catch(std::exception & e)
				{throw EvaluationException(e.what());}
			}
		}
	else
		{
		throw EvaluationException(" - Missing linguistic variable or membership function: ");
		}

	return temp;

}
/**
 * Return text representation of this expression.
 * @return java.lang.String
 */
std::string FuzzyExpression::getTextExpression()
{
	return textExpression;
}
/**
 * Constructor. Create an fuzzy expression "something is hedge, hedge, ... something".
 * For example, if expression is "temperature is not very high" then
 * lVariable = temperature,
 * mVariable = normal,
 * hVector = not, very,
 * textRepresentation = temperature is not very high.
 * This class is a service class for FuzzyRule and should not be used otherwise.
 * @param lv engine.LinguisticVariable Lingustic variable
 * @param mf java.lang.String Membership function
 * @param hVector java.util.Vector Vector containing all the hedges
 * @param textRepresentation java.lang.String Text representation of this expression
 */
FuzzyExpression::FuzzyExpression(LinguisticVariable * lVariable, std::string mVariable, std::vector<Hedge*> hVector, std::string textRepresentation)
{
	LV = lVariable;
	MF = mVariable;
	hedges = hVector;
	textExpression = textRepresentation;

  flagAND = false;
	flagOR = false;

	nestingUp = 0;
	nestingDown = 0;
}

FuzzyExpression::~FuzzyExpression()
{
  std::vector <Hedge*>::iterator it = hedges.begin();
	while ( it != hedges.end() )
  {
    delete (*it);
    ++it;
  }
}
