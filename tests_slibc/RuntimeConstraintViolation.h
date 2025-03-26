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
#ifndef RUNTIMECONSTRAINTVIOLATION_H
#define RUNTIMECONSTRAINTVIOLATION_H


#include <iostream>
#include <sstream>
#include <exception>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// temporary hack
#include "../src/slibc.h"

// this is a bit out of date. currently, we do not fill the struct
// ConstraintHandlerDetails any longer
class RuntimeConstraintViolation : public std::exception
{
public:
	RuntimeConstraintViolation(const std::string &expr = "")
		: expr(expr), line(0) {}

	RuntimeConstraintViolation(const std::string &expr,
							   const ConstraintHandlerDetails &d)
		: expr(expr), function(d.function), file(d.file), line(d.line) {}

	virtual ~RuntimeConstraintViolation() throw () {}
	virtual const char * what() const throw();

private:
	std::string expr;
	std::string function;
	std::string file;
	unsigned line;

	mutable std::string msg;
};

void cpp_constraint_handler_s(const char * restrict msg,
				void * restrict ptr,
				errno_t error);

#endif
