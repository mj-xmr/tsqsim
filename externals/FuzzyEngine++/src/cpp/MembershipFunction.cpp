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

#include "../include/FuzzyEngine++/MembershipFunction.hpp"


double MembershipFunction::fuzzify(double X)
{
	//Check if input value is in range, if not, return 0
	if(X<range[0] || X>range[3])	return 0;

	//Determine which of 3 /-\ slopes works
	//For middle part, return 1

	if(X>=range[1] && X<=range[2])	return 1;

	if(X>=range[0] && X<range[1])	return	(X-range[0])/(double)(range[1]-range[0]);

	if(X>range[2] && X<=range[3])	return (range[3]-X)/(double)(range[3]-range[2]);

	return 0;
}
/**
 * Return name of this membership function.
 * @return java.lang.std::string
 */
std::string MembershipFunction::getName()
{
	return name;
}
/**
 * Return 4 points of the trapeziod function.
 * @return double[]
 */
std::vector<double> MembershipFunction::getRange()
{
	return range;
}
/**
 * Constructor
 */
MembershipFunction::MembershipFunction(std::string name_in, std::vector<double> range_in)
{
	this->name = name_in;
	this->range = range_in;
}
/**
 * Return an array with discrete representation of the function.
 * @param from Left X-axis value.
 * @param to Right X-axis value.
 * @param size Number of discrete steps.
 * @return double[] Double array with size "size".
 */
std::vector<double> MembershipFunction::plot(double from, double to, int size)
{
	double increment = fabs((to-from)/(double)size);

	std::vector<double> temp(size);

	for(int i=0; i<size; i++)
		temp[i]=this->fuzzify(from+increment*i);

	return temp;
}
