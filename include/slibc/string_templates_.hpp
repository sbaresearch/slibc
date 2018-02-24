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
/// Contains overloaded templates for some _s-functions defined in string.h.
///
/// The usage of these templates is restricted to C++.
/// this file is included automatically, if the macro 
/// _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES is defined.
/// It's not necessary to declare the size of the destination
/// buffer, when the overloaded functions are available (only
/// if the compiler can calculate the size automatically).
/// 
/// The overloaded templates make the _s-functions easier to use.
/// Buffer sizes, which are declared in the _s-functions, are already
/// known at compilation time. This can be used by C++ templates.
///
/// Usage Example:
/// @code
///         char buf[10];
///         char *input = "123456789ABCDEF";
///         // ContstraintHandler is called, because the input 
///         // contains more than 10 characters
///         strcpy_s(buf, input)
/// @endcode
/// As you can see it's not necessary to explicitly declare the size-parameter (usually one
/// has to write strcpy_s(buf, sizeof(buf), input)).
/// This feature enhances the useability (less to write) and the migration
/// process to the new _s-functions. 
/// 
///////////////////////////////////////////////////////
#ifndef SLIBC_STRING_TEMPLATES_HPP
#define SLIBC_STRING_TEMPLATES_HPP

#include "./string.h"

///////////////////////////////////////////////////////
/// The strcpy_s template function copies the string \a s2 to \a s1.
///
/// For statically allocated destination buffers this C++ template
/// function automatically deducts @a strcpy_s' size argument @a s1max.
///
/// @param [out] s1        The destination buffer 
/// @param [in] s2         The source string
///
/// @return           0 if there was no runtime-constraint violation. 
///                   Otherwise a non-zero value is returned.   
///////////////////////////////////////////////////////
template<rsize_t s1max> errno_t strcpy_s(char (&s1)[s1max], const char * restrict s2)
{
	return strcpy_s(s1, s1max, s2);
}

///////////////////////////////////////////////////////
/// The strncpy_s template function copies the string \a s2 to \a s1.
///
/// For statically allocated destination buffers this C++ template
/// function automatically deducts @a strncpy_s' size argument @a s1max.
///
/// @param [out] s1        The destination buffer 
/// @param [in] s2         The source string
/// @param [in] n          Maximum amount of characters that should be copied. 
///                        (If @a s2 is shorter than @a n, less bytes are copied)
///
/// @return           0 if there was no runtime-constraint violation. 
///                   Otherwise a non-zero value is returned.   
///////////////////////////////////////////////////////
template<rsize_t s1max> errno_t strncpy_s(char (&s1)[s1max], const char * restrict s2, rsize_t n)
{
	return strncpy_s(s1, s1max, s2, n);
}


///////////////////////////////////////////////////////
/// The strcat_s template function copies the string @a s2 to the end of @a s1.
///
/// For statically allocated destination buffers this C++ template
/// function automatically deducts @a strcat_s' size argument @a s1max.
///
/// @param [in,out] s1         The destination buffer
/// @param [in]     s2         The source string
///
/// @return           0 if there was no runtime-constraint violation. 
///                   Otherwise a non-zero value is returned. 
///////////////////////////////////////////////////////
template<rsize_t s1max> errno_t strcat_s(char (&s1)[s1max],
										 const char * restrict s2)
{
  return strcat_s(s1, s1max, s2);
}

///////////////////////////////////////////////////////
/// The strncat_s template function copies not more than @a n characters of the string @a s2 to the end of @a s1.
///
/// For statically allocated destination buffers this C++ template
/// function automatically deducts @a strncat_s' size argument @a s1max.
///
/// @param [in,out] s1         The destination buffer
/// @param [in]     s2         The source string
/// @param [in]     n          Maximum amount of characters that should be copied. 
///                            (If @a s2 is shorter than @a n, less bytes are copied)
/// @return           0 if there was no runtime-constraint violation. 
///                   Otherwise a non-zero value is returned.
///////////////////////////////////////////////////////	
template<rsize_t s1max> errno_t strncat_s(char (&s1)[s1max],
										 const char * restrict s2, rsize_t n)
{
  return strncat_s(s1, s1max, s2, n);
}

#endif
