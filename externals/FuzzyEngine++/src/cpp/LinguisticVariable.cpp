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

#include <cmath>
#include "../include/FuzzyEngine++/LinguisticVariable.hpp"


void LinguisticVariable::add(MembershipFunction mFunction)
{
	std::vector <double> range = mFunction.getRange();
	storage.insert( make_pair(mFunction.getName(), mFunction) );

	//Check if there should be a change in min and max support values
	if(range[0]<minSupport)	minSupport=range[0];
	if(range[3]>maxSupport)	maxSupport=range[3];
}

void LinguisticVariable::add(std::string name,double start, double left_top, double right_top, double finish)
{
	std::vector <double> range;
	range.push_back(start);
	range.push_back(left_top);
	range.push_back(right_top);
	range.push_back(finish);

	MembershipFunction temp(name,range);
	storage.insert(make_pair(name,temp));

	//Check if there should be a change in min and max support values
	if(start<minSupport)	minSupport = start;
	if(finish>maxSupport)	maxSupport = finish;
}

LinguisticVariable * LinguisticVariable::copy()
{
	//Create new LV
	LinguisticVariable * tempLV = new LinguisticVariable(this->getLVName());


	//Copy membership functions
	std::map<std::string, MembershipFunction>::iterator it = storage.begin();
	while ( it != storage.end() )
	{
	  tempLV->add(it->second);
	  ++it;
	}

	//Copy input value
	tempLV->setInputValue(input_value);

	return tempLV;
}

double LinguisticVariable::defuzzify()// throw(NoRulesFiredException)
{
	//Number of rules fired
	int fired = for_defuzzification.size();

	if(fired == 0)
		{
			throw NoRulesFiredException("No rules were fired for "+this->thisLVname);
		}

	//min and max X (support) values are already calculated in minSupport/maxSupport
	double step = fabs((maxSupport-minSupport)/(double)100);

	//Find sum of scaled functions
	std::vector <double> scaled;
	std::vector <double> sum (100);

	//for(int i=0; i<(fired-1); i+=3)
	for(int i=0; i<(fired); ++i)
	{
		scaled = this->getMembershipFunctionByName(for_defuzzification[i].name)
						.plot(minSupport,maxSupport,100);

		//Scale and change weight if needed
		double scale = for_defuzzification[i].value;
		double weight = 1.0;

		std::string label = for_defuzzification[i].label;
		if( ! label.empty() )
			{
			//Look-up label weight in hash
			std::map<std::string, LinguisticVariable*>::iterator it = labelWeightsHash.find(label);

			//Catch exceptions if no weight change happened
			try{
				if( it != labelWeightsHash.end() )
				  weight = it->second->defuzzify();
				}
			catch(NoRulesFiredException & e)
				{
					weight=1.0;
				}
			}

		//Add to the sum
		for(int j=0; j<100; j++)	sum[j]+=scaled[j]*scale*weight;
	}

	//Find centroid
	double nominator = 0.0;
	double denominator = 0.0;

	for(int i=0; i<100; i++)
	{
		nominator+=(minSupport+step*i)*sum[i];
		denominator+=sum[i];
	}

	return nominator/denominator;
}

std::string LinguisticVariable::getLVName()
{
	return thisLVname;
}

MembershipFunction LinguisticVariable::getMembershipFunctionByName(std::string name)
{
  std::map<std::string, MembershipFunction>::const_iterator it = storage.find(name);
  if ( it == storage.end())
  {
    throw RulesParsingException("No linguistic variable found called '" + name + "'");
  }
	return (it->second); // FIXME: Faulty! What if find returns storage.end() ?
}

double LinguisticVariable::is(std::string name)
{
	MembershipFunction m = this->getMembershipFunctionByName(name);

//	if(m!=null)		return m.fuzzify(input_value);
//	else			return -1;

  return m.fuzzify(input_value);
}

LinguisticVariable::LinguisticVariable(std::string name)
{
	this->thisLVname = name;
	minSupport = maxSupport = 0;
}

void LinguisticVariable::reset()
{
	//Remove fired rules
	for_defuzzification.clear();

}

void LinguisticVariable::setInputValue(double value)
{
	this->input_value = value;
}

void LinguisticVariable::setLabelWeightsHash(std::map<std::string, LinguisticVariable*> hash)
{
	labelWeightsHash = hash;
}

void LinguisticVariable::set(std::string label, std::string name, double value)// throw(RulesParsingException)
{
  ForDefuzzification fdef;
	//Add label, name and value to the 'for_defuzzyfication' vector
	fdef.label = label;

	//Check that this name is a correct name for a MF
	//if(getMembershipFunctionByName(name)!=null)		for_defuzzification.addElement(name);
//	else	throw RulesParsingException("Wrong name of a membership function");
	fdef.name = name;
	fdef.value = value;

//	for_defuzzification.addElement(new Double(value));
  for_defuzzification.push_back( fdef );
}

void LinguisticVariable::setLVName(std::string name)
{
	thisLVname = name;
}
