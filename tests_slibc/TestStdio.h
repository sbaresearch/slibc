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
#ifndef TEST_STDIO_H
#define TEST_STDIO_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>


class TestStdio : public CPPUNIT_NS :: TestFixture
{
public:
	void setUp ();
	void tearDown ();

protected:

	void test_slibc_set_get_temp_dir (void);
	void test_tmpfile_s (void);
	void test_tmpnam_s (void);
	void test_mkstemp_s (void);
	void test_mktemp_s (void);

private:
	CPPUNIT_TEST_SUITE (TestStdio);

	CPPUNIT_TEST(test_slibc_set_get_temp_dir);
	CPPUNIT_TEST(test_tmpfile_s);
	CPPUNIT_TEST(test_tmpnam_s);
	CPPUNIT_TEST(test_mkstemp_s);
	CPPUNIT_TEST(test_mktemp_s);

	CPPUNIT_TEST_SUITE_END ();
};

#endif
