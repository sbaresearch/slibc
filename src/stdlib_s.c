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
#include "slibc/stdlib.h"
#include "slibc.h"
#include <limits.h>
#include <stdlib.h>
#include <string.h>

// external declarations

// Helperfunction for qsort, adapted from the original qsort implementation of the glibc
errno_t gnu_qsort_s(void *base, rsize_t nmemb, rsize_t size,
					int (*compar)(const void *x, const void *y, 
								  void *context),
					void *context);

//Helperfunction for bsearch_s adapted from the original bsearch function of the glibc
void *
gnu_bsearch_s (const void *key, const void *base, rsize_t nmemb, rsize_t size,
			   int (*compar) (const void *, const void *, void *context),
				void *context);


// ****************** internal **************************
/// Pointer to the current constraint handler.
/// It is a thread-local variable.
__thread constraint_handler_t slibc_constraint_handler = &abort_handler_s;


// ** Implementation ** //


constraint_handler_t set_constraint_handler_s(constraint_handler_t handler)
{
	constraint_handler_t tmp;
	tmp = slibc_constraint_handler;

	if (! handler)
	{
		// set it back to our default handler
		slibc_constraint_handler = &abort_handler_s;
	}
	else
		slibc_constraint_handler = handler;

	return tmp;
}


void abort_handler_s(const char * restrict msg,
					 void * restrict ptr,
					 errno_t error)
{	
	fprintf(stderr, "abort_handler_s was called in response to a runtime-constraint violation.\n\n");
	if (msg)
		fprintf(stderr, "%s\n", msg);
	fprintf(stderr, "\n\nNote to end users: This program was terminated as a result\
			of a bug present in the software. Please reach out to your	\
			software's vendor to get more help.\n");

	fflush(stderr);
	abort();
}


void ignore_handler_s(const char * restrict msg,
					  void * restrict ptr,
					  errno_t error)
{	
}


errno_t getenv_s(size_t * restrict len,
				 char * restrict value, rsize_t maxsize,
				 const char * restrict name)
{
#define GETENV_S_CLEANUP						\
	do {										\
		if(len != (size_t *) NULL)				\
		{										\
			*len = 0;							\
		}										\
	} while(0)

	_CONSTRAINT_VIOLATION_CLEANUP_IF (\
		(!name || maxsize == 0 || maxsize > RSIZE_MAX || (maxsize != 0 && value == (char *) NULL)),
		GETENV_S_CLEANUP,
		EINVAL, EINVAL);


	// In the GNU C library getenv is a reentrant function
	char * result = getenv(name);

	if (! result)
	{
		if(len != (size_t *) NULL)
			*len = 0;
		if(maxsize > 0)
			value[0] = '\0';

		return EINVAL;
	}

	size_t result_len = strlen(result);
	if(len != (size_t *) NULL)
		*len = result_len;
	if(result_len < maxsize)
	{
		strcpy(value,result);
		return 0;
	}
	else
	{
		// the standard does not explicitly say that.
		value[0] = '\0';
		return EINVAL;
	}
}

errno_t qsort_s(void *base, rsize_t nmemb, rsize_t size, 
				int (*compar) (const void *x, const void *y,
							   void *context),
				void *context)
{
	_CONSTRAINT_VIOLATION_IF ((nmemb > RSIZE_MAX || size > RSIZE_MAX),
							 EINVAL,
							 EINVAL);

	_CONSTRAINT_VIOLATION_IF ((nmemb != 0 && (base == NULL || compar == NULL)),
							  EINVAL, EINVAL);

	return gnu_qsort_s(base, nmemb, size, compar, context);
}


void *bsearch_s (const void *key, const void *base, rsize_t nmemb, rsize_t size,
				 int (*compar) (const void *, const void *, void *context),
				 void *context)
{
	_CONSTRAINT_VIOLATION_IF ( (nmemb > RSIZE_MAX || size > RSIZE_MAX),
							   EINVAL,
							   NULL);

	_CONSTRAINT_VIOLATION_IF ( (nmemb != 0 && (!key || !base || !compar)),
							   EINVAL,
							   NULL);

	return gnu_bsearch_s(key, base, nmemb, size, compar, context);
}
