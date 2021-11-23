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
#include <sstream>
#include "../include/FuzzyEngine++/FuzzyEngine.hpp"
#include "../include/FuzzyEngine++/HedgeNot.hpp"
#include "../include/FuzzyEngine++/HedgeVery.hpp"
#include "../include/FuzzyEngine++/HedgeSomewhat.hpp"

const int FuzzyEngine:: IF;
	const int FuzzyEngine:: THEN;
	const int FuzzyEngine:: IS;
	const int FuzzyEngine:: SET;
	const int FuzzyEngine:: AND;
	const int FuzzyEngine:: OR;
	const int FuzzyEngine:: LEFTP;
	const int FuzzyEngine:: RIGHTP;
	const int FuzzyEngine:: NOP;
	const int FuzzyEngine:: EXECUTE;
	const int FuzzyEngine:: HEDGE;
	const int FuzzyEngine:: RULE;
	const int FuzzyEngine:: UNDEFINED;
	const int FuzzyEngine:: WEIGHT;
	const int FuzzyEngine:: LV;

FuzzyEngine::~FuzzyEngine()
{
  std::map<std::string, Hedge*>::iterator it = hedgesHash.begin();
	while ( it != hedgesHash.end())
  {
    delete(it->second);
    ++it;
  }

  {
    std::map<std::string, LinguisticVariable*>::iterator it;

//    it = lvHash.begin();
//    while ( it != lvHash.end())
//    {
//      delete(it->second);
//      ++it;
//    }

    it = labelWeightsHash.begin();
    while ( it != labelWeightsHash.end())
    {
      delete(it->second);
      ++it;
    }
  }

}

void FuzzyEngine::addHedge(Hedge * hedge)
{
	hedgesHash.insert(make_pair(hedge->getName(),hedge));
}
/**
 * Evaluate block of rules (engine.FuzzyBlockOfRules)
 * @param block An instance of engine.FuzzyBlockOfRules
 */
void FuzzyEngine::evaluateBlock(FuzzyBlockOfRules * block)// throw(EvaluationException)
{
	block->evaluateBlock();
}
/**
 * Parse and evaluate a fuzzy rule in text form.
 * Input values for the linguistic variables participating in the rule
 * have to be set before calling this function.
 * Call to FuzzyEngine.isRuleFired() will return "true" if the rule fired.
 * @param rule std::string containing the rule
 */
std::string FuzzyEngine::evaluateRule(std::string rule)// throw(RulesParsingException)
{
	//Reset the flag
	flagRuleFired = false;

	//Split input std::string into tokens and return delimeters along with tokens
	//java.util.StringTokenizer tokens = new java.util.StringTokenizer(rule.trim(),new String("( )"),true);
	std::vector<std::string> tokens = Tokenize(rule);

	//Result string
	std::string result;
//	for (int i = 0; i < tokens.size(); ++i)
//	{
//	  std::cout << i << " " << tokens[i] << std::endl;
//	}

	try
	{
		result = parseExpression(tokens,NULL);
	}
	catch(RulesParsingException & e)
	{
		throw RulesParsingException(std::string("\nError parsing rule: ")+std::string(rule)+
                              std::string("\n")+std::string(e.what()));
	}


	if(isRuleFired())	return "Fired: "+result;
	else				return "";
}
/**
 * Returns "true" if a rule has fired during the last call to FuzzyEngine.evaluateRule(String).
 * If a block of rules has been evaluated, the function FuzzyBlockOfRules.isRuleFired()
 * should be called instead.
 * @return "True" if the last evaluated rules has fired, "false" if not.
 */
bool FuzzyEngine::isRuleFired()
{
	return flagRuleFired;
}

/**
 * Equivalent of FuzzyEngine.evaluateRule(String), but for the blocks of rules.
 * @param rule Textual represenation of a fuzzy rule.
 * @return parsedRule Parsed rule.
 * @exception engine.RulesParsingException This exception is thrown if an error occurs during parsing.
 *  Exception.getMessage() will return the reason for error.
 */
