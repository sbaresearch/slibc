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
