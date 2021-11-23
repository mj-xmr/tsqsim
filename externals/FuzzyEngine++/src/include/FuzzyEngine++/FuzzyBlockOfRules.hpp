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

#ifndef FUZZYBLOCKOFRULES_HPP_INCLUDED
#define FUZZYBLOCKOFRULES_HPP_INCLUDED

#include <vector>
#include <iosfwd>
#include "globals.hpp"
#include "EvaluationException.hpp"
#include "RulesParsingException.hpp"
#include "FuzzyRule.hpp"

class FuzzyEngine;


/**
 * Class for a block of fuzzy rules
 * @author: Edward Sazonov
 */
class DLLINTERFACE FuzzyBlockOfRules
{
public:
/**
 * This function evaluates this block, returns a lava.lang.std::string
 * containing evaluation result for every expression in the rule.
 * This function can be called only after parseBlock().
 */
std::string evaluateBlockText();// throw(EvaluationException);
/**
 * This function evaluates this block, does not return any diagnostic information.
 * This function can be called only after parseBlock().
 */
void evaluateBlock();// throw(EvaluationException);
/**
 * Returns true if any rule in the block has fired during a call to evaluateBlock()
 * or evaluateBlockText().
 * @return bool
 */
bool isRuleFired();
/**
 * Constructor
 * @param rules[] one-dimensional array of java.lang.std::string, containing all rules that will constitute this block
 */
FuzzyBlockOfRules(std::vector<std::string> rules);
/**
 * Constructor
 * @param rules a java.lang.std::string, containing all rules that will constitute this block (separated by \n)
 */
FuzzyBlockOfRules(std::string rules);
/**
 * Parse the rules in the block.
 * This call is only possible after the block has been registered with a fuzzy engine.
 * @exception engine.RulesParsingException Exception is thrown if any rule within block
 * generates a parsing error
 */
virtual ~FuzzyBlockOfRules();

void parseBlock();// throw(RulesParsingException);
/**
 * Set the pointer to the fuzzy engine.
 * This function is for the call FuzzyEngine.register(FuzzyBlockOfRules)
 * @param newFuzzyEngine Pointer to the fuzzy engine that will parse and compile this block of rules
 */
void setFuzzyEngine(FuzzyEngine * newFuzzyEngine);

private:
  void clearAllRules();
//	//Original text representation of rules
	std::vector<std::string> textRules;

	//Pointer to the fuzzy engine
	FuzzyEngine * fuzzyEngine;

	//Vector of all rules within block
	std::vector <FuzzyRule *> allRules;

	//Flag indicating a rule has fired
	bool flagRuleFired;
};


#endif // FUZZYBLOCKOFRULES_HPP_INCLUDED
