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
