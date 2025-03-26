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
