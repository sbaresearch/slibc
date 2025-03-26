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
