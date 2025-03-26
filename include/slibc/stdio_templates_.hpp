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
/// Contains overloaded templates for some _s-functions defined in stdio.h.
///
/// Usage of these templates is only possible in C++.
/// For more information please consult the documentation in 
/// string_templates_.hpp
///////////////////////////////////////////////////////
#ifndef SLIBC_STDIO_TEMPLATES_HPP
#define SLIBC_STDIO_TEMPLATES_HPP

#include "./stdio.h"
#include <stdarg.h>

///////////////////////////////////////////////////////
/// This function provides for fomatted output into buffer @a s while taking into account the size of s.
///
/// For statically allocated destination buffers this C++ template
/// function automatically deducts @a sprintf' size argument @a n.
///
/// @param [out] s1        The destination buffer 
/// @param [in]  format    format string (equal to printf)
/// @param [in]  ...       variable amount of parameters which are treated according
///                        to the specified format string.
/// @return 
///   the number of characters written (not counting the null byte) 
///   a negative number in case of an encoding error
///   0 in case of runtime-constraint violation
///////////////////////////////////////////////////////
template<rsize_t n> int sprintf_s(char (&s1)[n], 
								  const char * restrict format, ...) 
{
  va_list arg;
  va_start(arg, format);
  int r = vsprintf_s(s1, n, format, arg);
  va_end(arg);
  return r; 
}


///////////////////////////////////////////////////////
/// This function provides for fomatted output into buffer @a s while taking into account the size of s.
///
/// For statically allocated destination buffers this C++ template
/// function automatically deducts @a snprintf' size argument @a n.
///
/// @param [out] s1        The destination buffer 
/// @param [in]  format    format string (equal to printf)
/// @param [in]  ...       variable amount of parameters which are treated according
///                        to the specified format string.
/// @return 
///   the number of characters that would have been written (not counting the null byte) 
///      had s1 been sufficiently large
///   a negative number in case of an encoding error
///   0 in case of runtime-constraint violation
///////////////////////////////////////////////////////
template<rsize_t n> int snprintf_s(char (&s1)[n], 
								  const char * restrict format, ...) 
{
  va_list arg;
  va_start(arg, format);
  int r = vsnprintf_s(s1, n, format, arg);
  va_end(arg);
  return r; 
}

#endif
