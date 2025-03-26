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
/// Contains those _s functions that were added to C99's /usr/include/stdlib.h
///////////////////////////////////////////////////////
#include_next <stdlib.h>

#ifndef SLIBC_STDLIB_H
#define SLIBC_STDLIB_H

// TR 24731-1 is not available if __STDC_WANT_LIB_EXT1__ equals 0
#if (!defined(__STDC_WANT_LIB_EXT1__) || (__STDC_WANT_LIB_EXT1__ != 0))

#include "./base_.h"
#include "./errno.h"
#include "./stddef.h"

SLIBC_BEGIN_DECLS

//TR 24731-1 addition to stdlib.h

/// Definition of callback-type constraint_handler_t.
/// All SLIBC-functions invoke the constraint handler in case of a constraint violation.
typedef void (*constraint_handler_t)(const char * restrict msg,
									 void * restrict ptr,
									 errno_t error);


///////////////////////////////////////////////////////////////////////////////
///   The set_constraint_handler function sets a user-specified constraint handler.
///
///   The constraint handler is called whenever a runtime constraint violation 
///   is detected. If, for example, a user calls strcpy_s(NULL, 0, source) the
///   currently set runtime constraint handler will be invoked. The constraint 
///   handler is specific to each thread.
///
///   If the application does not set its own constraint handler, the default
///   constraint handler is called. In our implementation the default constraint 
///   handler is abort_handler_s.
///
///   @rcs  There are no runtime-constraints.
///
///   @param [in]  handler  a pointer to the new handler function
///
///   @return      the previously registered handler
///   @see   abort_handler_s, ignore_handler_s
///////////////////////////////////////////////////////////////////////////////
constraint_handler_t set_constraint_handler_s(constraint_handler_t handler);


/// The abort handler gives out an errormessage on stderr before
/// it ends the program with the function abort
void abort_handler_s(const char * restrict msg,
					 void * restrict ptr,
					 errno_t error);

/// the ignore_handler_s is used to ignore constraint violations
/// it does nothing
void ignore_handler_s(const char * restrict msg,
					  void * restrict ptr,
					  errno_t error);


///////////////////////////////////////////////////////////////////////////////
///   The getenv_s function gets the value of an environment variable.
///
///   Developers often make wrong assumptions about the size of environment 
///   variables. Since a local attacker can set environment variables, the
///   environment has to be considered evil as every other input. The getenv_s
///   functions forces the programmer to supply a maximum buffer size.
///
///   @rcs A runtime-constraint violation occurs if
///     \li name is a null pointer
///     \li maxsize is zero or greater than RSIZE_MAX
///     \li value shall not be a null pointer.
///   In case of a runtime-constriant violation, the a non-zero @a len is 
///   dereferenced and set to zero.
///
///   @param [out] len     If len is not Null, the integer pointed to by len 
///                        will be set to the length of the variable's value 
///                  (one needs a buffer with length + 1 for storing the string)
///   @param [out] value   contains the environment variable's value on success
///   @param [in]  maxsize the size of the buffer pointed to by value
///   @param [in]  name    the name of the environment variable to search for
///
///   @return Zero when the enviroment variable was found and successfully 
///             stored in the buffer pointed to by value. 
///           Non-zero otherwise.
///
///   @ex    
///         char env_value[255];
///         getenv_s(NULL, env_value, sizeof(env_value), "PATH");
///   @endex
///
///   @see    getenv
///////////////////////////////////////////////////////////////////////////////
errno_t getenv_s(size_t * restrict len,
				 char * restrict value, rsize_t maxsize,
				 const char * restrict name);


///////////////////////////////
///   This function sorts an array in ascending order.
///
///   The array is sorted according to the specified comparison function. 
///   Besides performing several runtime-checks (see rcs), the only difference is that
///   the comparison function accepts an additional argument for the caller's
///   use.
///
///   @rcs A runtime-constraint violation occurs if
///     \li @a nmemb or @a size is greater than @a RSIZE_MAX
///     \li if @a nmemb > 0 and (@a base or @a comparison are null pointers)
///
///   @param [in,out] base    points to the start of the array
///   @param [in]     nmemb   specifies the number of elements in the array
///   @param [in]     size    gives the size of an individual array argument
///   @param [in]     compar  a pointer to the comparison function
///   @param [in,out] context may hold a user-defined value or Null. This value 
///                           will be supplied as an extra-argument to the 
///                           comparison function.
///   @return zero if there was no runtime-constraint violation. 
///           non-zero value otherwise.
///
///   @see    qsort
///////////////////////////////

errno_t qsort_s(void *base, rsize_t nmemb, rsize_t size, 
				int (*compar) (const void *x, const void *y,
								void *context),
				void *context
   			);


///////////////////////////////
///   This function performs a binary search of a sorted array.
///
///   The array (given by base, nmemb and size) is searched for
///   a member that is the same as the object pointed to by key.
///
///   @rcs A runtime-constraint violation occurs if
///     \li @a nmemb or @a size is greater than @a RSIZE_MAX
///     \li if @a nmemb > 0 and (@a key, @a base or @a comparison are null pointers)
///
///   @param [in]     key     points to the object to be matched
///   @param [in]     base    points to the start of the array
///   @param [in]     nmemb   specifies the number of elements in the array
///   @param [in]     size    gives the size of an individual array argument
///   @param [in]     compar  a pointer to the comparison function
///   @param [in,out] context may hold a user-defined value or Null. This value 
///                           will be supplied as an extra-argument to the 
///                           comparison function.
///
///   @return A pointer to a matching element of the array
///           NULL if no match is found or there is a runtime-constraint violation
///   @see    bsearch
///////////////////////////////

void *bsearch_s (const void *key, const void *base, rsize_t nmemb, rsize_t size,
				int (*compar) (const void *, const void *, void *context),
				void *context);


// wctomb_s currently not implemented
// mbstowcs_s currently not implemented
// wcstombs_s currently not implemented	

SLIBC_END_DECLS

#endif //#if (!defined(__STDC_WANT_LIB_EXT1__) || (__STDC_WANT_LIB_EXT1__ != 0))

#endif
