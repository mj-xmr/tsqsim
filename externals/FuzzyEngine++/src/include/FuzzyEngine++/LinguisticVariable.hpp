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

#ifndef LINGUISTICVARIABLE_H_INCLUDED
#define LINGUISTICVARIABLE_H_INCLUDED

#include <map>

#include "globals.hpp"
#include "MembershipFunction.hpp"
#include "NoRulesFiredException.hpp"
#include "RulesParsingException.hpp"
#include "ForDefuzzification.hpp"

/**
 * Class for linguistic variables.
 */
class DLLINTERFACE LinguisticVariable
{
  public:
  /**
 * Constructor
 * @param name Name of this linguistic variable
 */
LinguisticVariable(std::string name);

LinguisticVariable() {} //FIXME ??? I've added this
virtual ~LinguisticVariable() {} //FIXME ??? I've added this

/**
 * Add a membership function.
 * @param mFunction MembershipFunction to be added.
 */
void add(MembershipFunction mFunction);
/**
 * Add a membership function given by its name and trapezoidal region.
 * @param name Name of the membership function.
 * @param start Min support value.
 * @param left_top Min top value.
 * @param right_top Max top value.
 * @param finish Max support value.
 */
void add(std::string name,double start, double left_top, double right_top, double finish);
/**
 * Return an exact copy of itself.
 * The copy is exact except that rules fired since the last reset()
 * will not influence defuzzification result.
 * @return engine.LinguisticVariable
 */
LinguisticVariable * copy();
/**
 * Defuzzify using centroid.
 * Memebership functions are scaled by product and combined by summation.
 * This method has to be completely redone (eliminated operations on discrete array,
 * support different modes of scaling and summation).
 * @return double Result of defuzzification
 * @exception fuzzyEngine.NoRulesFiredException This exception is thrown if no rules have
 * fired for this Linguistic Variable.
 */
double defuzzify();// throw(NoRulesFiredException);
/**
 * Return the name of this linguistic variable
 * @return java.lang.std::string
 */
std::string getLVName();
/**
 * Return a MembershipFunction belonging to this
 * LinguisticVariable by its name.
 * @param name java.lang.std::string Name of the membership function.
 * @return MemebershipFunction
 */
MembershipFunction getMembershipFunctionByName(std::string name);
/**
 * Perform fuzzification for an input value.
 * @param name Name of the membership function
 * @return double Returns result of fuzzification or -1 if fuzzification is impossible.
 */
double is(std::string name);
/**
 * Reset all rules that have previously fired for this LinguisticVariable.
 */
void reset();
/**
 * Set input value for this lingustic variable.
 * @param value double
 */
void setInputValue(double value);
/**
 * Provide access to the shared labels' weights hastable.
 * This method is used by FuzzyEngine in order to provide access to all labels
 * and weights by every rule. Current implementation requires that an instance of
 * LinguisticVariable can only be registered with one FuzzyEngine.
 * @param hash java.util.std::map<std::string, MembershipFunction>
 */
void setLabelWeightsHash(std::map<std::string, LinguisticVariable*> hash);
/**
 * Store result of a fired rule.
 * This methos is invoked if a rule fired. It stores fired rule's label,
 * name of the membership function for which the rule fired and membership value.
 * Stored information is used when calling defuzzify().
 * @param label Label of the fired rule, null if rule has no label.
 * @param name Name of the membership function
 * @param value Membership value.
 */
void set(std::string label, std::string name, double value);// throw(RulesParsingException);
/**
 * Set the name of this linguistic variable.
 * @return java.lang.std::string
 */
void setLVName(std::string name);

private:

	std::string thisLVname;
	std::map<std::string, MembershipFunction> storage;
	double input_value;
	std::vector < ForDefuzzification > for_defuzzification;

	//Min and max support values for defuzzification
	double minSupport;
	double maxSupport;

	//std::map<std::string, MembershipFunction> with labels' weights - value set by the fuzzy engine
	std::map<std::string, LinguisticVariable*> labelWeightsHash;

};

#endif // LINGUISTICVARIABLE_H_INCLUDED
