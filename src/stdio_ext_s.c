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
#include "slibc.h"
#include <limits.h>

static char slibc_tmp_dir[PATH_MAX] = "/tmp/";
#ifdef SLIBC_MT
static pthread_mutex_t slibc_tmp_dir_m = PTHREAD_MUTEX_INITIALIZER;
#endif



errno_t slibc_set_tmp_dir(const char *tmp_dir)
{
	// we copy to the local variable first
	char local_tmp_dir[PATH_MAX];

	_CONSTRAINT_VIOLATION_IF( (! tmp_dir),
							  EINVAL, EINVAL);

	if (strcpy_s(local_tmp_dir, sizeof(local_tmp_dir), tmp_dir))
		return -1;

	// make sure that the dirname ends in /
	size_t len = strlen(local_tmp_dir);
	if (local_tmp_dir[len-1] != '/')
	{
		if (strcat_s(local_tmp_dir, sizeof(local_tmp_dir), "/"))
			return -1;
	}

	SLIBC_MUTEX_LOCK(&slibc_tmp_dir_m);
	// we know this works
	strcpy(slibc_tmp_dir, local_tmp_dir);
	SLIBC_MUTEX_UNLOCK(&slibc_tmp_dir_m);

	return 0;
}


errno_t slibc_get_tmp_dir(char *buf, rsize_t buf_size)
{
#define SLIBC_GET_TMP_DIR_CLEANUP				\
	do											\
	{											\
		if (buf && buf_size > 0)				\
			buf[0] = '\0';						\
	} while(0)

	_CONSTRAINT_VIOLATION_CLEANUP_IF(\
		(! buf || buf_size == 0 || buf_size > RSIZE_MAX),
		SLIBC_GET_TMP_DIR_CLEANUP,
		EINVAL, EINVAL);


	SLIBC_MUTEX_LOCK(&slibc_tmp_dir_m);
	if (strlen(slibc_tmp_dir) < buf_size)
	{
		strcpy(buf, slibc_tmp_dir);
		SLIBC_MUTEX_UNLOCK(&slibc_tmp_dir_m);
		return 0;
	}
	else
	{
		SLIBC_MUTEX_UNLOCK(&slibc_tmp_dir_m);

		buf[0] = '\0';

		_CONSTRAINT_VIOLATION("Target buf not big enough", EINVAL, EINVAL);
	}
}


errno_t mktemp_s(char *temp, size_t sizeInChars)
{
	unsigned int i = 0;
	unsigned int x = 0;
	int xstart = 0;

	_CONSTRAINT_VIOLATION_IF( (!temp),
							  EINVAL,
							  EINVAL);

	for(i = 0; i < strlen(temp); i++)
	{
		if(temp[i] == 'X')
		{
			x++;
			xstart = 1;
		}
		else if (xstart)
		{
			temp[0] = '\0';

			_CONSTRAINT_VIOLATION("temp must containt 6 consecutive X characters",
								  EINVAL, EINVAL);
		}
	}

	_CONSTRAINT_VIOLATION_CLEANUP_IF( \
		(x > sizeInChars || strlen(temp) > sizeInChars || x != 6),
		temp[0] = '\0',
		EINVAL,
		EINVAL);

	char * res = mktemp(temp);

	if(res != (char *) NULL)
		return 0;
	return -1;
}


errno_t mkstemp_s(char *temp, int *fd, size_t sizeInChars)
{
	unsigned int i = 0;
	unsigned int x = 0;
	int xstart = 0;

	_CONSTRAINT_VIOLATION_IF( (!temp),
							  EINVAL,
							  EINVAL);

	for(i = 0; i < strlen(temp); i++)
	{
		if(temp[i] == 'X')
		{
			x++;
			xstart = 1;
		}
		else if (xstart)
		{
			temp[0] = '\0';

			_CONSTRAINT_VIOLATION("temp must containt 6 consecutive X characters",
								  EINVAL, EINVAL);
		}
	}

	_CONSTRAINT_VIOLATION_CLEANUP_IF( \
		(x > sizeInChars || strlen(temp) > sizeInChars || x != 6),
		temp[0] = '\0',
		EINVAL,
		EINVAL);

	*fd = mkstemp(temp);

	if(*fd != -1)
		return 0;
	return -1;
}
