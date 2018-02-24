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
#include "slibc/stdio.h"
#include <iostream>
#include <sstream>
#include <exception>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "TestStdioFmt.h"
#include "RuntimeConstraintViolation.h"


using namespace std;


CPPUNIT_TEST_SUITE_REGISTRATION (TestStdioFmt);


void TestStdioFmt :: setUp (void)
{
	// SetUp your objects
	set_constraint_handler_s(cpp_constraint_handler_s);
}

void TestStdioFmt :: tearDown (void) 
{
	// Delete your objects
	
}	

///////////////////////////////////////////////////////
/// Test: Sprintf_s
///
///////////////////////////////////////////////////////
void TestStdioFmt :: test_sprintf_s_ShouldPass (void)
{
	char b[10];

	// sprintf_s function returns the number of characters written in the array
	CPPUNIT_ASSERT_EQUAL(9, sprintf_s(b, 10, "%s%s", "test", "again"));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(b, "testagain"));

}

///////////////////////////////////////////////////////
/// Test: Sprintf_s
///
///////////////////////////////////////////////////////
void TestStdioFmt :: test_sprintf_s_ShouldThrowException (void)
{
	int n = 0;
	char s[10];
	memset(s, 0, sizeof(s));
	
	CPPUNIT_ASSERT_THROW(sprintf_s(s, 10, "%s%s", "testadfsf", "again"), RuntimeConstraintViolation);

	// Neither s nor format shall be a null pointer
	CPPUNIT_ASSERT_THROW(sprintf_s(NULL, 10, "%s%s", "test2", "again"), RuntimeConstraintViolation);
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wformat-extra-args"
	CPPUNIT_ASSERT_THROW(sprintf_s(s, 10, NULL, "test2", "again"), RuntimeConstraintViolation);
//#pragma GCC diagnostic pop

	// n shall neither equal zero
	CPPUNIT_ASSERT_THROW(sprintf_s(s, 0, "%s%s", "test", "again"), RuntimeConstraintViolation);

	// The number of characters (including the trailing null) required for the
	// result to be written to the array pointed to by s shall not be greater than n
	CPPUNIT_ASSERT_THROW(sprintf_s(s, 5, "%s%s", "test", "again"), RuntimeConstraintViolation);

	// The %n specifier (modified or not by flags, field width, or precision) shall not appear in the
	// string pointed to by format
	CPPUNIT_ASSERT_THROW(sprintf_s(s, 10, "%s%n", "test", &n), RuntimeConstraintViolation);


	// Any argument to sprintf_s corresponding to a %s
	// specifier shall not be a null pointer
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wformat"
	CPPUNIT_ASSERT_THROW(sprintf_s(s, 10, "%s%s", (char *) NULL, "again"), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(sprintf_s(s, 10, "%s%s", "test", (char *) NULL), RuntimeConstraintViolation);
//#pragma GCC diagnostic pop

	// ... then sprintf_s sets s1[0] to the null character.
	CPPUNIT_ASSERT_EQUAL(0, (int)s[0]);

	CPPUNIT_ASSERT_THROW(sprintf_s(s, sizeof(s), "%s", s), RuntimeConstraintViolation);
	char *p = s;
	CPPUNIT_ASSERT_THROW(sprintf_s(s, sizeof(s), "%s", p), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(sprintf_s(s, sizeof(s), "%s", p + 9), RuntimeConstraintViolation);
}

///////////////////////////////////////////////////////
/// Test: Snprintf_s
///////////////////////////////////////////////////////
void TestStdioFmt :: test_snprintf_s_ShouldPass (void)
{
	char s[10];

	CPPUNIT_ASSERT_EQUAL(10, snprintf_s(s, 10, "%s%s", "test2", "again"));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s, "test2agai"));

	// snprintf_s function returns the number of characters written in the array
	CPPUNIT_ASSERT_EQUAL(9, snprintf_s(s, 10, "%s%s", "test", "again"));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s, "testagain"));

	CPPUNIT_ASSERT_EQUAL(9, snprintf_s(s, 3, "%s%s", "test", "again"));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s, "te"));
}

