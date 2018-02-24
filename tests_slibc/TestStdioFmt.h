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
#ifndef TEST_STDIOFMT_H
#define TEST_STDIOFMT_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>


class TestStdioFmt : public CPPUNIT_NS :: TestFixture
{
	CPPUNIT_TEST_SUITE (TestStdioFmt);


	CPPUNIT_TEST (test_sprintf_s_ShouldPass);		// does not test for format errors
	CPPUNIT_TEST (test_sprintf_s_ShouldThrowException);	// TODO: %n test is missing

	CPPUNIT_TEST (test_snprintf_s_ShouldPass);
	CPPUNIT_TEST (test_snprintf_s_ShouldThrowException);

	CPPUNIT_TEST (test_vsprintf_s_ShouldPass);
	CPPUNIT_TEST (test_vsprintf_s_ShouldThrowException);	// tests missing

	CPPUNIT_TEST (test_vsnprintf_s_ShouldPass);
	CPPUNIT_TEST (test_vsnprintf_s_ShouldThrowException);
	
	CPPUNIT_TEST (test_fscanf_s_ShouldPass);
	CPPUNIT_TEST (test_fscanf_s_ShouldAssignOne);
	CPPUNIT_TEST (test_fscanf_s_ShouldAssignZero);
	CPPUNIT_TEST (test_fscanf_s_ShouldThrowException);

	CPPUNIT_TEST (test_fprintf_s_ShouldPass);
	CPPUNIT_TEST (test_fprintf_s_ShouldThrowException);

	CPPUNIT_TEST (test_sscanf_s_ShouldPass);
	CPPUNIT_TEST (test_sscanf_s_ShouldThrowException);

	CPPUNIT_TEST (test_vfprintf_s_ShouldPass);
	CPPUNIT_TEST (test_vfprintf_s_ShouldThrowException);	// TODO: %n and %s test missing

//	CPPUNIT_TEST (test_vprintf_s_ShouldPass);		
	CPPUNIT_TEST (test_vprintf_s_ShouldThrowException);	// TODO: %n and %s test missing


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

	void test_sprintf_s_ShouldPass (void);
	void test_sprintf_s_ShouldThrowException (void);
	void test_snprintf_s_ShouldPass (void);
	void test_snprintf_s_ShouldThrowException (void);

	void test_vsprintf_s_ShouldPass (void);
	void test_vsprintf_s_ShouldThrowException (void);

	void test_vsnprintf_s_ShouldPass (void);
	void test_vsnprintf_s_ShouldThrowException (void);
		
	void test_fscanf_s_ShouldPass (void);
	void test_fscanf_s_ShouldAssignOne (void);
	void test_fscanf_s_ShouldAssignZero (void);
	void test_fscanf_s_ShouldThrowException (void);

	void test_scanf_s_ShouldPass (void);

	void test_fprintf_s_ShouldPass (void);
	void test_fprintf_s_ShouldThrowException (void);

	void test_sscanf_s_ShouldPass (void);
	void test_sscanf_s_ShouldThrowException (void);

	void test_vfprintf_s_ShouldPass (void);
	void test_vfprintf_s_ShouldThrowException (void);

	void test_vprintf_s_ShouldPass (void);
	void test_vprintf_s_ShouldThrowException (void);

};

#endif
