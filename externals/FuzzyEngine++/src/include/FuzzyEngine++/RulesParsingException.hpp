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

#ifndef RULESPARSINGEXCEPTION_H_INCLUDED
#define RULESPARSINGEXCEPTION_H_INCLUDED

#include <stdexcept>
#include <iosfwd>
#include "globals.hpp"

/**
 * This exception is thrown if an error occurs during parsing a fuzzy rule
 * Exception.getMessage() will return cause of the error
 */
class DLLINTERFACE RulesParsingException : public std::runtime_error
{
  public:
  /**
 * Constructor
 * @param string message
 */
    RulesParsingException(const std::string& message);

};

#endif // RULESPARSINGEXCEPTION_H_INCLUDED