///////////////////////////////////////////////////////
/// Test: Snprintf_s
///
///////////////////////////////////////////////////////
void TestStdioFmt :: test_snprintf_s_ShouldThrowException (void)
{
	char s[10];

	char *n = (char *) 0;
	CPPUNIT_ASSERT_THROW(snprintf_s(s, 10, "%s%s", n, "again"), RuntimeConstraintViolation);

//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wformat"
	CPPUNIT_ASSERT_THROW(snprintf_s(s, 10, "%s%s%n", n, "again"), RuntimeConstraintViolation);
//#pragma GCC diagnostic pop

	int i;
	CPPUNIT_ASSERT_THROW(snprintf_s(s, 10, "%s%s%n", n, "again", &i), RuntimeConstraintViolation);

	// Neither s nor format shall be a null pointer
	CPPUNIT_ASSERT_THROW(snprintf_s(NULL, 10, "%s%s", "test2", "again"), RuntimeConstraintViolation);
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wformat-extra-args"
	CPPUNIT_ASSERT_THROW(snprintf_s(s, 10, NULL, "test2", "again"), RuntimeConstraintViolation);
//#pragma GCC diagnostic pop

	// n shall neither equal zero
	CPPUNIT_ASSERT_THROW(snprintf_s(s, 0, "%s%s", "test", "again"), RuntimeConstraintViolation);

	// The %n specifier (modified or not by flags, field width, or precision) shall not appear in the
	// string pointed to by format
	int in = 1;
	CPPUNIT_ASSERT_THROW(snprintf_s(s, 10, "%s%n", "test", &in), RuntimeConstraintViolation);

	// Any argument to sprintf_s corresponding to a %s
	// specifier shall not be a null pointer
//#pragma GCC diagnostic push
//#pragma GCC diagnostic ignored "-Wformat"
	CPPUNIT_ASSERT_THROW(snprintf_s(s, 10, "%s%s", (char *) NULL, "again"), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(snprintf_s(s, 10, "%s%s", "test", (char *) NULL), RuntimeConstraintViolation);
//#pragma GCC diagnostic pop

	// ... then sprintf_s sets s1[0] to the null character.
	CPPUNIT_ASSERT_EQUAL(0, (int)s[0]);
}


///////////////////////////////////////////////////////
/// Test: Vsprintf_s
///////////////////////////////////////////////////////
void vsprintf_s_ShouldPass (const char * format, ... )
{
	va_list args;
	char buffer[10];
	int len = 10;		// fixed length for the test

	va_start( args, format );

	// the vsprintf_s function returns the number of characters written in the array,
	// not counting the terminating null character
	CPPUNIT_ASSERT_EQUAL(9, vsprintf_s( buffer, len, format, args ));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(buffer, "123 < 456"));
}

void TestStdioFmt :: test_vsprintf_s_ShouldPass (void)
{
	vsprintf_s_ShouldPass( "%d %c %d", 123, '<', 456 );
}

