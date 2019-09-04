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
//Request the glibc-spcific strerror_r function
#ifndef _GNU_SOURCE
# define _GNU_SOURCE
#endif
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/file.h>

#include "slibc.h"
#include <unistd.h>

// external declaration
char *
gnu_strtok_s(char * restrict s1,
			 rsize_t * restrict s1max,
			 const char * restrict s2,
			 char ** restrict ptr);

// ** Implementation **



size_t strnlen_s(const char *s, size_t maxsize)
{
	if (!s) return 0;

	return strnlen(s, maxsize);
}


errno_t strcpy_s(char * restrict s1, rsize_t s1max, const char * restrict s2)
{
	_CONSTRAINT_VIOLATION_IF((s1 == NULL), EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_IF((s1max == 0), EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_IF((s1max > RSIZE_MAX), EINVAL, EINVAL);

	rsize_t s2_len = 0;
	_CONSTRAINT_VIOLATION_CLEANUP_IF(s2 == NULL,
									 s1[0] = 0, 
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF((s1max <= (s2_len=strnlen_s(s2, s1max)) ),
									 s1[0] = 0, EINVAL, EINVAL);

	_CONSTRAINT_VIOLATION_CLEANUP_IF(\
		REGIONS_OVERLAP_CHECK(s1, s1max, s2, s2_len+1),
		s1[0] = 0, 
		EINVAL, EINVAL);


	strncpy(s1, s2, s1max-1);
	s1[s1max-1] = '\0';

	// on success
	return 0;
}


errno_t strncpy_s(char * restrict s1, rsize_t s1max, const char * restrict s2, rsize_t n)
{
	rsize_t m;

	_CONSTRAINT_VIOLATION_IF((s1 == NULL), 
							 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_IF((s1max == 0), 
							 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_IF((s1max > RSIZE_MAX),
							 EINVAL, EINVAL);

	_CONSTRAINT_VIOLATION_CLEANUP_IF(s2 == NULL,
									 s1[0] = 0, 
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF(n > RSIZE_MAX,
									 s1[0] = 0, 
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF((n >= s1max && s1max <= strnlen_s(s2, s1max)),
									 s1[0] = 0, 
									 EINVAL, EINVAL);

	// If s2 < n, we are going to read strlen(s2) + its terminating null byte
	// Otherwise, we are going to read exactly n bytes
	rsize_t s2_size = MIN(strnlen_s(s2, n) + 1, n);
	_CONSTRAINT_VIOLATION_CLEANUP_IF(\
		REGIONS_OVERLAP_CHECK(s1, s1max, s2, s2_size), 
		s1[0] = 0, 
		EINVAL, EINVAL);
	

	m = MIN(n, s1max-1);
	strncpy(s1, s2, m);
	s1[MIN(n, s1max-1)] = '\0';

	// on success
	return 0;
}



errno_t strcat_s(char * restrict s1,
				 rsize_t s1max,
				 const char * restrict s2)
{
	_CONSTRAINT_VIOLATION_IF((s1 == NULL), 
							 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_IF((s1max == 0), 
							 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_IF((s1max > RSIZE_MAX),
							 EINVAL, EINVAL);

	size_t s1_len = 0;
	rsize_t s2_len = 0;
	size_t m = s1max - (s1_len=strnlen_s(s1, s1max));

	_CONSTRAINT_VIOLATION_CLEANUP_IF(s2 == NULL,
									 s1[0] = 0, 
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF(m == 0,
									 s1[0] = 0, 
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF((m <= (s2_len=strnlen_s(s2, m))), 
									 s1[0] = 0, 
									 EINVAL, EINVAL);

	_CONSTRAINT_VIOLATION_CLEANUP_IF(\
		REGIONS_OVERLAP_CHECK(s1+s1_len, m, s2, s2_len+1), 
		s1[0] = 0, 
		EINVAL, EINVAL);


	strncat(s1, s2, m-1);
	// should not be necessary
	s1[s1max-1] = '\0';
	
	return 0;
}


errno_t strncat_s(char * restrict s1,
				  rsize_t s1max,
				  const char * restrict s2,
				  rsize_t n)
{
	_CONSTRAINT_VIOLATION_IF((s1 == NULL), 
							 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_IF((s1max == 0), 
							 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_IF((s1max > RSIZE_MAX),
							 EINVAL, EINVAL);

	size_t s1_len = 0;
	size_t m = s1max - (s1_len=strnlen_s(s1, s1max));

	_CONSTRAINT_VIOLATION_CLEANUP_IF(s2 == NULL,
									 s1[0] = 0, 
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF(n > RSIZE_MAX || m == 0,
									 s1[0] = 0, 
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF((n >= m && m <= strnlen_s(s2, m)), 
									 s1[0] = 0, 
									 EINVAL, EINVAL);

	// If s2 < n, we are going to read strlen(s2) + its terminating null byte
	// Otherwise, we are going to read exactly n bytes
	rsize_t s2_size = MIN(strnlen_s(s2, n) + 1, n);
	_CONSTRAINT_VIOLATION_CLEANUP_IF(\
		REGIONS_OVERLAP_CHECK(s1+s1_len, m, s2, s2_size), 
		s1[0] = 0, 
		EINVAL, EINVAL);
	

	strncat(s1, s2, n);
	// should not be necessary
	s1[s1max-1] = '\0';
	
	return 0;
}

errno_t memcpy_s(void * restrict s1, rsize_t s1max,
				 const void * restrict s2, rsize_t n)
{
#define MEMCPY_S_CLEANUP						  \
	do											  \
	{											  \
		if(s1 != NULL && s1max <= RSIZE_MAX)	  \
			memset(s1, 0, s1max);				  \
	} while (0)

	_CONSTRAINT_VIOLATION_CLEANUP_IF(s1 == NULL,
									 MEMCPY_S_CLEANUP, 
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF(s2 == NULL,
									 MEMCPY_S_CLEANUP,
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF(s1max > RSIZE_MAX, 
									 MEMCPY_S_CLEANUP,
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF(n > RSIZE_MAX, 
									 MEMCPY_S_CLEANUP,
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF(n > s1max, 
									 MEMCPY_S_CLEANUP,
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF(REGIONS_OVERLAP_CHECK(s1, s1max, s2, n), 
									 MEMCPY_S_CLEANUP,
									 EINVAL, EINVAL);

	void * res = memcpy(s1, s2, n);
	if (res != (void *) NULL)
		return 0;
	return -1;
}

errno_t memmove_s(void *s1, rsize_t s1max,
				  const void *s2, rsize_t n)
{
#define MEMMOVE_S_CLEANUP						\
	do											\
	{											\
		if(s1 != NULL && s1max <= RSIZE_MAX)	\
			memset(s1, 0, s1max);				\
	} while(0)

	_CONSTRAINT_VIOLATION_CLEANUP_IF(s1 == NULL,
									 MEMMOVE_S_CLEANUP, 
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF(s2 == NULL,
									 MEMMOVE_S_CLEANUP,
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF(s1max > RSIZE_MAX, 
									 MEMMOVE_S_CLEANUP,
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF(n > RSIZE_MAX, 
									 MEMMOVE_S_CLEANUP,
									 EINVAL, EINVAL);
	_CONSTRAINT_VIOLATION_CLEANUP_IF(n > s1max, 
									 MEMMOVE_S_CLEANUP,
									 EINVAL, EINVAL);

	
	(void) memmove(s1,s2,n);

	return 0;
}

char *strtok_s(char * restrict s1,
			   rsize_t * restrict s1max,
			   const char * restrict s2,
			   char ** restrict ptr)
{
	_CONSTRAINT_VIOLATION_IF(\
		(!s1max || !s2 || !ptr || (!s1 && !*ptr) || *s1max > RSIZE_MAX),
		EINVAL,
		NULL);

	return gnu_strtok_s(s1, s1max, s2, ptr);
}

errno_t strerror_s(char *s, rsize_t maxsize,
				   errno_t errnum)
{
	_CONSTRAINT_VIOLATION_IF((!s || maxsize > RSIZE_MAX || maxsize == 0),
							 EINVAL,
							 EINVAL);

#ifdef SLIBC_MT
	// this version is thread-safe

	// we use the GNU strerror_r instead of the XSI-compliant strerror_r
	// the XSI-compliant strerror_r returns an error if the buffer
	// is not big enough. For our purposed, truncate behavior is better.
	char *err = strerror_r(errnum, s, maxsize);
	if (err != s)
	{
		// in that case strerror_r returned a static string
		// copy it into our buffer
		strncpy_s(s, maxsize, err, maxsize-1);

		// was the message truncated?
		if (strlen(err) > maxsize-1)
		{
			// truncation happened.
			if (maxsize > 3)
				s[maxsize-2] = s[maxsize-3] = s[maxsize-4] = '.';

			return -1;
		}
		return 0;
	}
	else
	{
		// the result was already copied into s

		if (strlen(s) == maxsize-1)
		{
			// the error string takes up all of the available space
			// we do not know whether the string was truncated.
			// find that out
			char *tmp = (char*) malloc(maxsize + 1);
			// we try with one additional byte
			char *ret = strerror_r(errnum, tmp, maxsize+1);
			if (strlen(ret) > strlen(s))
			{
				// truncation happened
				if (maxsize > 3)
					s[maxsize-2] = s[maxsize-3] = s[maxsize-4] = '.';	
				free(tmp);
				return -1;
			}
			free(tmp);
			return 0;
		}
		return 0;
	}
#else
	// not thread-safe, but simpler
	char * ch = strerror(errnum);
	strcpy_s(s, maxsize, ch);


	if(strlen(ch) < maxsize)
	{
		strncpy(s, ch, maxsize-1);
		s[maxsize-1] = '\0';
		return 0;
	} else {
		strncpy(s, ch, maxsize-1);
		if(maxsize > 3)
		{
			rsize_t i;
			for(i = maxsize -4; i < maxsize-1; i++)
				s[i] = '.';
		}
		s[maxsize-1] = '\0';
		return -1;
	}
#endif
}

size_t strerrorlen_s(errno_t errnum)
{
	char * ch = strerror(errnum);
	return strlen(ch);
}

errno_t memset_s(void *dest, rsize_t destsz, int ch, rsize_t count) {
    if (dest == NULL) return EINVAL;
    if (destsz > RSIZE_MAX) return EINVAL;
    if (count > destsz) return EINVAL;

    volatile unsigned char *p = (volatile unsigned char*)dest;
    while (destsz-- && count--) {
        *p++ = ch;
    }

    return 0;
}
