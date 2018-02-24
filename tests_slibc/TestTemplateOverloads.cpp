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
