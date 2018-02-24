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
/// TR 24731-1 stddef.h defines the type rsize_t. 
///////////////////////////////////////////////////////
// include the system-header first
#include_next <stddef.h>

// Glibc headers often include stddef.h only to get some types.
// In that case the caller defined __need_TYPE (e.g. __need_size_t).
// If stddef.h is included in a normal way, it will define the macro _STDDEF_H
// (Let's hope that this macro name is portable)
#if defined(_STDDEF_H) && !defined(SLIBC_STDDEF_H)
#define  SLIBC_STDDEF_H

// TR 24731-1 is not available if __STDC_WANT_LIB_EXT1__ equals 0
#if (!defined(__STDC_WANT_LIB_EXT1__) || (__STDC_WANT_LIB_EXT1__ != 0))

// Not totally sure if this is the correct solution.
// The problem is our stddef.h might get included with a
// define such as __need_NULL. In that case the above stddef.h
// will only define this one datatype and no size_t.
// Update: should not be needed any longer since we check
//         whether _STDDEF_H was defined above
//#define __need_size_t
//#include_next <stddef.h>

// TR 24731-1 addition to stddef.h
///
///rsize_t is a type for communicating realistic object sizes.
///Often, large object sizes are the result of an integer overflow. To
///detect these overflow conditions at runtime, the type rsize_t 
///restricts the maximum allowed object size. It does not allow
///large positive numbers.  rsize_t is an unsigned type. It's maximum
///value is given by the macro RSIZE_MAX.
typedef size_t rsize_t;

#endif

#endif
