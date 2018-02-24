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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <printf.h>


#define FORMAT_STR_CHECK(format) \
	(format == NULL || format_str_has_n_spec(format))


////////////////////////////////////////////////////////////////////////////////
///	  Checks that the supplied string arguments are
///		  different from Null and do not overlap with
///		  the target buffer;
///
///	  @param s1 null if we are not copying into a string
///	  @param s1max 0 if we are not copying into a string
///
///	  @return 0 in case of success, 
///           1 means one of the arguments is null etc.
////////////////////////////////////////////////////////////////////////////////
static int validate_str_args(const char *s1, rsize_t s1max,
							 const char* restrict format, va_list arg)
{
	unsigned argtypes_max = strlen (format) / 2 * sizeof (int);
	int *argtypes = (int *) alloca (argtypes_max);
	int num_args = parse_printf_format (format, argtypes_max, argtypes);

	va_list ap;
	va_copy(ap, arg);

	int i = 0;
	for(; i < num_args; i++)
	{
		char *s = 0;

		switch (argtypes[i] & ~PA_FLAG_MASK)
		{
		case PA_CHAR:
		case PA_WCHAR:
		case PA_INT:
			if (argtypes[i] & PA_FLAG_LONG)
				va_arg(ap, long int);
			else if (argtypes[i] & PA_FLAG_LONG_LONG)
				va_arg(ap, long long int);
			else
				va_arg(ap, int);
			break;
		case PA_FLOAT:
		case PA_DOUBLE:
			if (argtypes[i] & PA_FLAG_LONG_DOUBLE)
				va_arg(ap, long double);
			else
				va_arg(ap, double);
			break;
		case PA_STRING:
		case PA_WSTRING:
			s = va_arg(ap, char*);
			if (!s)
				return 1;
			if (s1 && REGIONS_OVERLAP_CHECK(s1, s1max, s, strnlen_s(s, s1max)+1))
				return 1;
			break;
		case PA_POINTER:
			va_arg(ap, char*);
			break;
		}
	}

	va_end(ap);

	return 0;
}


////////////////////////////////////////////////////////////////////////////////
///   Checks whether a format string contains %n
///
///	  @param const char *  format
///
///	  @return 1 if a %n conversion specifier exists, 0 otherwise
////////////////////////////////////////////////////////////////////////////////
static int format_str_has_n_spec(const char *	format)
{
	unsigned argtypes_max = strlen (format) / 2 * sizeof (int);
	int *argtypes = (int *) alloca (argtypes_max);
	int num_args = parse_printf_format (format, argtypes_max, argtypes);

	int i = 0;
	for(; i < num_args; i++)
	{
		if (argtypes[i] & PA_FLAG_PTR)
		{
			// I think this only happens for %n
			return 1;
		}
	}
	return 0;
}


int vsprintf_s(char * restrict s, 
			   rsize_t n,
			   const char * restrict format,
			   va_list arg)
{
	int ret = 0;

	_CONSTRAINT_VIOLATION_IF((s == NULL || n == 0 || n >= RSIZE_MAX),
							 EINVAL,
							 0);

	_CONSTRAINT_VIOLATION_CLEANUP_IF(FORMAT_STR_CHECK(format),
									 s[0] = 0,
									 EINVAL,
									 0);

	_CONSTRAINT_VIOLATION_CLEANUP_IF(validate_str_args(s, n, format, arg), 
									 s[0] = 0,
									 EINVAL,
									 0);


	///	Is buffer s with length n sufficient?
	{
		va_list arg2;
		va_copy(arg2, arg);
		ret = vsnprintf(NULL, 0, format, arg2);
		va_end(arg2);
	}

#define TARGET_IS_SUFFICIENTLY_LARGE (ret < 0 || (unsigned)ret+1 > n)

	_CONSTRAINT_VIOLATION_CLEANUP_IF(TARGET_IS_SUFFICIENTLY_LARGE,
									 s[0] = 0,
									 EINVAL,
									 0);

	return vsnprintf(s, n, format, arg);
}


int vsnprintf_s(char * restrict s, rsize_t n,
				const char * restrict format,
				va_list arg)
{
	_CONSTRAINT_VIOLATION_IF((s == NULL || n == 0 || n >= RSIZE_MAX),
							 EINVAL,
							 -1);

	_CONSTRAINT_VIOLATION_CLEANUP_IF(FORMAT_STR_CHECK(format),
									 s[0] = 0,
									 EINVAL,
									 -1);

	_CONSTRAINT_VIOLATION_CLEANUP_IF(validate_str_args(s, n, format, arg), 
									 s[0] = 0,
									 EINVAL,
									 -1);


	return vsnprintf(s, n, format, arg);
}


int sprintf_s(char * restrict s, 
			  rsize_t n,
			  const char * restrict format, ...)
{
	int ret = 0;
	va_list argp;
	
	va_start(argp, format);
	ret = vsprintf_s(s, n, format, argp);
	va_end(argp);
	
	return ret;
}


