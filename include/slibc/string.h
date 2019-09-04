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
///////////////////////////////////////////////////////
/// @file
/// Contains those _s-functions that are related to strings
///////////////////////////////////////////////////////
#include_next <string.h>

#ifndef SLIBC_STRING_H
#define SLIBC_STRING_H

// TR 24731-1 is not available if __STDC_WANT_LIB_EXT1__ equals 0
#if (!defined(__STDC_WANT_LIB_EXT1__) || (__STDC_WANT_LIB_EXT1__ != 0))

#include "./base_.h"
#include "./stddef.h"
#include "./errno.h"


SLIBC_BEGIN_DECLS

///////////////////////////////////////////////////////
/// The strnlen_s function determines the length of @a s.
/// 
/// At most maxsize characters are accessed and maxsize is returned. Otherwise
/// the number of characters before the nullbyte are returned.
/// The only difference to @a strnlen is that in case of @a s being a 
/// null pointer this function gracefully returns 0.
///
/// @rcs  There are no runtime-constraints.
///
/// @param [in] s          The string of whose length should be calculated
/// @param [in] maxsize    Only maxsize characters should be accessed
///
/// @return           Zero if @a s is a null pointer. 
///                   @a Maxsize characters if there is no nullbyte in the first @a maxsize chars of @a s.
///                   Otherwise the number of characters before the nullbyte.
/// @see strlen, strnlen
///////////////////////////////////////////////////////

size_t strnlen_s(const char *s, size_t maxsize);


///////////////////////////////////////////////////////
/// The strcpy_s function copies the string \a s2 to \a s1.
///
/// Unlike the traditional strcpy, the size of the destination buffer \a s1
/// has to be specified. The function makes sure that it never
/// writes outside the specified bounds.
///
/// The buffer @a s1 must be large enough for holding @a s2 plus
/// the terminating null byte.
///
/// @post As long as s1 is not null, the string in \a s1 will always be 
/// null-terminated.
///
/// @rcs A runtime-constraint violation occurs if
///  \li either s1 or s2 is a null pointer. 
///  \li s1 (as determined by s1max) is not large enough to hold @a s2 (including its terminating null byte).
///  \li s1 and s2 overlap.
///
/// @param [out] s1        The destination buffer 
/// @param [in] s1max      The size of s1
/// @param [in] s2         The source string
///
/// @return           0 if there was no runtime-constraint violation. 
///                   Otherwise a non-zero value is returned.   
///////////////////////////////////////////////////////

errno_t strcpy_s(char * restrict s1, rsize_t s1max, const char * restrict s2);


///////////////////////////////////////////////////////
/// The strncpy_s function copies not more than @a n characters from @a s2 to @a s1.
/// 
/// In contrast to @a strncpy this functions expects the buffer size
/// of @a s1 as a second parameter. The function will never write
/// beyond the specified buffer size.
///
/// @rcs A runtime-constraint violation occurs if
///  \li either s1 or s2 is a null pointer. 
///  \li s1 (as determined by s1max) is not large enough to hold the source (including its terminating null byte).
///  \li s1 and s2 overlap.
///
/// @param [out] s1        The destination buffer
/// @param [in] s1max      The size of s1
/// @param [in] s2         The source string
/// @param [in] n          Maximum amount of characters that should be copied. 
///                        (If @a s2 is shorter than @a n, less bytes are copied)
///
/// @return           0 if there was no runtime-constraint violation. 
///                   Otherwise a non-zero value is returned. 
/////////////////////////////////////////////////////// 

errno_t strncpy_s(char * restrict s1, rsize_t s1max, const char * restrict s2, rsize_t n);


