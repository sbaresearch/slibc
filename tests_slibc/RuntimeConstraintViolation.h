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