///////////////////////////////////////////////////////
/// Test: Vsprintf_s
///////////////////////////////////////////////////////
void vsprintf_s_ShouldFail (const char * format, ... )
{
	va_list args;
	int len = 10;		// fixed length for the test
	char buffer[10];
	const char * restrict format_fail = 0;

	va_start( args, format );

	CPPUNIT_ASSERT_THROW(vsprintf_s( NULL, len, format, args ), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(vsprintf_s( buffer, 0, format, args ), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(vsprintf_s( buffer, len, format_fail, args ), RuntimeConstraintViolation);
}


void TestStdioFmt :: test_vsprintf_s_ShouldThrowException (void)
{
	vsprintf_s_ShouldFail( "%d %c %d %n", 123, '<', 456 );
}


void vsnprintf_s_ShouldPass(const char* formatstring, ...) 
{
	int nSize = 0;
	char buff[10];
	memset(buff, 0, sizeof(buff));

	va_list args;
	va_start(args, formatstring);

	nSize = vsnprintf_s( buff, sizeof(buff), formatstring, args);

	va_end(args);

	CPPUNIT_ASSERT_EQUAL(nSize, 12);
}

void TestStdioFmt :: test_vsnprintf_s_ShouldPass (void)
{
	vsnprintf_s_ShouldPass("%s %s", "Hi", "there!!!!");
}

///////////////////////////////////////////////////////
/// Test: Vsnprintf_s
/// 
///////////////////////////////////////////////////////
void vsnprintf_s_ShouldFail (const char * format, ... )
{
	va_list args;
	int len = 10, len_fail=0;		
	char buffer[10];

	va_start( args, format );

	CPPUNIT_ASSERT_THROW(vsnprintf_s(NULL, len, format, args ), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(vsnprintf_s( buffer, len_fail, format, args ), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(vsnprintf_s( buffer, len, NULL, args ), RuntimeConstraintViolation);

	// The %n specifier (modified or not by flags, field width, or precision) shall not appear in the
	// string pointed to by format
	CPPUNIT_ASSERT_THROW(vsnprintf_s(buffer, len, format, args), RuntimeConstraintViolation);
	va_end(args);
}

void TestStdioFmt :: test_vsnprintf_s_ShouldThrowException (void)
{
	vsnprintf_s_ShouldFail( "%d %c %d %n", 123, '<', 456 );
}

///////////////////////////////////////////////////////
/// Test: fscanf_s
///
///////////////////////////////////////////////////////
void TestStdioFmt :: test_fscanf_s_ShouldPass (void)
{
	int n, i;
	float x;
	char name[50];
	char input[] = "25 54.32E-1 thompson";	// 25 54.32E-1 thompson
	int result;

	FILE *stream;
	stream = fmemopen (input, strlen(input), "r");

	n=fscanf_s(stream, "%d%f%s", &i, &x, name, (rsize_t) 50);
	fclose(stream);


	CPPUNIT_ASSERT_EQUAL(3, n);

	CPPUNIT_ASSERT_EQUAL(25, i);
	CPPUNIT_ASSERT_EQUAL((float) 5.432, x);
	result = strncmp(name, "thompson", 9);
	CPPUNIT_ASSERT_EQUAL(0, result);
	
	//loooooong test
	int i1, i2, i3;
	float x1, x2;
	double d;
	char bla[7], t[5], name1[20];

	char w = '\0'; 
	char input1[] = "25 54.32E-1 thompson c blabla 100 7.8 test 10 30.1E-1";	// 25 54.32E-1 thompson

	FILE *stream1;
	stream1 = fmemopen (input1, strlen(input1), "r");

	n=fscanf_s(stream1, "%d %f %s %c %s %d %lf %s %d %f", &i1, &x1, name1, (rsize_t) 20,
			   &w, sizeof(w), bla, sizeof(bla), &i2, &d, t, sizeof(t), &i3, &x2);

	CPPUNIT_ASSERT_EQUAL(25, i1);
	CPPUNIT_ASSERT_EQUAL((float) 5.432, x1);

	result = strncmp(name1, "thompson", 9);
	CPPUNIT_ASSERT_EQUAL(0, result);

	CPPUNIT_ASSERT_EQUAL(true, w == 'c');

	result = strncmp(bla, "blabla", 7);
	CPPUNIT_ASSERT_EQUAL(0, result);

	CPPUNIT_ASSERT_EQUAL(100, i2);
	CPPUNIT_ASSERT_EQUAL(7.8, d);

	result = strncmp(t, "test", 5);
	CPPUNIT_ASSERT_EQUAL(0, result);

	CPPUNIT_ASSERT_EQUAL(10, i3);
	CPPUNIT_ASSERT_EQUAL((float) 3.01, x2);
	fclose(stream1);
	
}

///////////////////////////////////////////////////////
/// Test: fscanf_s
///////////////////////////////////////////////////////
void TestStdioFmt :: test_fscanf_s_ShouldAssignZero (void)
{
	char name[5];
	char input[] = "thompson";	// thompson
	int n = -1;

	FILE *stream;
	stream = fmemopen (input, strlen(input), "r");

	n=fscanf_s(stream, "%s", name, sizeof(name));
	fclose(stream);

	CPPUNIT_ASSERT_EQUAL(0, n);	
}

///////////////////////////////////////////////////////
/// Test: fscanf_s
///
/// Another test for fscanf_s.
/// We parse strings, chars and pointers.
///
///////////////////////////////////////////////////////
void TestStdioFmt :: test_fscanf_s_ShouldAssignOne (void)
{
	int n, i;
	char input[] = "String1 stringzwei 12c"; //0x12345678
	char string1[8], stringzwei[]="Stringzwei", w='0';

	FILE *stream;
	stream = fmemopen (input, strlen(input), "r");
	
	n=fscanf_s(stream, "%s%s%d%c", string1, sizeof(string1), stringzwei, sizeof(stringzwei), &i, &w, 1);

	fclose(stream);

	CPPUNIT_ASSERT_EQUAL(true, w == 'c');
	CPPUNIT_ASSERT_EQUAL(0, strcmp(stringzwei, "stringzwei"));
	CPPUNIT_ASSERT_EQUAL(12, i);
	CPPUNIT_ASSERT_EQUAL(4, n);
}

///////////////////////////////////////////////////////
/// Test: fscanf_s
///
///////////////////////////////////////////////////////
void TestStdioFmt :: test_fscanf_s_ShouldThrowException (void)
{
  
	char input[] = "23 234 34 24";
	char s[5];

	FILE *stream;
	stream = fmemopen (input, strlen(input), "r");


	// Neither stream nor format shall be a null pointer
	CPPUNIT_ASSERT_THROW(fscanf_s(stream, NULL, s, sizeof s), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(fscanf_s(NULL, "%s", s, sizeof s), RuntimeConstraintViolation);
	// Any argument indirected though in order to store converted input shall not be a null pointer
	CPPUNIT_ASSERT_THROW(fscanf_s(stream, "%s", (char*)0, sizeof s), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(fscanf_s(stream, "%d", (int*)0), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(fscanf_s(stream, "%f", (float*)0), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(fscanf_s(stream, "%d", (double*)0), RuntimeConstraintViolation);
	fclose(stream);
}


///////////////////////////////////////////////////////
/// Test: fprintf_s
///
/// The fprintf_s function returns the number of characters transmitted, or a negative
/// value if an output error, encoding error, or runtime-constraint violation occurred.
///
///////////////////////////////////////////////////////
void TestStdioFmt :: test_fprintf_s_ShouldPass (void)
{

	char input[26];
	char string_[] = "Test";
	float float_ = 1.1;

	FILE *stream;
	stream = fmemopen (input, 26, "w");

	CPPUNIT_ASSERT_EQUAL(25, fprintf_s(stream, "Das ist ein %f %s", float_, string_));

	fclose(stream);

	CPPUNIT_ASSERT_EQUAL(0, strcmp(input, "Das ist ein 1.100000 Test"));

}

///////////////////////////////////////////////////////
/// Test: fprintf_s
///
///////////////////////////////////////////////////////
void TestStdioFmt :: test_fprintf_s_ShouldThrowException (void)
{

	char input[26];
	char s[5];
	FILE *stream;
	stream = fmemopen (input, 26, "w");


	// Neither stream nor format shall be a null pointer
	CPPUNIT_ASSERT_THROW(fprintf_s(stream, NULL, s, sizeof s), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(fprintf_s(NULL, "%s", s, sizeof s), RuntimeConstraintViolation);
	// Any argument to fprintf_s corresponding to a %s specifier shall not be a null pointer
	CPPUNIT_ASSERT_THROW(fprintf_s(stream, "%s", (char*)0, sizeof s), RuntimeConstraintViolation);
	// The %n specifier (modified or not by flags, field width, or precision)
	// shall not appear in the string pointed to by format
	CPPUNIT_ASSERT_THROW(fprintf_s(stream, "%s%n", s), RuntimeConstraintViolation);
	fclose(stream);
}

///////////////////////////////////////////////////////
/// Test: sscanf_s
///
///////////////////////////////////////////////////////
void TestStdioFmt :: test_sscanf_s_ShouldPass (void)
{

	float x=0;
	char name[9];
	char string[] = "25 54.32E-1 thompson";	// 25 54.32E-1 thompson
	int result=0, i=0;

	CPPUNIT_ASSERT_EQUAL(3, sscanf_s(string, "%d%f%s", &i, &x, name, (rsize_t) 50));

	CPPUNIT_ASSERT_EQUAL(25, i);
	CPPUNIT_ASSERT_EQUAL((float) 5.432, x);
	result = strncmp(name, "thompson", 9);
	CPPUNIT_ASSERT_EQUAL(0, result);
	
	//loooooong test
	int i1, i2, i3;
	float x1, x2;
	double d;
	char bla[7], t[5], name1[50];

	char w='0';
	char input1[] = "25 54.32E-1 thompson c blabla 100 7.8 test 10 30.1E-1";	// 25 54.32E-1 thompson


	CPPUNIT_ASSERT_EQUAL(10, sscanf_s(input1, "%d %f %s %c %s %d %lf %s %d %f", &i1, &x1, name1, (rsize_t) 50,
									  &w, 1, bla, sizeof(bla), &i2, &d, t, sizeof(t), &i3, &x2));

	CPPUNIT_ASSERT_EQUAL(25, i1);
	CPPUNIT_ASSERT_EQUAL((float) 5.432, x1);

	result = strncmp(name1, "thompson", 9);
	CPPUNIT_ASSERT_EQUAL(0, result);

	CPPUNIT_ASSERT_EQUAL(true, w == 'c');

	result = strncmp(bla, "blabla", 7);
	CPPUNIT_ASSERT_EQUAL(0, result);

	CPPUNIT_ASSERT_EQUAL(100, i2);
	CPPUNIT_ASSERT_EQUAL(7.8, d);

	result = strncmp(t, "test", 5);
	CPPUNIT_ASSERT_EQUAL(0, result);

	CPPUNIT_ASSERT_EQUAL(10, i3);
	CPPUNIT_ASSERT_EQUAL((float) 3.01, x2);

}

///////////////////////////////////////////////////////
/// Test: sscanf_s
///
///////////////////////////////////////////////////////
void TestStdioFmt :: test_sscanf_s_ShouldThrowException (void)
{
	char string[] = "23 234 34 24";
	char s[5];

	// Neither stream nor format shall be a null pointer
	CPPUNIT_ASSERT_THROW(sscanf_s(string, NULL, s, sizeof s), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(sscanf_s(NULL, "%s", s, sizeof s), RuntimeConstraintViolation);
	// Any argument indirected though in order to store converted input shall not be a null pointer
	CPPUNIT_ASSERT_THROW(sscanf_s(string, "%s", (char*)0, sizeof s), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(sscanf_s(string, "%d", (int*)0), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(sscanf_s(string, "%f", (float*)0), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(sscanf_s(string, "%d", (double*)0), RuntimeConstraintViolation);
}

///////////////////////////////////////////////////////
/// Test: vfprintf_s
///
/// The vfprintf_s function returns the number of characters transmitted, or a negative
/// value if an output error, encoding error, or runtime-constraint violation occurred.
///
///////////////////////////////////////////////////////
void vfprintf_s_ShouldPass (const char * format, ... )
{
	va_list args;
	char buffer[10];

	va_start( args, format );

	FILE *stream;
	stream = fmemopen (buffer, 10, "w");

	// The vfprintf_s function returns the number of characters transmitted
	CPPUNIT_ASSERT_EQUAL(9, vfprintf_s( stream, format, args ));

	fclose(stream);

	CPPUNIT_ASSERT_EQUAL(0, strcmp(buffer, "123 < 456"));
}

void TestStdioFmt :: test_vfprintf_s_ShouldPass (void)
{
	vfprintf_s_ShouldPass( "%d %c %d", 123, '<', 456 );
}

///////////////////////////////////////////////////////
/// Test: vfprintf_s
///
///////////////////////////////////////////////////////
void vfprintf_s_ShouldFail (const char * format, ... )
{
	va_list args;
	char buffer[10];

	va_start( args, format );

	FILE *stream;
	stream = fmemopen (buffer, 10, "w");

	CPPUNIT_ASSERT_THROW(vfprintf_s( NULL, format, args ), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(vfprintf_s( stream, NULL, args ), RuntimeConstraintViolation);

	fclose(stream);
}

void TestStdioFmt :: test_vfprintf_s_ShouldThrowException (void)
{
	vfprintf_s_ShouldFail( "%d %c %d", 123, '<', 456 );
}

///////////////////////////////////////////////////////
/// Test: vprintf_s
///
/// The vprintf_s function returns the number of characters transmitted, or a negative
/// value if an output error, encoding error, or runtime-constraint violation occurred.
///
///////////////////////////////////////////////////////
void vprintf_s_ShouldPass (const char * format, ... )
{
	va_list args;
	va_start( args, format );

	vprintf_s(format, args);

	// The vfprintf_s function returns the number of characters transmitted
	CPPUNIT_ASSERT_EQUAL(9, printf( format, args ));

	//CPPUNIT_ASSERT_EQUAL(0, strcmp(buffer, "123 < 456"));
}

void TestStdioFmt :: test_vprintf_s_ShouldPass (void)
{
	vprintf_s_ShouldPass( "%d %c %d", 123, '<', 456 );
//	char string[] = "test";
//	int integer = 10;

	//vprintf_s_ShouldPass( "\n! %d %s", integer, string );
}

///////////////////////////////////////////////////////
/// Test: vprintf_s
///
///////////////////////////////////////////////////////
void vprintf_s_ShouldFail (const char * format, ... )
{
	va_list args;

	va_start( args, format );

	// format shall not be a null pointer
	CPPUNIT_ASSERT_THROW(vprintf_s( NULL, args ), RuntimeConstraintViolation);
}

void TestStdioFmt :: test_vprintf_s_ShouldThrowException (void)
{
	vprintf_s_ShouldFail( "%d %c %d", 123, '<', 456 );
}


