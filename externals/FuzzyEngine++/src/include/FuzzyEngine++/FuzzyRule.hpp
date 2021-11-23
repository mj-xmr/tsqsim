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

#ifndef FUZZYRULE_HPP_INCLUDED
#define FUZZYRULE_HPP_INCLUDED

#include <iosfwd>

#include "globals.hpp"
#include "EvaluationException.hpp"
#include "FuzzyExpression.hpp"

/**
 * Container for a fuzzy rule.
 * This class contains vectors of left-part and right-part expressions
 * (before and after "then") for a fuzzy rule.
 */
class DLLINTERFACE FuzzyRule
{
  public:
/**
 * Evaluate left part and execute right part of a pre-parsed rule.
 * Changes value of the private variable evaluationResult.
 * This call will set flagRuleFired to true if any expression fires.
 * @return java.lang.String Returns text representation of the rule
 * with all expressions evaluated.
 */
std::string evaluateRuleText();// throw(EvaluationException);
/**
 * Evaluate left part and execute right part of a pre-parsed rule.
 * Changes value of the private variable evaluationResult.
 * This call will set flagRuleFired to true if any expression fires.
 */
void evaluateRule();// throw(EvaluationException);
/**
 * Returns the result of the left part evaluation.
 * @return double
 */
double getEvaluationResult();
/**
 * Return this rule's label.
 * @return java.lang.String
 */
std::string getLabel();
/**
 * Returns the java.lang.Vector containing all expression for the left part of the rule.
 * @return java.util.Vector
 */
std::vector< FuzzyExpression > & getLeftPartExpressions();
/**
 * Returns the java.lang.Vector containing all expression for the right part of the rule.
 * @return java.util.Vector
 */
std::vector< FuzzyExpression > & getRightPartExpressions();
/**
 * Returns true if the rule fired (during executeRule call).
 * @return boolean
 */
bool isRuleFired();
/**
 * Constructor.
 * @param lb This rule label (java.lang.String).
 */
FuzzyRule(std::string lb);
/**
 * Set label for this rule.
 * @param newLabel java.lang.String
 */
void setLabel(std::string newLabel);
/**
 * Constructor.
 */
FuzzyRule();

  private:
  //Label of this rule
	std::string label;

	//Left and right sides
	std::vector< FuzzyExpression > leftPartExpressions;
	std::vector< FuzzyExpression > rightPartExpressions;

	//Flag to indicate that this rules has fired
	bool flagRuleFired;
	double evaluationResult;

	//Nesting stack class
	class StackElement
	{
	  public:
		double accumulatedResult;
		bool flagAND;
		bool flagOR;

		StackElement(double acc, bool And, bool Or)
			{ accumulatedResult = acc; flagAND = And; flagOR = Or;}
	};
};


#endif // FUZZYRULE_HPP_INCLUDED
