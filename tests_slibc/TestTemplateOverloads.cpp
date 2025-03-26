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
#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
#include "slibc/string.h"
#include "slibc/stdio.h"
#include "TestTemplateOverloads.h"
#include "RuntimeConstraintViolation.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <iostream>
#include <fstream>

using namespace std;


CPPUNIT_TEST_SUITE_REGISTRATION (TestTemplateOverloads);


void TestTemplateOverloads::setUp()
{
	set_constraint_handler_s(cpp_constraint_handler_s);
}

void TestTemplateOverloads::tearDown()
{
}


void TestTemplateOverloads::test_strcpy_s()
{
	char buf[10];
	const char *input = "123456789ABCDEF";

	CPPUNIT_ASSERT_THROW(strcpy_s(buf, input), RuntimeConstraintViolation);
}

void TestTemplateOverloads::test_strncpy_s()
{
	char buf[10];
	const char *input = "123456789ABCDEF";


	CPPUNIT_ASSERT_THROW(strncpy_s(buf, input, 15), RuntimeConstraintViolation);

	CPPUNIT_ASSERT_EQUAL(0,strncpy_s(buf, input, 9));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(buf, "123456789"));
}

void TestTemplateOverloads::test_strcat_s()
{
	char s1[5];

	CPPUNIT_ASSERT_EQUAL(0, strcpy_s(s1, "12"));
	CPPUNIT_ASSERT_EQUAL(0, strcat_s(s1, "3"));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s1, "123"));

	CPPUNIT_ASSERT_EQUAL(0, strcat_s(s1, "4"));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s1, "1234"));

	CPPUNIT_ASSERT_THROW(strcat_s(s1, "4"), RuntimeConstraintViolation);
}

void TestTemplateOverloads::test_strncat_s()
{
	char s1[5];

	CPPUNIT_ASSERT_EQUAL(0, strcpy_s(s1, "12"));
	CPPUNIT_ASSERT_EQUAL(0, strncat_s(s1, "3", 1));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s1, "123"));

	CPPUNIT_ASSERT_EQUAL(0, strncat_s(s1, "4", 1));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s1, "1234"));

	CPPUNIT_ASSERT_THROW(strncat_s(s1, "4", 1), RuntimeConstraintViolation);
}

void TestTemplateOverloads::test_sprintf_s()
{
	char b[10];

	// sprintf_s function returns the number of characters written in the array
	CPPUNIT_ASSERT_EQUAL(9, sprintf_s(b, "%s%s", "test", "again"));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(b, "testagain"));

	CPPUNIT_ASSERT_THROW(sprintf_s(b, "%s%s", "test", "again12"), RuntimeConstraintViolation);
}

void TestTemplateOverloads::test_snprintf_s()
{
	char b[10];

	CPPUNIT_ASSERT_EQUAL(9, snprintf_s(b, "%s%s", "test", "again"));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(b, "testagain"));
}
