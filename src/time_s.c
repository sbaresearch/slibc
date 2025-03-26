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
#include <time.h>
#include <string.h>
#include <stdlib.h>

#include "slibc.h"

errno_t asctime_s(char *s, rsize_t maxsize, const struct tm *timeptr)
{
#define ASCTIME_S_CLEANUP								\
	do												\
	{													\
		if(s != NULL && maxsize > 0 && maxsize < RSIZE_MAX)	\
			s[0] = '\0';									\
	} while(0)

	_CONSTRAINT_VIOLATION_CLEANUP_IF(\
		(!s || !timeptr || maxsize < 26 || maxsize > RSIZE_MAX 
		 || timeptr->tm_year < 0 || timeptr->tm_year > 9999),
		ASCTIME_S_CLEANUP,
		EINVAL, EINVAL);

	
	char *ret = asctime_r(timeptr, s);
	if (ret == NULL)
	{
		// not sure if this is possible at all 
		// but let's be on the safe side.
		return -1;
	}
	else
		return 0;
}

errno_t ctime_s(char *s, rsize_t maxsize, const time_t *timer)
{
	struct tm date;
	localtime_s(timer, &date);
	return asctime_s(s, maxsize, &date);
}

struct tm *gmtime_s(const time_t * restrict timer, struct tm * restrict result)
{
	_CONSTRAINT_VIOLATION_IF ( (!timer || !result),
							   EINVAL,
							   NULL);

	return gmtime_r(timer, result);
}

struct tm *localtime_s(const time_t * restrict timer, struct tm * restrict result)
{
	_CONSTRAINT_VIOLATION_IF ( (!timer || !result),
							   EINVAL,
							   NULL);

	return localtime_r(timer, result);
}
