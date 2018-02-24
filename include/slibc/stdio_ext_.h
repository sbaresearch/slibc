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
/// Contains _s contains that are not part of the TR 24731-1.
///////////////////////////////////////////////////////
#ifndef  SLIBC_STDIO_EXT_H
#define  SLIBC_STDIO_EXT_H

#include "./stdio.h"

SLIBC_BEGIN_DECLS

///////////////////////////////////////////////////////////////////////////////
///   This function sets the temporary directory to a user-specified directory.
///
///   @remark This function is an extension of the ISO C standard and does not normally
///   exist.
///
///   This functions allows one to change the directory where temporary
///   files created by the functions tmpfile_s and tmpnam_s are created.
///
///   The Cert Secure Programming Standard for C recommends to not create temporary files
///   in shared directories. Instead, files should be stored in a directory that
///   is only writeable by the user. Since /tmp is normally writable by everyone all directories
///   and files under /tmp/ are considered insecure. You can use slibc_set_tmp_dir to set
///   a different temporary directory for use by the functions tmpnam_s and tmpfile_s.
///   If your program runs with elevated privileges and
///   needs to be secure against local attackers, consider following the Cert's recommendation.
///   
///   See https://www.securecoding.cert.org/confluence/display/seccode/FIO43-C.+Do+not+create+temporary+files+in+shared+directories
///
///   @rcs A runtime-constraint violation occurs if
///    \li tmp_dir is a NULL pointer
///    \li tmp_dir is longer than PATH_MAX
///
///   @param [in] tmp_dir  the new temporary directory
///
///   @return 0 if the temporary directory was set successfully
///           A non-zero value is returned otherwise
///
///   @see    slibc_get_tmp_dir, tmpfile_s, tmpnam_s
///////////////////////////////////////////////////////////////////////////////
errno_t slibc_set_tmp_dir(const char *tmp_dir);


///////////////////////////////////////////////////////////////////////////////
///   This function returns the temporary directory used by other slibc-functions.
///
///   @remark This function is an extension of the ISO C standard and does not normally
///   exist.
///
///   This functions allows one to query the directory where temporary
///   files created by the functions tmpfile_s and tmpnam_s are created.
///
///   @rcs A runtime-constraint violation occurs if
///    \li tmp_dir is a NULL pointer
///    \li tmp_dir is longer than PATH_MAX
///
///   @param [out] tmp_dir       output buffer for holgin the temporary directory
///   @param [in]  tmp_dir_size  the size of the output buffer
///
///   @return 0 if the temporary directory was retrieved successfully
///           A non-zero value is returned otherwise
///
///   @see    slibc_set_tmp_dir, tmpfile_s, tmpnam_s
///////////////////////////////////////////////////////////////////////////////
errno_t slibc_get_tmp_dir(char *tmp_dir, rsize_t tmp_dir_size);


///////////////////////////////
///
///  The mkstemp_s function creates a file with temp as namebase. On succes this function writes the filedescriptor to fd. A string
///  of the form baseXXXXXX is expected as temp. The X are replaced by a generated string.
///
///  @rcs
///  @li temp must not be a NULL pointer
///  @li sizeInChars must be bigger than or equal to the length of the given string
///  @li the X must be at the end of the template
///
///  @param temp
///  @param fd
///  @param sizeInChars
///
///  @return The mkstemp_s function returns 0 on success, -1 on failure or EINVAL if a runtime constraint is violated
///
///  @see mkstemp
///////////////////////////////

errno_t mkstemp_s(char *temp, int *fd, size_t sizeInChars);

///////////////////////////////
///
///  The mktemp_s function generates a valid filename with temp as base and writes this filename to temp. A string of the form baseXXXXXX is
///  expected as temp. The X are replaced by a generated string.
///
///  @rcs
///  @li temp must not be a NULL pointer
///  @li sizeInChars must be bigger than or equal to the length of the given string
///  @li the X must be at the end of the template
///
///  @param temp
///  @param sizeInChars
///
///  @return The mktemp_s function returns 0 on success, -1 on failure or EINVAL if a runtime constraint is violated
///
///  @see mktemp
///////////////////////////////

errno_t mktemp_s(char *temp, size_t sizeInChars);

SLIBC_END_DECLS

#endif
