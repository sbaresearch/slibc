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
/// TR 24731-1 stdint.h defines the macro RSIZE_MAX.
///////////////////////////////////////////////////////
#ifdef __cplusplus
// In C++ we explicitly have to request that the
// SIZE_MAX macro is defined by defining __STDC_LIMIT_MACROS.
#define __STDC_LIMIT_MACROS 
#endif
// include the system-header first
#include_next <stdint.h>

#ifndef  SLIBC_STDINT_H
#define  SLIBC_STDINT_H

// TR 24731-1 is not available if __STDC_WANT_LIB_EXT1__ equals 0
#if (!defined(__STDC_WANT_LIB_EXT1__) || (__STDC_WANT_LIB_EXT1__ != 0))


///RSIZE_MAX defines the highest number that a value of type rsize_t may contain.
///
///Functions that have a parameter of rsize_t will report a runtime
///constraint violation if its value exceeds RSIZE_MAX.
#define RSIZE_MAX (SIZE_MAX >> 1)

#endif //(!defined(__STDC_WANT_LIB_EXT1__) || (__STDC_WANT_LIB_EXT1__ != 0))

#endif