FuzzyRule * FuzzyEngine::parseRule(std::string rule)// throw(RulesParsingException)
{
	//Split input std::string into tokens and return delimeters along with tokens
	//java.util.StringTokenizer tokens = new java.util.StringTokenizer(rule.trim(),new String("( )"),true);
	std::vector<std::string> tokens = Tokenize(rule);

	//Output rule
	FuzzyRule * parsedRule = new FuzzyRule();

	try
	{
		parseExpression(tokens, parsedRule);
	}
	catch(RulesParsingException & e)
	{
		throw RulesParsingException("\nError parsing rule: "+rule+"\n"+e.what());
	}

	return parsedRule;
}
/**
 * Register a block of rules with the engine.
 * Every block has to be registered before it can be parsed.
 * TODO implement
 * @param block engine.FuzzyBlockOfRules to be registered.
 */
void FuzzyEngine::regist(FuzzyBlockOfRules * block)// throw(std::exception)
{
  block->setFuzzyEngine(this);
}
/**
 * Register a linguistic variable with the engine.
 * Any lingustic variable participating in fuzzy evaluations should be registered with the engine.
 * The same lingustic variable cannot be registered with different engines if labels are used.
 * @param function fuzzyEngine.LinguisticVariable to be registered with the engine.
 */
void FuzzyEngine::regist(LinguisticVariable * function)
{
	//Store the LV itself
	this->lvHash.insert(make_pair(function->getLVName(),function));

	//Provide access from LV to labels' weights hash
	function->setLabelWeightsHash(labelWeightsHash);
}

void FuzzyEngine::reset()
{
	//Reset fired rules
	flagRuleFired = false;
	std::map<std::string, LinguisticVariable*>::iterator it = lvHash.begin();
	while ( it != lvHash.end())
  {
      it->second->reset();
      ++it;
  }
	//Reset labels' weights changes
	it = labelWeightsHash.begin();
	while ( it != labelWeightsHash.end())
  {
      it->second->reset();
      ++it;
  }
}

FuzzyEngine::FuzzyEngine()
{
	engineState = UNDEFINED;
	flagRuleFired = false;

	addHedge(new HedgeNot());
	addHedge(new HedgeVery());
	addHedge(new HedgeSomewhat());

	controlHash.insert( std::make_pair("if", IF) );
	controlHash.insert( std::make_pair("then", THEN));
	controlHash.insert( std::make_pair("is", IS));
	controlHash.insert( std::make_pair("and", AND));
	controlHash.insert( std::make_pair("or", OR));
	controlHash.insert( std::make_pair("(", LEFTP));
	controlHash.insert( std::make_pair(")", RIGHTP));
	controlHash.insert( std::make_pair(" ", NOP));
	controlHash.insert( std::make_pair("rule", RULE));
	controlHash.insert( std::make_pair("weight", WEIGHT));
	controlHash.insert( std::make_pair("set", SET));

}

