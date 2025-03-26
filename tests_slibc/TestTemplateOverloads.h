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
#ifndef TESTMSCANF_S_H
#define TESTMSCANF_S_H

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>


class TestTemplateOverloads : public CPPUNIT_NS :: TestFixture
{
public:
	void setUp ();
	void tearDown ();

protected:
	void test_strcpy_s();
	void test_strncpy_s();
	void test_strcat_s();
	void test_strncat_s();
	void test_sprintf_s();
	void test_snprintf_s();

private:
	CPPUNIT_TEST_SUITE (TestTemplateOverloads);

	CPPUNIT_TEST(test_strcpy_s);
	CPPUNIT_TEST(test_strncpy_s);
	CPPUNIT_TEST(test_strcat_s);
	CPPUNIT_TEST(test_strncat_s);
	CPPUNIT_TEST(test_sprintf_s);
	CPPUNIT_TEST(test_snprintf_s);

	CPPUNIT_TEST_SUITE_END ();
};

#endif
