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

#include <iostream>
#include "../include/FuzzyEngine++/FuzzyBlockOfRules.hpp"
#include "../include/FuzzyEngine++/FuzzyEngine.hpp"

/**
 * This function evaluates this block, returns a lava.lang.std::string
 * containing evaluation result for every expression in the rule.
 * This function can be called only after parseBlock().
 */
std::string FuzzyBlockOfRules::evaluateBlockText()// throw(EvaluationException)
{

	//Reset the flag
	flagRuleFired = false;

	std::string output;

	//Perform evaluation and execution of every rule
	std::vector <FuzzyRule*>::iterator it = allRules.begin();
	while ( it != allRules.end() )
	{
    try
    {
      std::string s = (*it)->evaluateRuleText();
      if((*it)->isRuleFired())
      {
        output+=s+"\n";
        flagRuleFired = true;
      }
    }
    catch(std::exception & e)
    {
    //Add exception handling
      std::cout << "Exception: " << e.what() << std::endl;
      throw EvaluationException(e.what());
    }
    ++it;
	}

	return output;
}
/**
 * This function evaluates this block, does not return any diagnostic information.
 * This function can be called only after parseBlock().
 */
void FuzzyBlockOfRules::evaluateBlock()// throw(EvaluationException)
{
	//Reset the flag
	flagRuleFired = false;

	//Perform evaluation and execution of every rule
	std::vector <FuzzyRule*>::iterator it = allRules.begin();
	while ( it != allRules.end() )
	{
      try
      {
        (*it)->evaluateRule();
        if((*it)->isRuleFired())	flagRuleFired = true;
      }
      catch(std::exception & e)
      {
      //Add exception handling
        std::cout << "Exception: " << e.what() << std::endl;
        throw EvaluationException(e.what());
      }
    ++it;
  }

}
/**
 * Returns true if any rule in the block has fired during a call to evaluateBlock()
 * or evaluateBlockText().
 * @return bool
 */
bool FuzzyBlockOfRules::isRuleFired()
{
	return flagRuleFired;
}
/**
 * Constructor
 * @param rules[] one-dimensional array of java.lang.std::string, containing all rules that will constitute this block
 */
FuzzyBlockOfRules::FuzzyBlockOfRules(std::vector<std::string> rules)
{
	textRules = rules;
}
/**
 * Constructor
 * @param rules a java.lang.std::string, containing all rules that will constitute this block (separated by \n)
 */
FuzzyBlockOfRules::FuzzyBlockOfRules(std::string rules)
{
	size_t start = 0;
	size_t end = 0;
	size_t length = rules.length();

	std::vector<std::string> ruleStrings;

	while ( end < length )
	{
    end = rules.find("\n", start);
    if ( end == std::string::npos )
      end = length;
    ruleStrings.push_back(rules.substr(start,end));
    start = end + 1;
	}

	textRules.assign(ruleStrings.begin(), ruleStrings.end());

	clearAllRules();
}

FuzzyBlockOfRules::~FuzzyBlockOfRules()
{
  clearAllRules();
}

/**
 * Parse the rules in the block.
 * This call is only possible after the block has been registered with a fuzzy engine.
 * @exception engine.RulesParsingException Exception is thrown if any rule within block
 * generates a parsing error
 */
void FuzzyBlockOfRules::parseBlock()// throw(RulesParsingException)
{
	//Check if fuzzyEngine is Ok
	if(fuzzyEngine==NULL)
		throw RulesParsingException(" - Cannot parse; the block should be registered first: ");

	//Check is rules are Ok
	if(textRules.empty())
		throw RulesParsingException(" - Cannot parse an empty block of rules: ");

	//Clear the rules
	clearAllRules();

	//Parse each rule
	for(size_t i=0; i<textRules.size(); i++)
	{
	  allRules.push_back(fuzzyEngine->parseRule(textRules[i]));
	  //std::cout << "fuzzyEngine->parseRule(textRules[i]) = " << fuzzyEngine->parseRule(textRules[i]) << std::endl;
	}
}

void FuzzyBlockOfRules::clearAllRules()
{
  for(size_t i=0; i<allRules.size(); i++)
	{
	  delete allRules[i];
	}
	allRules.clear();
}
/**
 * Set the pointer to the fuzzy engine.
 * This function is for the call FuzzyEngine.register(FuzzyBlockOfRules)
 * @param newFuzzyEngine Pointer to the fuzzy engine that will parse and compile this block of rules
 */
void FuzzyBlockOfRules::setFuzzyEngine(FuzzyEngine * newFuzzyEngine)
{
	fuzzyEngine = newFuzzyEngine;
}