int snprintf_s(char * restrict s, 
			   rsize_t n,
			   const char * restrict format, ...)
{
	int ret = 0;
	va_list argp;
	
	va_start(argp, format);
	ret = vsnprintf_s(s, n, format, argp);
	va_end(argp);
	
	return ret;
}


int vfprintf_s(FILE * restrict stream,
			   const char * restrict format, va_list arg)
{
	_CONSTRAINT_VIOLATION_IF(stream == NULL,
							 EINVAL,
							 -1);

	_CONSTRAINT_VIOLATION_IF(FORMAT_STR_CHECK(format),
							 EINVAL,
							 -1);

	_CONSTRAINT_VIOLATION_IF(validate_str_args(0, 0, format, arg), 
							 EINVAL,
							 -1);

	
	return vfprintf(stream, format, arg);
}


int fprintf_s(FILE * restrict stream,
			  const char * restrict format, ...)
{
	_CONSTRAINT_VIOLATION_IF(stream == NULL,
							 EINVAL,
							 -1);

	_CONSTRAINT_VIOLATION_IF(FORMAT_STR_CHECK(format),
							 EINVAL,
							 -1);


	va_list arg;
	va_start (arg, format);

	_CONSTRAINT_VIOLATION_CLEANUP_IF(validate_str_args(0, 0, format, arg), 
									 va_end(arg),
									 EINVAL,
									 -1);
	
	int ret = vfprintf_s(stream, format, arg);
	va_end(arg);
	return ret;
}


int vprintf_s(const char * restrict format,
			  va_list arg)
{
	_CONSTRAINT_VIOLATION_IF(FORMAT_STR_CHECK(format),
							 EINVAL,
							 -1);

	_CONSTRAINT_VIOLATION_IF(validate_str_args(0, 0, format, arg), 
							 EINVAL,
							 -1);

	int ret = printf(format, arg);

	return ret;
}


int printf_s(const char * restrict format, ...)
{
    _CONSTRAINT_VIOLATION_IF(FORMAT_STR_CHECK(format), EINVAL, -1);

	va_list arg;
	va_start(arg, format);

	///	no %s replacement may be null
    _CONSTRAINT_VIOLATION_CLEANUP_IF(validate_str_args(0, 0, format, arg), 
									 va_end(arg), EINVAL, -1);

	int ret = vprintf_s(format,arg);

	va_end(arg);
	return ret;
}


int vscanf_s(const char * restrict format, va_list arg)
{
	_CONSTRAINT_VIOLATION_IF(format == NULL,
							 EINVAL,
							 EOF);

	_CONSTRAINT_VIOLATION_IF(arg == NULL,
							 EINVAL,
							 EOF);

	return vfscanf_s(stdin, format,arg);
}


int scanf_s(const char * restrict format, ...)
{
	_CONSTRAINT_VIOLATION_IF(format == NULL,
							 EINVAL,
							 EOF);

	va_list argp;
	va_start(argp, format);
	int ret = vscanf_s(format, argp);
	va_end(argp);
	return ret;
}


int vsscanf_s(const char * restrict s,
			  const char * restrict format, va_list arg)
{
	_CONSTRAINT_VIOLATION_IF(s == NULL, 
							 EINVAL, 
							 EOF);

	_CONSTRAINT_VIOLATION_IF(format == NULL,
							 EINVAL,
							 EOF);

	_CONSTRAINT_VIOLATION_IF(arg == NULL,
							 EINVAL,
							 EOF);

	FILE *stream;
	stream = fmemopen ((char *) s, strlen(s), "r");
	int ret = vfscanf_s(stream, format, arg);
	fclose(stream);
	return ret;
}


int sscanf_s(const char * restrict s,
			 const char * restrict format, ...)
{
	_CONSTRAINT_VIOLATION_IF(s == NULL, 
							 EINVAL, 
							 EOF);

	_CONSTRAINT_VIOLATION_IF(format == NULL,
							 EINVAL,
							 EOF);

	va_list argp;
	va_start(argp, format);

	int ret = vsscanf_s(s, format, argp);

	va_end(argp);
	return ret;
}


int fscanf_s(FILE * restrict stream,
			 const char * restrict format, ...)
{
	va_list argp;
	va_start(argp, format);
	int ret = vfscanf_s(stream, format, argp);
	va_end(argp);
	return ret;
}


extern int gnu_vfscanf_s (_IO_FILE *s, const char *format, 
						  _IO_va_list argptr,
						  int *errp);

int vfscanf_s(FILE * restrict stream,
			  const char * restrict format, va_list arg)
{
	_CONSTRAINT_VIOLATION_IF(stream == NULL, 
							 EINVAL, 
							 EOF);

	_CONSTRAINT_VIOLATION_IF(format == NULL,
							 EINVAL,
							 EOF);

	_CONSTRAINT_VIOLATION_IF(arg == NULL,
							 EINVAL,
							 EOF);

	return 	gnu_vfscanf_s(stream, format, arg, NULL);
}
