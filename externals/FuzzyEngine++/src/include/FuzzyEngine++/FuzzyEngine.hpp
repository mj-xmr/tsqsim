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

#ifndef FUZZYENGINE_HPP_INCLUDED
#define FUZZYENGINE_HPP_INCLUDED

#include <iosfwd>
#include <stack>
#include <map>

#include "globals.hpp"
#include "FuzzyBlockOfRules.hpp"
#include "RulesParsingException.hpp"
#include "EvaluationException.hpp"
#include "LinguisticVariable.hpp"
#include "FuzzyRule.hpp"

class Hedge;

/**
 * This class evaluates rules given by std::string variables.
 * Evaluation is performed either on a single rule or a block of rules.
 */
class DLLINTERFACE FuzzyEngine
{
 public:
virtual ~FuzzyEngine();
/**
 * Add a hedge (derived from engine.Hedge) to the engine
 * @param hedge Implementation of a hedge
 */
void addHedge(Hedge * hedge);
/**
 * Evaluate block of rules (engine.FuzzyBlockOfRules)
 * @param block An instance of engine.FuzzyBlockOfRules
 */
void evaluateBlock(FuzzyBlockOfRules * block);// throw(EvaluationException);
/**
 * Parse and evaluate a fuzzy rule in text form.
 * Input values for the linguistic variables participating in the rule
 * have to be set before calling this function.
 * Call to FuzzyEngine.isRuleFired() will return "true" if the rule fired.
 * @param rule std::string containing the rule
 */
std::string evaluateRule(std::string rule);// throw(RulesParsingException);
/**
 * Returns "true" if a rule has fired during the last call to FuzzyEngine.evaluateRule(String).
 * If a block of rules has been evaluated, the function FuzzyBlockOfRules.isRuleFired()
 * should be called instead.
 * @return "True" if the last evaluated rules has fired, "false" if not.
 */
bool isRuleFired();

/**
 * Equivalent of FuzzyEngine.evaluateRule(String), but for the blocks of rules.
 * @param rule Textual represenation of a fuzzy rule.
 * @return parsedRule Parsed rule.
 * @exception engine.RulesParsingException This exception is thrown if an error occurs during parsing.
 *  Exception.getMessage() will return the reason for error.
 */
FuzzyRule * parseRule(std::string rule);// throw(RulesParsingException);
/**
 * Register a block of rules with the engine.
 * Every block has to be registered before it can be parsed.
 * @param block engine.FuzzyBlockOfRules to be registered.
 */
void regist(FuzzyBlockOfRules * block);// throw(std::exception);
/**
 * Register a linguistic variable with the engine.
 * Any lingustic variable participating in fuzzy evaluations should be registered with the engine.
 * The same lingustic variable cannot be registered with different engines if labels are used.
 * @param function fuzzyEngine.LinguisticVariable to be registered with the engine.
 */
void regist(LinguisticVariable * function);
/**
 * Reset all previously fired rules.
 * Call to this function clears all rules and resets the engine to its initial state.
 */
void reset();
/**
 * Constructor.
 * Engine initialization is performed here.
 */
FuzzyEngine();

  private:

  /**
 * Parse a rule like: if a is b and/or hedge, hedge c is d then e is f.
 * Recursive nesting for multilevel logical dependencies. Recursion is organized
 * by employing nesting Stack instead of recursive calls because
 * it allows easy storage of compiled rules (in block parsing mode)
 * Two modes of operation (rule evaluation or block parsing mode) are determined
 * by the value of the parameter "rule": if "rule" is equal to null, then the engine is in
 * rule evaluation mode and input values of all linguistic variables should be set
 * for the call to complete successfully. If "rule" points to an instance of FuzzyRule,
 * then only parsing is performed without performing actual evaluation of the rule.
 * Results of the parsing  are stored in the "rule".
 * @param tokens java.util.StringTokenizer Text representation of a fuzzy rule split into tokens.
 * @param rule FuzzyRule Container for the parsed rule (when operating in block parsing mode)
 * @return parsedRule java.lang.std::string Textual results of parsing are returned for review
 */
std::string parseExpression(std::vector<std::string> tokens,FuzzyRule * rule);// throw(RulesParsingException);
std::vector<std::string> Tokenize(const std::string& str, const std::string& delimiters = " ");


//Action constants
	static const int IF = 1;
	static const int THEN = 2;
	static const int IS = 3;
	static const int SET = 4;
	static const int AND = 5;
	static const int OR = 6;
	static const int LEFTP = 7;
	static const int RIGHTP = 8;
	static const int NOP = 9;
	static const int EXECUTE = 10;
	static const int HEDGE = 11;
	static const int RULE = 12;
	static const int UNDEFINED = 14;
	static const int WEIGHT = 15;
	static const int LV = 16;

	//Common subStates of the engine
	static const int READY = 100;
	static const int LV_READ = 101;
	static const int IS_READ = 102;
	static const int NOT_READ = 103;
	static const int HEDGE_READ = 104;
	static const int EXCEPTION = 105;

	//subStates of LABEL state
	static const int STORE_LABEL = 200;

	//subStates of EVALUATION state
	static const int COMPLETE_EVALUATION = 300;

	//subStates of EXECUTION state
	static const int RULE_READ = 400;
	static const int LABEL_READ = 401;
	static const int COMPLETE_EXECUTION = 402;

	//Fuzzy engine states
	static const int LABEL = 500;
	static const int EVALUATION = 501;
	static const int EXECUTION = 502;

	//Global engine state
	int engineState;

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

	//Hashtables
	std::map<std::string, int> controlHash;
	std::map<std::string, LinguisticVariable*> lvHash;
	std::map<std::string, Hedge*>  hedgesHash;
	std::map<std::string, LinguisticVariable*> labelWeightsHash;

	//Nesting stack
	std::stack < StackElement > nestingStack;

	bool flagRuleFired;
};


#endif // FUZZYENGINE_HPP_INCLUDED
