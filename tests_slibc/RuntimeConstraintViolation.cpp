/* Copyright (C) 2011-2012 SBA Research gGmbh

   This file is part of the Slibc Library.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
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
