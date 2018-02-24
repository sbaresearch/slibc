// This Version of strtok_s is based on the glibc implementation 
// of the strtok_r.
// It includes content from:
//    glibc-2.16.0/string/strpbrk.c
//    glibc-2.16.0/string/strspn.c
//    glibc-2.16.0/string/strtok_r.c

/* Reentrant string tokenizer.	Generic version.
   Copyright (C) 1991,1996-1999,2001,2004 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, write to the Free
   Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307 USA.	*/

#include <string.h>
#include "slibc.h"

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT. */
static rsize_t
strspn_s (const char *s, rsize_t * restrict smax, const char *accept);

/* Find the first occurrence in S of any character in ACCEPT. */
static char *
strpbrk_s (const char *s, rsize_t * restrict smax, const char *accept);


SLIBC_INTERNAL char *
gnu_strtok_s (char * restrict s1,
			  rsize_t * restrict s1max,
			  const char * restrict s2,
			  char ** restrict ptr)
{
	char *token;
	rsize_t num_leading_delim = 0;

	if (s1 == NULL)
		s1 = *ptr;

	/* Scan leading delimiters.	 */
	num_leading_delim = strspn_s (s1, s1max, s2);
	s1 += num_leading_delim;
	(*s1max) -= num_leading_delim;

	if (*s1 == '\0')
	{
		*ptr = s1;
		return NULL;
	}

	/* Find the end of the token.  */
	token = s1;
	s1 = strpbrk_s (token, s1max, s2);
	if (s1 == NULL)
	{
		/* This token finishes the string.	*/
		*ptr = (char *) memchr (token, '\0', (size_t) s1max);
		*s1max -= (*ptr) - token;
	}
	else
	{
		/* Terminate the token and make *SAVE_PTR point past it.  */
		*s1 = '\0';
		*ptr = s1 + 1;
		*s1max -= (*ptr) - token;
	}
	return token;
}

/* Find the first occurrence in S of any character in ACCEPT. */
static char *
strpbrk_s (const char *s, rsize_t * restrict smax, const char *accept)
{
	unsigned i = 0;
	while (*s != '\0' && i < *smax)
	{
		const char *a = accept;
		while (*a != '\0')
			if (*a++ == *s)
				return (char *) s;
		++s;
		++i;
	}
	
	return NULL;
}

/* Return the length of the maximum initial segment
   of S which contains only characters in ACCEPT. */
static rsize_t
strspn_s (const char *s, rsize_t * restrict smax, const char *accept)
{
	const char *p;
	const char *a;
	rsize_t count = 0;
	rsize_t i = 0;
	
	for (p = s; *p != '\0' && i < *smax ; ++p)
	{
		i++;
		for (a = accept; *a != '\0'; ++a)
			if (*p == *a)
				break;
		if (*a == '\0')
			return count;
		else
			++count;
	}
	
	return count;
}
