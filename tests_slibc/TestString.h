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
#ifndef TEST_STRING_H
#define TEST_STRING_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

class TestString : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (TestString);


	CPPUNIT_TEST (test_strnlen_s_LengthCorrect);

	CPPUNIT_TEST (test_strcpy_s_ShouldCopyCorrect);
	CPPUNIT_TEST (test_strcpy_s_ShouldThrowException);

	CPPUNIT_TEST (test_strncpy_s_ShouldCopyCorrect);	
	CPPUNIT_TEST (test_strncpy_s_ShouldThrowException);

	CPPUNIT_TEST (test_strcat_s_ShouldAppendCorrect);	
	CPPUNIT_TEST (test_strcat_s_ShouldThrowException);	

	CPPUNIT_TEST (test_strncat_s_ShouldAppendCorrect);	
	CPPUNIT_TEST (test_strncat_s_ShouldThrowException);	

	CPPUNIT_TEST(test_gets_s);
	CPPUNIT_TEST(test_memcpy_s);
	CPPUNIT_TEST(test_strerror_s);
	CPPUNIT_TEST(test_strerrorlen_s);
	CPPUNIT_TEST(test_memmove_s);
	CPPUNIT_TEST(test_strtok_s);
	CPPUNIT_TEST(test_fopen_s);
	CPPUNIT_TEST(test_freopen_s);

	CPPUNIT_TEST_SUITE_END ();

public:
	void setUp (void);
	void tearDown (void);

protected:
	void test_strnlen_s_LengthCorrect (void);

	void test_strcpy_s_ShouldCopyCorrect (void);
	void test_strcpy_s_ShouldThrowException (void);

	void test_strncpy_s_ShouldCopyCorrect (void);
	void test_strncpy_s_ShouldThrowException (void);

	void test_strcat_s_ShouldAppendCorrect (void);
	void test_strcat_s_ShouldThrowException (void);

	void test_strncat_s_ShouldAppendCorrect (void);
	void test_strncat_s_ShouldThrowException (void);
		
	void test_gets_s (void);
	void test_memcpy_s (void);

	void test_strerror_s (void);
	void test_strerrorlen_s (void);
	void test_memmove_s (void);
	void test_strtok_s (void);
	void test_fopen_s (void);
	void test_freopen_s (void);
};

#endif
