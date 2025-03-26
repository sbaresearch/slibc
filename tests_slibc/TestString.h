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
