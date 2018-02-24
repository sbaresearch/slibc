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
#ifndef SLIBC_BASE_H
#define SLIBC_BASE_H

// allow compilation with a non c99-compiler
#if __STDC_VERSION_ < 199901L
#  define restrict  
#endif

// translate the Visual Studio Name to our name
#ifdef _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
#define SLIBC_WANT_TEMPLATES
#endif

/* C++ needs to know that types and declarations are C, not C++.  */
#ifdef  __cplusplus
# define SLIBC_BEGIN_DECLS  extern "C" {
# define SLIBC_END_DECLS    }
#else
# define SLIBC_BEGIN_DECLS
# define SLIBC_END_DECLS
#endif

#endif
