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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "slibc.h"

#define RUNTIME_CONSTRAINT_MSG_MAX 1024


void slibc_call_constraint_handler(const char *msg,
								   const char *func,
								   const char *file,
								   unsigned line,
								   errno_t error)
{

	/* In the worst case, the msg stored in buf is truncated.
	 */
	char buf[RUNTIME_CONSTRAINT_MSG_MAX];


	/* To be on the safe side
	 */
	if (!msg)
		msg = "(empty message)";
	if (!func)
		func = "(empty functionname)";
	if (!file)
		file = "(empty filename)";
			
	snprintf(buf, sizeof(buf), "The runtime-constraint violation was caused by the\
 following expression in %s:\n%s (in %s:%u)",
				 func, msg, file, line);	

	slibc_constraint_handler(buf, NULL, error);
}


