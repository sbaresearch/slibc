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
/// Contains those _s-functions that are related to time
///////////////////////////////////////////////////////
#include_next <time.h>

// Glibc headers often include time.h only to get some types
// in that case the caller defined __need_TYPE (e.g. __need_time_t)
// If time.h is included in a normal way, it will define the macro _TIME_H
// (Let's hope that this macro name is portable)
#if defined(_TIME_H) && !defined(SLIBC_TIME_H)
#define SLIBC_TIME_H

// TR 24731-1 is not available if __STDC_WANT_LIB_EXT1__ equals 0
#if (!defined(__STDC_WANT_LIB_EXT1__) || (__STDC_WANT_LIB_EXT1__ != 0))

#include "./base_.h"
#include "./errno.h"
#include "./stddef.h"

SLIBC_BEGIN_DECLS

///////////////////////////////
/// The asctime_s function converts its argument to a text representation.
///
/// Unlike the traditional asctime function the size of the destination buffer
/// has to be specified.
///
/// @rcs A runtime-constraint violation occurs if
///     \li s or timeptr are a null pointer
///     \li maxsize is less than 26  or greater than RSIZE_MAX
///     \li the broken-down time pointed to by timeptr is not normalized
/// In case of a runtime-constriant violation, s[0] is set to a null character 
/// if it is safe to do so.
///
/// @param [out] s        specifies the destination buffer
/// @param [in]  maxsize  the size of @a s
/// @param [in]  timeptr  pointer to the broken-down time that shall be converted
///
/// @return Zero on success
///         Non-zero otherwise.
///
/// @see    asctime
///////////////////////////////

errno_t asctime_s(char *s, rsize_t maxsize, const struct tm *timeptr);


///////////////////////////////
/// This functions converts a time represented as type @a time_t to a text representation.
///
/// The type @a time_t represents the number of seconds elapsed since the Epoch,
/// 1970-01-01 00:00:00 +0000 (UTC).
///
/// Calling ctime_is is equivalent to
/// asctime_s( s, maxsize, localtime_s( timer ) )
///
/// @rcs A runtime-constraint violation occurs if
///     \li s or timeptr are a null pointer
///     \li maxsize is less than 26  or greater than RSIZE_MAX
/// In case of a runtime-constriant violation, s[0] is set to a null character 
/// if it is safe to do so.
///
/// @param [out] s        specifies the destination buffer
/// @param [in]  maxsize  the size of @a s
/// @param [in]  timeptr  pointer to a value of type @time_t that shall be converted
///
/// @return Zero on success
///         Non-zero otherwise.
///
/// @see    ctime
///////////////////////////////

errno_t ctime_s(char *s, rsize_t maxsize, const time_t *timer);


///////////////////////////////
/// The gmtime_s function converts a time given as type @a time_t to UTC broken-down time.
///
/// @rcs A runtime-constraint violation occurs if
///     \li timer or result are a null pointer
///
/// @param [in]  timer  pointer to a value of type @time_t that shall be converted
/// @param [out] result the resulting time expressed as UTC broken-down time
///
/// @return On success @a result is returned.
///         Otherwise a NULL pointer is returned.
///
/// @see    gmtime
///////////////////////////////

struct tm *gmtime_s(const time_t * restrict timer, struct tm * restrict result);

///////////////////////////////
/// The localtime_s function converts a time given as type @a time_t to local broken-down time.
///
/// @rcs A runtime-constraint violation occurs if
///     \li timer or result are a null pointer
///
/// @param [in]  timer  pointer to a value of type @time_t that shall be converted
/// @param [out] result the resulting time expressed as local broken-down time
///
/// @return On success @a result is returned.
///         Otherwise a NULL pointer is returned.
///
/// @see    localtime
///////////////////////////////

struct tm *localtime_s(const time_t * restrict timer, struct tm * restrict result);

SLIBC_END_DECLS

#endif //#if (!defined(__STDC_WANT_LIB_EXT1__) || (__STDC_WANT_LIB_EXT1__ != 0))

#endif
