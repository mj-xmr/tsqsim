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
#ifndef MEMBERSHIPFUNCTION_H_INCLUDED
#define MEMBERSHIPFUNCTION_H_INCLUDED

#include <string>
#include <vector>
#include "globals.hpp"

/**
 * Class for fuzzy membership functions.
 */

class DLLINTERFACE MembershipFunction
{

public:
/**
 * Fuzzify a value.
 * @param X Input value.
 * @return Result of fuzzification.
 */
double  fuzzify(double X);
/**
 * Return name of this membership function.
 * @return java.lang.std::string
 */
std::string getName();
/**
 * Return 4 points of the trapeziod function.
 * @return double[]
 */
std::vector<double> getRange();
/**
 * Constructor
 */
MembershipFunction(std::string name_in, std::vector<double> range_in);
/**
 * Return an array with discrete representation of the function.
 * @param from Left X-axis value.
 * @param to Right X-axis value.
 * @param size Number of discrete steps.
 * @return double[] Double array with size "size".
 */
std::vector<double> plot(double from, double to, int size);

private:
	std::string name;
	std::vector<double> range;
};


#endif // MEMBERSHIPFUNCTION_H_INCLUDED
