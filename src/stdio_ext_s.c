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
