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
#define SLIBC_WANT_MKTEMP
#include "stdlib.h"

#include <iostream>
#include <sstream>
#include <exception>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "TestStdlib.h"
#include "RuntimeConstraintViolation.h"


using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION (TestStdlib);


void TestStdlib :: setUp (void)
{
	// SetUp your objects
	set_constraint_handler_s(cpp_constraint_handler_s);
}

void TestStdlib :: tearDown (void) 
{
	// Delete your objects
	
}

///////////////////////////////////////////////////////
/// Test: Strnlen_s
/// 
///////////////////////////////////////////////////////
void TestStdlib :: test_getenv_s (void)
{
	const char *name = "test";
	const char *invalue = "output";
	size_t len = 0;
	char outvalue[10];
	errno_t ret;

	setenv(name, invalue, 0);

	CPPUNIT_ASSERT_THROW(getenv_s(&len, outvalue, sizeof(outvalue), NULL), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(getenv_s(&len, outvalue, 0, name), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(getenv_s(&len, outvalue, RSIZE_MAX +1, name), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(getenv_s(&len, NULL, sizeof(outvalue), name), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(getenv_s(NULL, outvalue, sizeof(outvalue), NULL), RuntimeConstraintViolation);
	
	// a valid call with all parameters
	ret = getenv_s(&len, outvalue, sizeof(outvalue), name);
	CPPUNIT_ASSERT_EQUAL(0, ret);
	CPPUNIT_ASSERT_EQUAL(string(invalue), string(outvalue)); //0,strncmp(invalue,outvalue,7));
	CPPUNIT_ASSERT_EQUAL((size_t) 6, len);
	
	// we search for a non-existant environment variable
	ret = getenv_s(&len, outvalue, sizeof(outvalue), "bla");
	CPPUNIT_ASSERT(ret != 0);
	CPPUNIT_ASSERT_EQUAL((size_t) 0, len);
	CPPUNIT_ASSERT_EQUAL(true, outvalue[0] == '\0');
	CPPUNIT_ASSERT_EQUAL((size_t) 0, len);

	// a valid call with no length param
	ret = getenv_s(NULL, outvalue, sizeof(outvalue), name);
	CPPUNIT_ASSERT_EQUAL(0, ret);
	CPPUNIT_ASSERT_EQUAL(string(invalue), string(outvalue));

	// a valid call with no length param and testing for off-by-one
	ret = getenv_s(NULL, outvalue, 7, name);
	CPPUNIT_ASSERT_EQUAL(0, ret);
	CPPUNIT_ASSERT_EQUAL(string(invalue), string(outvalue));

	// buffer too small
	ret = getenv_s(NULL, outvalue, 6, name);
	CPPUNIT_ASSERT(ret != 0);
	CPPUNIT_ASSERT_EQUAL(true, outvalue[0] == '\0');

	// buffe too small but with len given
	ret = getenv_s(&len, outvalue, 6, name);
	CPPUNIT_ASSERT(ret != 0);
	CPPUNIT_ASSERT_EQUAL(true, outvalue[0] == '\0');
	CPPUNIT_ASSERT_EQUAL((size_t) 6, len);

	unsetenv(name);
}


int compare(const void *str1, const void *str2, void *context)
{
	return strcmp(*(const char**) str1, *(const char**) str2);
}

void TestStdlib :: test_qsort_s (void)
{
	const char *arr[] = {"dog", "pig", "horse", "cat", "human", "rat", "cow", "goat"};
	
	unsigned int i;
	const char *sorted[] = {"cat", "cow", "dog", "goat", "horse", "human", "pig", "rat"};

	CPPUNIT_ASSERT_THROW(qsort_s( &arr, RSIZE_MAX+1, sizeof( char * ), compare, NULL), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(qsort_s( &arr, sizeof(arr)/sizeof(arr[0]), RSIZE_MAX+1, compare, NULL ), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(qsort_s( (char*) NULL, 1, sizeof( char * ), compare, NULL ), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(qsort_s( &arr, sizeof(arr)/sizeof(arr[0]), sizeof( char * ), NULL, NULL ), RuntimeConstraintViolation);

	qsort_s( &arr, sizeof(arr)/sizeof(arr[0]), sizeof( char * ), compare, NULL );
	
	for( i = 0; i < sizeof(arr)/sizeof(arr[0]); ++i )
		CPPUNIT_ASSERT_EQUAL(strcmp(arr[i],sorted[i]),0);
	
}

void TestStdlib :: test_bsearch_s (void)
{
	const char *key = "cat";
	char *result;
	const char *arr[] = {"cat", "cow", "dog", "goat", "horse", "human", "pig", "rat"};


	CPPUNIT_ASSERT_THROW(bsearch_s(&key, arr, RSIZE_MAX+1, sizeof( char * ), compare, NULL), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(bsearch_s(&key, arr, sizeof(arr)/sizeof(arr[0]), RSIZE_MAX+1, compare, NULL), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(bsearch_s(NULL, arr, 1, sizeof( char * ), compare, NULL), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(bsearch_s(&key, (char *) NULL, 1, sizeof( char * ), compare, NULL), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(bsearch_s(&key, arr, 1, sizeof( char * ), (int (*)(const void*, const void*, void*))NULL, NULL), RuntimeConstraintViolation);

	result = *(char **)bsearch_s(&key, arr, sizeof(arr)/sizeof(arr[0]), sizeof( char * ), compare, NULL);
	CPPUNIT_ASSERT_EQUAL(0, strcmp(result,"cat"));
}