///////////////////////////////////////////////////////
/// The strcat_s function copies the string @a s2 to the end of @a s1.
///
/// The string concatentation operation will overwrite the existing terminating null byte of @a s1.
/// The buffer s1 must be large enough to accomodate both for @a s1, @a s2 and @a s2's terminating null
/// byte. In contrast to the traditional @a strcat function, @a strcat_s expects its caller to 
/// explicitly specify the size of the destination buffer @a s1. This allows the function to 
/// check whether the supplied is indeed large enough.
///
/// @rcs A runtime-constraint violation occurs if
///  \li either @a s1 or @a s2 is a null pointer. 
///  \li @a s1 (as determined by @a s1max) is not large enough to hold @a s1+s2.
///  \li @a s1 and @a s2 overlap.
///
/// @param [in,out] s1         The destination buffer
/// @param [in]     s1max      The size of @a s1
/// @param [in]     s2         The source string
///
/// @return           0 if there was no runtime-constraint violation. 
///                   Otherwise a non-zero value is returned. 
/// @see strcat
///////////////////////////////////////////////////////

errno_t strcat_s(char * restrict s1,
				 rsize_t s1max,
				 const char * restrict s2);

                 
///////////////////////////////////////////////////////
/// The strncat_s function copies not more than @a n characters of the string @a s2 to the end of @a s1.
///
/// The string concatentation operation will overwrite the existing terminating null byte of @a s1.
/// The buffer s1 must be large enough to accomodate both for @a s1, @a s2 and s2's terminating null
/// byte. In contrast to the traditional @a strcat function, @a strcat_s expects its caller to 
/// explicitly specify the size of the destination buffer @a s1. This allows the function to 
/// check whether the supplied is indeed large enough.
///
/// @rcs A runtime-constraint violation occurs if
///  \li either @a s1 or @a s2 is a null pointer. 
///  \li @a s1 (as determined by @a s1max) is not large enough to hold the result.
///  \li @a s1 and @a s2 overlap.
/// 
/// @param [in,out] s1         The destination buffer
/// @param [in]     s1max      The size of s1
/// @param [in]     s2         The source string
/// @param [in]     n          Maximum amount of characters that should be copied. 
///                            (If @a s2 is shorter than @a n, less bytes are copied)
/// @return           0 if there was no runtime-constraint violation. 
///                   Otherwise a non-zero value is returned.
/// @see strncat
///////////////////////////////////////////////////////				 
 
errno_t strncat_s(char * restrict s1,
				  rsize_t s1max,
				  const char * restrict s2,
				  rsize_t n);


////////////////////////////////////////////////////////
/// The memcpy_s function copies @a n bytes from buffer @a s2 to buffer @a s1.
///  
/// Unlike the traditional @a memcpy function @a memcpy_s accepts a new parameter
/// @a s1max for specifying the buffer size of @a s1. A runtime-constraint violation
/// occurrs (instead of a buffer overflow) if @a s1 not large enough to hold
/// @a n bytes of @a s2.
///
/// @rcs A runtime-constraint violation occurs if
///  \li either @a s1 or @a s2 is a null pointer. 
///  \li @a s1 (as determined by @a s1max) is not large enough to hold the result.
///  \li @a s1 and @a s2 overlap.
///
/// @param [out] s1         The destination buffer
/// @param [in]  s1max      The size of s1
/// @param [in]  s2         The source buffer
/// @param [in]  n          Amount of bytes to be copied
///
/// @return           0 if there was no runtime-constraint violation. 
///                   Otherwise a non-zero value is returned.
///
/// @see memcpy
////////////////////////////////////////////////////////

errno_t memcpy_s(void * restrict s1, rsize_t s1max,
				 const void * restrict s2, rsize_t n);


///////////////////////////////
/// The memmove_s function copies @a n bytes from buffer @a s2 to buffer @a s1 while allowing the buffers to overlap.
///  
/// Unlike the traditional @a memmove function @a memmove_s accepts a new parameter
/// @a s1max for specifying the buffer size of @a s1. A runtime-constraint violation
/// occurrs (instead of a buffer overflow) if @a s1 not large enough to hold
/// @a n bytes of @a s2.
///
/// @rcs A runtime-constraint violation occurs if
///  \li either @a s1 or @a s2 is a null pointer. 
///  \li @a s1 (as determined by @a s1max) is not large enough to hold the result.
///  
/// @remark @a s1 and @a s2 are allowed to overlap.
///
/// @param [out] s1         The destination buffer
/// @param [in]  s1max      The size of s1
/// @param [in]  s2         The source buffer
/// @param [in]  n          Amount of bytes to be copied
///
/// @return           0 if there was no runtime-constraint violation. 
///                   Otherwise a non-zero value is returned.
///
/// @see memmove
///////////////////////////////                 

