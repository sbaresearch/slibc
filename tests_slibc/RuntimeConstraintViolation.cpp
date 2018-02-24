/* Copyright (C) 2011-2012 SBA Research gGmbh

   This file is part of the Slibc Library.

   The Slibc Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The Slibc library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the Slibc Library; if not, see
   <http://www.gnu.org/licenses/>.  
*/
#include <iostream>
#include <sstream>
#include <exception>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "RuntimeConstraintViolation.h"

using namespace std;

const char* RuntimeConstraintViolation::what() const throw()
{
	ostringstream out;
	if (! expr.empty())
		out << expr;
	else
		out << "Runtime Constraint Violation";

	if (! function.empty())
		out << " in function '" << function << "', ";
	if (! file.empty())
		out << "file '" << file << "' ";
	if (line)
		out << " at line " << line;

	msg = out.str();
	return msg.c_str();
}

// For this function to work correctly, it is important
// to have slibc compiled as C++ code or use the compiler switch
// -fexceptions when compiling C code. Otherwise, the 
// thrown C++ exception travels up the stack through C 
// code which is a non supported configuration. (although 
// it seems to work on some systems)
void cpp_constraint_handler_s(const char * restrict msg,
							  void * restrict ptr,
							  errno_t error)
{
	if (!msg)
		msg = "";

	throw RuntimeConstraintViolation(msg);
}
