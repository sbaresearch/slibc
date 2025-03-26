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
