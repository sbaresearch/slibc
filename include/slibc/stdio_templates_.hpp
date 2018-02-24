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
