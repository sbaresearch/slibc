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
#ifndef SLIBC_H
#define SLIBC_H
///////////////////////////////////////////////////////
/// @file
/// Internal include-file for the functions defined in ISO/IEC TR 24731-1 
//  'Bounds-checking interfaces'.
///
/// This Technical Report provides alternative functions for the C library that
/// promote safer, more secure programming. The functions verify that output 
/// buffers are large enough for the intended result and return a failure 
/// indicator if they are not. Data is never written past the end of an array. 
/// All string results are null terminated.
//////////////////////////////////////////////////////
#define SLIBC_WANT_MKTEMP

#include "slibc/errno.h"
#include "slibc/stddef.h"
#include "slibc/stdint.h"
#include "slibc/stdlib.h"
#include "slibc/time.h"
#include "slibc/string.h"
#include "slibc/stdio.h"

#ifdef __cplusplus
extern "C" {
#endif

/// The Macro SLIBC_MT turns on SLIBC_Multithreading support. By default, it is
/// activated. You can comment out the following line to deactivate it.
/// SLIBC_MT will add a dependecy to pthread.h and lock access to shared variables.
/// Please note that, additionally, the library needs to be compiled with -pthread.
#define SLIBC_MT

#ifdef SLIBC_MT
# include <pthread.h>
# define SLIBC_MUTEX_LOCK(mutex) pthread_mutex_lock(mutex)
# define SLIBC_MUTEX_UNLOCK(mutex) pthread_mutex_unlock(mutex)
#else
# define SLIBC_MUTEX_LOCK(mutex) 
# define SLIBC_MUTEX_UNLOCK(mutex) 
# define __thread 
#endif

/// This struct contains details about a constraint violation.
/// In our implementation a constraint handler's second argument
/// always points to ConstraintHandlerDetails
typedef struct {
	const char *function;
	const char *file;
	unsigned line;
} ConstraintHandlerDetails;


/// Pointer to the current constraint handler
extern __thread constraint_handler_t slibc_constraint_handler;

void slibc_call_constraint_handler(const char *msg,
								   const char *func,
								   const char *file,
								   unsigned line,
								   errno_t error);

/* #define RUNTIME_CONSTRAINT_HANDLER() \ */
/* 	slibc_call_constraint_handler("Runtime constraint violation", "",	\ */
/* 								  __FUNCTION__,	 __FILE__, __LINE__, EINVAL) */

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

/// 1) check whether s1 points into the region [s1, s1+s1max)
/// 2) check whether the last byte of s2 is >= s1 
/// s1_size and s2_size specify the size of the respective buffers, the size
/// is string_length+1 because of the terminating null byte.
#define REGIONS_OVERLAP_CHECK(s1, s1_size, s2, s2_size)					\
	( ((s2 >= s1) && ((char *)s2 < ((char *)s1 + s1_size))) ||			\
	  ((s2 < s1)  && ((char *)s2 + s2_size -1 >= (char *)s1)) )





#define _CONSTRAINT_VIOLATION(msg, error_code, ret_code)				\
	do {																\
		errno = (error_code);											\
		slibc_call_constraint_handler(msg,								\
									  __FUNCTION__,						\
									  __FILE__,							\
									  __LINE__,							\
									  error_code);						\
		return (ret_code);												\
	} while(0)

#define _CONSTRAINT_VIOLATION_IF(expr, error_code, ret_code)			\
    do {																\
		int expr_val = expr;											\
		if (expr_val)													\
		{																\
			errno = error_code;											\
			slibc_call_constraint_handler(#expr, __FUNCTION__,__FILE__, __LINE__, error_code); \
			return ret_code;											\
		}																\
    } while(0)
	
/* N.B: cleanup_code is only evaluated in case of a 
 *      constraint violation (i.e., if expr is true)
 */
#define _CONSTRAINT_VIOLATION_CLEANUP_IF(expr, cleanup_code, error_code, ret_code) \
    do {																\
		int expr_val = expr;											\
		if (expr_val)													\
		{																\
			do {														\
				cleanup_code;	/* execute */							\
			} while(0);													\
			errno = error_code;											\
			slibc_call_constraint_handler(#expr, __FUNCTION__, __FILE__, __LINE__, error_code); \
			return ret_code;											\
		}																\
    } while(0)



#define SLIBC_INTERNAL __attribute__((visibility ("hidden")))



#ifdef __cplusplus
}
#endif


#endif