errno_t memmove_s(void *s1, rsize_t s1max,
		const void *s2, rsize_t n);


///////////////////////////////
/// The strtok_s function breaks a string into smaller strings according to a specified delimiter.
///
/// A sequence of strok_s invocations is necessary to break up a string. On the first call,
/// @a s1 points to the buffer to be tokenized, @a s1max denotes its size, @a delim points to the
/// delimiter string, @a ptr points to a caller-provided char pointer.
/// On successive calls, @a s1 should be NULL, while @a ptr should be unchanged from the 
/// previous call.
///
/// @remark Please note that the buffer @a s1 will be modified by @a strok_s.  
///  If a delimiter is found in @a s1, it will be replaced
///  with a null byte.
///
/// @param [in]    s1     on the first call: the buffer to be tokenized. On subsequent calls: Null
/// @param [in,out] s1max  on the first call the caller supplies the size of s1 here. 
///                      on subsequent calls the number is upated to reflect the number of characters in the current oken.
/// @param [in]    delim  the delimiter   
/// @param [in,out] ptr    used internally by strtok_s in order to maintain state between successive calls of this function
///
/// @return A pointer to the first character of a token, or a null pointer if there is no
///         token or there is a runtime-constraint violation.
///
/// @see    strtok, strtok_r
///////////////////////////////

char *strtok_s(char * restrict s1,
	rsize_t * restrict s1max,
	const char * restrict delim,
	char ** restrict ptr);


///////////////////////////////
/// The strerror_s function returns a human-readable error message for a specified error number.
///
/// @a strerror_s copies the message to buffer @a s. The caller is 
/// expected to provide the length of @a s in parameter @a maxsize.
/// If the buffer @a s is not big enough to hold the result, the error message is truncated
/// and the last byte of @a s is set to the null byte.
///
/// @rcs A runtime-constraint violation occurs if
///  \li @a s is a null pointer
///
/// @param [out] s destination buffer for the error message
/// @param [in] maxsize
/// @param [in] errnum the error number (typically from errno)
///
/// @return           0 if there was no runtime-constraint violation. 
///                   Otherwise a non-zero value is returned.
///
/// @see    strerror, strerror_r
///////////////////////////////

errno_t strerror_s(char *s, rsize_t maxsize,
		errno_t errnum);


///////////////////////////////
/// The strerrorlen_s function determines the length of the error-message for a specified error number.
///
/// You can use this function to find out how big the buffer passed to strerror_s shall be
/// in order to have a non-truncated error mesage.
///
/// @param [in] errnum the error number
///
/// @return The strerrorlen_s function returns the number of characters (not including the null character) in
///         the error-message.
///
///////////////////////////////        

size_t strerrorlen_s(errno_t errnum);

///////////////////////////////
/// The memset_s function copies the value ch (after conversion to unsigned char as if by (unsigned char)ch)
/// into each of the first count characters of the object pointed to by dest. The following errors are detected
/// at runtime and call the currently installed constraint handler function after storing ch in every location
/// of the destination range [dest, dest+destsz) if dest and destsz are themselves valid.
///
/// The behavior is undefined if the size of the character array pointed to by dest < count <= destsz;
/// in other words, an erroneous value of destsz does not expose the impending buffer overflow.
///
/// @param [out] dest destination buffer
///
/// @param [in] destsz size of the destination array
///
/// @param [in] ch fill character
///
/// @param [in] count number of bytes to fill
///
/// @return The memset_s function returns zero on success, non-zero on error. Also on error, if dest is not
/// a null pointer and destsz is valid, writes destsz fill bytes ch to the destination array.
///
///////////////////////////////

errno_t memset_s(void *dest, rsize_t destsz, int ch, rsize_t count);

SLIBC_END_DECLS


#if defined(__cplusplus) && (defined(SLIBC_WANT_TEMPLATES))
# include "./string_templates_.hpp"
#endif

#endif //#if (!defined(__STDC_WANT_LIB_EXT1__) || (__STDC_WANT_LIB_EXT1__ != 0))

#endif
