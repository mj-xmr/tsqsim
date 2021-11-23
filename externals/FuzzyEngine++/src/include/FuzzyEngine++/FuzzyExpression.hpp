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

#ifndef FUZZYEXPRESSION_HPP_INCLUDED
#define FUZZYEXPRESSION_HPP_INCLUDED

#include "globals.hpp"
#include "EvaluationException.hpp"
#include "LinguisticVariable.hpp"
#include "Hedge.hpp"

/**
 * Contains single fuzzy expression in the form "LV is hedge, hedge, ... MF"
 */
class DLLINTERFACE FuzzyExpression
{
	public:
/**
 * Evaluate this fuzzy expression, compute and store result.
 * @return Result of evaluation
 * @exception engine.RulesParsingException This exception is thrown
 * if an error occurs during evaluation
 */
double evaluateExpression();// throw(EvaluationException);
/**
 * Execute this fuzzy expression with the given value and label.
 * @param value Double result of the last fired expression.
 * @param label String label of this rule.
 * @exception engine.RulesParsingException This exception is thrown
 * if an error occurs during evaluation.
 */
double  executeExpression(double value, std::string label);// throw(EvaluationException);
/**
 * Return text representation of this expression.
 * @return java.lang.String
 */
std::string getTextExpression();
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
FuzzyExpression(LinguisticVariable * lVariable, std::string mVariable, std::vector <Hedge*> hVector, std::string textRepresentation);

virtual ~FuzzyExpression();

//Public flags for structuring a rule - have no accessors
	bool flagAND;
	bool flagOR;

	//Nesting counters - have no accessors
	int nestingUp;
	int nestingDown;

  private:
//Linguistic variable
	LinguisticVariable * LV;

	//Member function
	std::string MF;

	//Vecot of hedges - the sequence of appearance is equivalent to Stack.pop() operations
	std::vector <Hedge *> hedges;


	//Text representation of this expression
	std::string textExpression;

};

#endif // FUZZYEXPRESSION_HPP_INCLUDED