std::string FuzzyEngine::parseExpression(std::vector<std::string> tokens,FuzzyRule * rule)
			 //throw(RulesParsingException)
{

	//Conrol Word
	int controlWord = NOP;

	//Current state of the engine
	int engineState = LABEL;

	//Current subState
	int engineSubState = READY;

	//Current linguistic variable
	LinguisticVariable * lVariable = NULL;

	//Current hedge
	Hedge * hVariable = NULL;

	//Current membersip function by name
	std::string mVariable;

	//Storage variables
	double accumulatedResult = 0.0;
	std::string currentToken;

	//Flags
	bool flagAND = false;
	bool flagOR = false;

	//Nesting up counter - for block parsing mode
	int nestingUp = 0;

	//Hedges buffer
	std::stack <Hedge *> hedgesBuffer;

	//Labels stuff
	std::string thisRuleLabel;
	std::string changeRuleLabel;

	//Output string
	std::string out;

	//Process a rule

for (size_t i = 0; i < tokens.size(); ++i)
{
	//Reset control word
	controlWord = UNDEFINED;

	//Read next token
	currentToken = tokens[i];

	//Add to the output string
	out+=currentToken;

	//Check control words hastable
	std::map<std::string, int>::iterator temp = controlHash.find(currentToken);
	if(temp!=controlHash.end())
	{
	  controlWord = temp->second;
	}
	else
	{
		//Check LV hashtable
		std::map<std::string, LinguisticVariable*>::iterator temp = lvHash.find(currentToken);
		if(temp!=lvHash.end())
    {
      controlWord = LV;
      lVariable = temp->second;
    }
		else
		{
			//Check hedges
			std::map<std::string, Hedge*>::iterator temp = hedgesHash.find(currentToken);
			if(temp!=hedgesHash.end())
      {
        controlWord=HEDGE;
        hVariable = temp->second;
      }
		}
	}

	//Switch according to the state/subState
	if(controlWord!=NOP)
	{
	switch(engineState)
	{
	case LABEL:
		switch(engineSubState)
		{
//LABEL:READY --------------------------------------------------------------------------------------------------
		case READY:
			switch(controlWord)
			{
				case LV:
				case HEDGE:
					throw RulesParsingException("- A label cannot be the same as an LV or a hedge: "+out);
				case IF:
					engineState = EVALUATION;
					break;
				case SET:
					accumulatedResult = 1.0;
					engineState = EXECUTION;
					break;
				case UNDEFINED:
					thisRuleLabel = currentToken;
					engineSubState = STORE_LABEL;

					//Block parsing mode
					if(rule!=NULL)
						rule->setLabel(currentToken);

					break;
				default:
					throw RulesParsingException(" - A rule should start with a label of an 'if': "+out);
			}
			break;
//LABEL:STORE_LABEL --------------------------------------------------------------------------------------------
		case STORE_LABEL:
			switch(controlWord)
			{
				case IF:
					//Store label in the label's hash and create a copy of WEIGHT LV for that label
					if( labelWeightsHash.find(thisRuleLabel) == labelWeightsHash.end() )
						{
						//retrive WEIGHT LV

						std::map<std::string, LinguisticVariable*>::iterator it = lvHash.find("weight");
						if(it==lvHash.end())
						  throw RulesParsingException(" - WEIGHT LV is not registered but required for LABELS: "+out);

            LinguisticVariable * tempLV = (it->second);
						tempLV = tempLV->copy();
						tempLV->setLVName(thisRuleLabel);
						labelWeightsHash.insert( make_pair(thisRuleLabel,tempLV));
						}
					engineState = EVALUATION;
					engineSubState = READY;
					break;
				case SET:
					//Store label in the label's hash and create a copy of WEIGHT LV for that label
					if( labelWeightsHash.find(thisRuleLabel) == labelWeightsHash.end() )
						{
						//retrive WEIGHT LV
						std::map<std::string, LinguisticVariable*>::iterator it = lvHash.find("weight");
						if(it==lvHash.end())
						  throw RulesParsingException(" - WEIGHT LV is not registered but required for LABELS: "+out);

            LinguisticVariable * tempLV = (it->second);
						tempLV = tempLV->copy();
						tempLV->setLVName(thisRuleLabel);
						labelWeightsHash.insert( make_pair(thisRuleLabel,tempLV) );
						}
					accumulatedResult = 1.0;
					engineState = EXECUTION;
					engineSubState = READY;
					break;
				default:
					throw RulesParsingException(" - Incorrect LABEL: "+out);
			}
			break;
		}
		break;
	case EVALUATION:
		switch(engineSubState)
		{
//EVALUATION:READY ---------------------------------------------------------------------------------------------
		case READY:
			switch(controlWord)
			{
				case LV:
					engineSubState = LV_READ;
					break;
				case AND:
					if(!flagAND && !flagOR)
						flagAND = true;
					else
						throw RulesParsingException(" - Incorrect AND/OR operation"+out);
					break;
				case OR:
					if(!flagAND && !flagOR)
						flagOR = true;
					else
						throw RulesParsingException(" - Incorrect AND/OR operation"+out);
					break;
				case LEFTP:
					//Nesting
					//Block parsing mode
					if(rule!=NULL)	nestingUp++;
					//Rule evaluation mode
					else
					{
					nestingStack.push(StackElement(accumulatedResult,flagAND,flagOR));
					accumulatedResult = 0.0;
					flagAND = false;
					flagOR = false;
					}
					break;
				case RIGHTP:
					//Block parsing mode
					if(rule!=NULL)
						(rule->getLeftPartExpressions().end() - 1)->nestingDown++;
					//Rule evaluation mode
					else
					{
					//Check for hanging AND/OR operations
					if(flagAND || flagOR)
						throw RulesParsingException(" - Unmatched AND/OR operation: "+out);

					//Return from nesting
					StackElement & tempSE = nestingStack.top();
					nestingStack.pop();
					flagAND = tempSE.flagAND;
					flagOR = tempSE.flagOR;

					//Add to display string
					std::stringstream ssbuf;
					ssbuf << accumulatedResult;
					std::string s = ssbuf.str();
					out = out + "(" + s.substr(0,s.length() > 3 ? 4 : 3) + ") ";

					//A hedge cannot appear at this place
					//If both flagAND and flahOR are not set, keep the accumulatedResult
					if(flagAND)
						{
						flagAND = false;
						accumulatedResult = accumulatedResult > tempSE.accumulatedResult ?
							tempSE.accumulatedResult : accumulatedResult;
						}
					if(flagOR)
						{
						flagOR = false;
						accumulatedResult = accumulatedResult < tempSE.accumulatedResult ?
							tempSE.accumulatedResult : accumulatedResult;
						}
					}
					break;
				case THEN:
					engineState = EXECUTION;
					break;
				default:
					throw RulesParsingException(" - Incorrect operation: "+out);
			}
			break;
//EVALUATION:LV_READ -------------------------------------------------------------------------------------------
		case LV_READ:
			//the next item should be 'is' - everything else is an exception
			switch(controlWord)
			{
				case IS:
					engineSubState = IS_READ;
					break;
				default:
					throw RulesParsingException(" - only IS may be present at this place: "+out);
			}
			break;
//EVALUATION:IS_READ -------------------------------------------------------------------------------------------
		case IS_READ:
			//the next item may be a hedge or a membership function
			switch(controlWord)
			{
				case HEDGE:
					hedgesBuffer.push(hVariable);
					engineSubState = HEDGE_READ;
					break;
				case UNDEFINED:
					engineSubState = COMPLETE_EVALUATION;
					mVariable = currentToken;
					break;
				default:
					throw RulesParsingException(" - Incorrect operation after IS: "+out);

			}
			break;
//EVALUATION:HEDGE_READ ----------------------------------------------------------------------------------------
		case HEDGE_READ:
			//the next item can only be a membership function or another hedge
			switch(controlWord)
			{
				case UNDEFINED:
					engineSubState = COMPLETE_EVALUATION;
					mVariable = currentToken;
					break;
				case HEDGE:
					hedgesBuffer.push(hVariable);
					engineSubState = HEDGE_READ;
					break;
				default:
					throw RulesParsingException(" - Incorrect operation after HEDGE: "+out);
			}
			break;
//EVALUATION:EXCEPTION -----------------------------------------------------------------------------------------
		default:
			throw RulesParsingException(" - Error in EVALUATION state: "+out);
		}
//EVALUATION:COMPLETE_EVALUATION -------------------------------------------------------------------------------
		if(engineSubState==COMPLETE_EVALUATION)
		{
		//Block parsing mode
		if(rule!=NULL)
			{
			//Store hedges if needed
			std::vector<Hedge*> hVector;
			while(!hedgesBuffer.empty())
			{
			  hVector.push_back(hedgesBuffer.top());
			  hedgesBuffer.pop();
			}


			FuzzyExpression tempExpression(lVariable,mVariable,hVector,out);
			//Store flags
			tempExpression.flagAND=flagAND;
			tempExpression.flagOR=flagOR;
			flagOR=flagAND=false;
			tempExpression.nestingUp = nestingUp;
			nestingUp=0;
			//Reset text represenation
			out.clear();
			//Store the expression
			rule->getLeftPartExpressions().push_back(tempExpression);

			}
		else
		//Rule evaluation mode
			{
			double tempResult = 0.0;

			//Complete evaluation
			tempResult = (*lVariable).is(mVariable);
			//lVariable = null;

			if(tempResult == -1)
				throw RulesParsingException(" - Unable to perform fuzzy evaluation: "+out);

			//Apply hedge if needed
			while(!hedgesBuffer.empty())
			{
			  tempResult = hedgesBuffer.top()->hedgeIt(tempResult);
			  hedgesBuffer.pop();
			}


			//Check if doing AND or OR ---> !(AND||OR) = STORE
			if(!flagAND && !flagOR)
			{
				accumulatedResult = tempResult;
			}
			else
			{
				if(flagAND && flagOR)
					throw RulesParsingException(" - Incorrect AND/OR operation: "+out);
				if(flagAND)
					{
				flagAND = false;
				accumulatedResult = accumulatedResult > tempResult ? tempResult : accumulatedResult;
					}
				if(flagOR)
					{
					flagOR = false;
					accumulatedResult = accumulatedResult < tempResult ? tempResult : accumulatedResult;
					}
			}
			//Add to display string
			std::stringstream ssbuf;
      ssbuf << tempResult;
      std::string s = ssbuf.str();
			out = out + "(" + s.substr(0,s.length() > 3 ? 4 : 3) + ") ";
//      std::cout << out << "  "%.2lf°"!" << std::endl;
//      std::cout << out << "  "%.2lf°"!" << std::endl;
			}//end of mode switch

			//Switch subState
			engineSubState = READY;
		}
		break;
	case EXECUTION:
		switch(engineSubState)
		{

//EXECUTION: READY --------------------------------------------------------------------------------------------
		case READY:
			switch(controlWord)
			{
			case LV:
				engineSubState = LV_READ;
				break;
			//Nothing to do if an 'and' is found
			case AND:
				break;
			//Change a rule's weight
			case RULE:
				engineSubState = RULE_READ;
				break;
			//Everything else generates exception
			default:
				throw RulesParsingException(" - Incorrect operation after THEN: "+out);
			}
			break;
//EXECUTION: RULE_READ ----------------------------------------------------------------------------------------
		case RULE_READ:
			//The next item should be a label
			switch(controlWord)
			{
			case UNDEFINED:
				changeRuleLabel = currentToken;
				engineSubState = LABEL_READ;
				break;
			default:
				throw RulesParsingException(" - A LABEL should follow RULE: "+out);
			}
			break;
//EXECUTION: LABEL_READ ---------------------------------------------------------------------------------------
		case LABEL_READ:
			//The next item should be WEIGHT
			switch(controlWord)
			{
			case WEIGHT:
				engineSubState = LV_READ;
				break;
			default:
				throw RulesParsingException(" - An error after RULE LABEL (was 'weight' LV registered?): "+out);
			}
			break;
//EXECUTION: LV_READ ------------------------------------------------------------------------------------------
		case LV_READ:
			//The next item must be IS - anything else generates an exception
			switch(controlWord)
			{
			case IS:
				engineSubState = IS_READ;
				break;
			default:
				throw RulesParsingException(" - Only IS can be present at this place: "+out);
			}
			break;
//EXECUTION: IS_READ ------------------------------------------------------------------------------------------
		case IS_READ:
			//The next item can be a HEDGE or a membership function
			switch(controlWord)
			{
			case HEDGE:
				hedgesBuffer.push(hVariable);
				engineSubState = HEDGE_READ;
				break;
			case UNDEFINED:
				mVariable = currentToken;
				engineSubState = COMPLETE_EXECUTION;
				break;
			default:
				throw RulesParsingException(" - Incorrect sequence after IS: "+out);
			}
			break;
//EXECUTION: HEDGE_READ ----------------------------------------------------------------------------------------
		case HEDGE_READ:
			//The next item can be a membership function or another hedge
			switch(controlWord)
			{
			case HEDGE:
				hedgesBuffer.push(hVariable);
				engineSubState = HEDGE_READ;
				break;
			case UNDEFINED:
				mVariable = currentToken;
				engineSubState = COMPLETE_EXECUTION;
				break;
			default:
				throw RulesParsingException(" - An error in EXECUTION stage: "+out);

			}
			break;
		}//end of switch (EXECUTION)

//EXECUTION: COMPLETE_EXECUTION -------------------------------------------------------------------------------
		if(engineSubState ==COMPLETE_EXECUTION)
		{

		//Block parsing mode
		if(rule!=NULL)
		{
			//Store hedges if needed
			std::vector< Hedge* > hVector;
			while(!hedgesBuffer.empty())
			{
			  hVector.push_back(hedgesBuffer.top());
			  hedgesBuffer.pop();
			}


			//Check if this is a weight change operation
			if( ! changeRuleLabel.empty() )
			{
				//Ensure that thisRuleLabel is not equal to changeRuleLabel
				//if( ! thisRuleLabel.empty() && ! changeRuleLabel.empty() && thisRuleLabel.equals(changeRuleLabel))
				if ( thisRuleLabel == changeRuleLabel )
					throw RulesParsingException(" - A LABEL cannot be assigned to a RULE that changes that label's WEIGHT: "+out);
				//Fetch the label WEIGHT LV from the hash
				std::map<std::string, LinguisticVariable*>::iterator it = labelWeightsHash.find(changeRuleLabel);
				if(it == labelWeightsHash.end())
					throw RulesParsingException(" - Unable to change WEIGHT for LABEL "+changeRuleLabel+" the LABEL hasn't yet been encountered: "+out);
			}

			FuzzyExpression tempExpression(lVariable,mVariable,hVector,out);
			//Reset text represenation
			out.clear();
			//Store the expression
			rule->getRightPartExpressions().push_back(tempExpression);
		}
		else
		//Rule evaluation mode
		{
		//A temporary variable to store results of hedging / negating
		double tempResult = accumulatedResult;



			//If something fired
			if(accumulatedResult > 0.0)
			{
				//If this is a weight change operation
				if( ! changeRuleLabel.empty() )
				{
					//Ensure that thisRuleLabel is not equal to changeRuleLabel
					//if(thisRuleLabel!=null && changeRuleLabel!=null && thisRuleLabel.equals(changeRuleLabel))
					if ( thisRuleLabel == changeRuleLabel )
						throw RulesParsingException(" - A LABEL cannot be assigned to a RULE that changes that label's WEIGHT: "+out);
					//Fetch the label WEIGHT LV from the hash
					std::map<std::string, LinguisticVariable*>::iterator it = labelWeightsHash.find(changeRuleLabel);
				  if(it == labelWeightsHash.end())
						throw RulesParsingException(" - Unable to change WEIGHT for LABEL "+changeRuleLabel+" the LABEL hasn't yet been encountered: "+out);
				}

				//Apply hedge if needed
				while( ! hedgesBuffer.empty() )
				{
				  tempResult = (hedgesBuffer.top())->hedgeIt(tempResult);
				  hedgesBuffer.pop();
				}


				//Store result
//				std::cout << "thisRuleLabel = " << thisRuleLabel << " currentToken = " << currentToken
//				 << ", tempResult " << tempResult << std::endl;
				(*lVariable).set(thisRuleLabel, currentToken, tempResult);

				//Set fired flag
				flagRuleFired = true;

			}

			//Add to display string
			std::stringstream ssbuf;
      ssbuf << tempResult;
      std::string s = ssbuf.str();
			out = out + "(" + s.substr(0,s.length() > 3 ? 4 : 3) + ") ";

		}//end of mode switching

			//Switch engineSubState
			engineSubState = READY;

		}

		break;
	} //end if switch(engineState)
	} //end of if(controlWord!=NOP)

} //end of while

return out;
}

std::vector<std::string> FuzzyEngine::Tokenize(const std::string& str, const std::string& delimiters)
{
    std::vector<std::string> tokens;
    // Skip delimiters at beginning.
    std::string::size_type lastPos = str.find_first_not_of(delimiters, 0);
    // Find first "non-delimiter".
    std::string::size_type pos     = str.find_first_of(delimiters, lastPos);

    while (std::string::npos != pos || std::string::npos != lastPos)
    {
        // Found a token, add it to the vector.
        tokens.push_back(str.substr(lastPos, pos - lastPos));
        // Skip delimiters.  Note the "not_of"
        lastPos = str.find_first_not_of(delimiters, pos);
        // Find next "non-delimiter"
        pos = str.find_first_of(delimiters, lastPos);
    }
    return tokens;
}
