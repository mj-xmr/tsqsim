//Fuzzy engine for C++ example
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
#include <cstdio>

#include "FuzzyController.hpp"

// returns 0 if user cancelled input
double getVar( const char * msg, double min = 0, double max = 0 )
{
  double var = 0;
  std::stringstream ssbuf;
  std::string strIn;

  ssbuf << msg << " ( " << min << ", " << max << " ) :";
  std::string strMsg(ssbuf.str());
  ssbuf.clear();
  bool bVarOK = false;
  do
  {
    std::cout << strMsg << std::endl;
    std::cin >> strIn;
    if ( strIn == "q" || strIn == "Q" ) return 0;
    ssbuf.str(strIn);
    ssbuf >> var;
    ssbuf.clear();

    // fail conditions
    if ( ! var || // you entered 0 or chars, tehehe
        ( var <= min ) ||
        ( max > 0 && var >= max )
       )
    {
      std::cout << "You bugger !!!" << std::endl;
    }
    else
    {
      bVarOK = true;
    }
  } while ( ! bVarOK );

  return var;
}

// returns false if user finished calculating
bool calculate()
{
  double var = 0;

  var = getVar("Enter radial distance from target at 0", -180, 180);
  if ( var == 0 ) return false;
  double pos = var;

  var = getVar("Enter your velocity as a percent of orbital velocity", 0 , 100);
  if ( var == 0 ) return false;
  double vel = var / (double) 100;

  var = getVar("Enter number of iterations", 0, 1000);
  if ( var == 0 ) return false;
  int iterations = var;


	  FuzzyController fuzzyController;
	  fuzzyController.SetInputPosition( pos );
	  fuzzyController.SetInputVelocity( vel );

	  printf("Legend:\noutput time == ot,\tposition (input) == p,\tdist passed == dp,\nnew dist == nd,\t\ttotal dist == td\n\n");

	  double d = 0;
	  for (int i = 0; i < iterations; ++i)
	  {
		  fuzzyController.Evaluate();

		  double result = fuzzyController.GetOutputTime();

		  // post-process the data (or "amplify" in control engineering jargon)
		  double distPassed = result * vel * 180;

		  d += distPassed;
		  double newDist = (pos) - distPassed; // a variable handy for diplaying only

		  printf("ot = %.3f,\tp = %.3f,\tdp = %.3f,\tnd = %.3f,\ttd = %.3f\n",
			 result,pos, distPassed, newDist, d);

		  pos = newDist;

		  // disturbances - you may add them and see what happens
	//				if ( i == 3 )
	//					pos -= 7;
	//
	//				if ( i == 5 )
	//					pos -= 1;

		  // Feedback to controller
		  fuzzyController.SetInputPosition(pos);
		  // reset the state
		  fuzzyController.Reset();
	  }

  return true;
}

int main( int argc, char * argv[] )
{
  std::cout << "Welcome to an example application using C++ port of FuzzyEngine (FuzzyEngine++)\nby Szymon \"Enjo\" Ender. "
  << "The original FuzzyEngine was written in Java \nby Professor Edward Sazonov from Clarkson University.\n"
  << "Visit http://people.clarkson.edu/~esazonov/FuzzyEngine.htm \n"
  << "and http://sf.net/projects/fuzzyengine\n"
  << "for details and a nicer Java example.\n"
  << "Bear in mind that the FuzzyEngine and FuzzyEngine++ are licensed under GNU GPL,\n"
  << "therefore you CAN NOT link this library with your closed source application!\n";

  try
  {
    do
    {
      std::cout << "\nEnter q or Q anytime to quit the application.\n\n";
    } while ( calculate() );
  }
  catch (std::exception & ex)
  {
    std::cout << "Exception caught:\n" << ex.what() << std::endl;
  }

  std::cout << "Bye" << std::endl;
  return 0;
}
