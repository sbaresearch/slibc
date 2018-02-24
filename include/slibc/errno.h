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
/// TR 24731-1 errno.h defines the type errno_t. 
///////////////////////////////////////////////////////
// include the system-header first
#include_next <errno.h>

// Glibc headers often include errno.h only to get some types
// in that case the caller defined __need_TYPE (e.g. __need_Emath)
// If errno.h is included in a normal way, it will define the macro _ERRNO_H
// (Let's hope that this macro name is portable)
#if defined(_ERRNO_H) && !defined(SLIBC_ERRNO_H)
#define  SLIBC_ERRNO_H

// TR 24731-1 is not available if __STDC_WANT_LIB_EXT1__ equals 0
#if (!defined(__STDC_WANT_LIB_EXT1__) || (__STDC_WANT_LIB_EXT1__ != 0))

//TR 24731-1 addition to errno.h
///errno_t is the type for communicating error values. 
///It may contain all of the values that might be found in errno.
typedef int errno_t;

#endif

#endif
