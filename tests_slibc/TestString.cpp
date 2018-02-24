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
//#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES
#define SLIBC_WANT_TEMPLATES
#include "slibc/string.h"

#include <iostream>
#include <sstream>
#include <exception>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "TestString.h"
#include "RuntimeConstraintViolation.h"


using namespace std;


CPPUNIT_TEST_SUITE_REGISTRATION (TestString);

const char * s2 = "123";

void TestString :: setUp (void)
{
	// SetUp your objects
	set_constraint_handler_s(cpp_constraint_handler_s);
}

void TestString :: tearDown (void) 
{
	// Delete your objects
	
}

///////////////////////////////////////////////////////
/// Test: Strnlen_s
/// 
///////////////////////////////////////////////////////
void TestString :: test_strnlen_s_LengthCorrect (void)
{
	const char *s1 = "123";

	// If s is a null pointer, then the strnlen_s function returns zero.
	CPPUNIT_ASSERT_EQUAL((size_t) 0, strnlen_s(NULL, 2));

	CPPUNIT_ASSERT_EQUAL((size_t) 2, strnlen_s(s1, 2));
	CPPUNIT_ASSERT_EQUAL((size_t) 3, strnlen_s(s1, 4));
	CPPUNIT_ASSERT_EQUAL((size_t) 3, strnlen_s(s1, 3));
}

///////////////////////////////////////////////////////
/// Test: Strcpy_s
/// 
/// The strcpy_s function returns zero if there was no runtime-constraint violation.
/// Otherwise, a non-zero value is returned.
///
///////////////////////////////////////////////////////
void TestString :: test_strcpy_s_ShouldCopyCorrect (void)
{
	char s1[5];
	s2 = "1234";


	CPPUNIT_ASSERT_EQUAL(0, strcpy_s(s1, 5, s2));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s1, s2));
}

///////////////////////////////////////////////////////
/// Test: Strcpy_s
///
///////////////////////////////////////////////////////
void TestString :: test_strcpy_s_ShouldThrowException (void)
{
	char s1[5];
	s2 = "1234";

	// Neither s1 nor s2 shall be a null pointer
	CPPUNIT_ASSERT_THROW(strcpy_s(NULL, 5, s2), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(strcpy_s(s1, 5, NULL), RuntimeConstraintViolation);
	// s1max shall not equal zero
	CPPUNIT_ASSERT_THROW(strcpy_s(s1, 0, s2), RuntimeConstraintViolation);
	// s1max shall be greater than strnlen_s(s2, s1max)
	CPPUNIT_ASSERT_THROW(strcpy_s(s1, strnlen_s(s2, strlen(s2)), s2), RuntimeConstraintViolation);

	// Copying shall not take place between objects that overlap
	CPPUNIT_ASSERT_THROW(strcpy_s(s1, sizeof(s1), s1), RuntimeConstraintViolation);
	// ... then strcpy_s sets s1[0] to the null character.
	CPPUNIT_ASSERT_EQUAL(0, (int)s1[0]);

	strcpy_s(s1, sizeof(s1), "ABCD");
	CPPUNIT_ASSERT_THROW(strcpy_s(s1, sizeof(s1), s1+2), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_EQUAL(0, (int)s1[0]);

	strcpy_s(s1, sizeof(s1), "ABCD");
	CPPUNIT_ASSERT_THROW(strcpy_s(s1+2, sizeof(s1)-2, s1), RuntimeConstraintViolation);

	// test overlapping
	// This has to cause a runtime constraint violation
	// because the arguments overlap.
	strcpy_s(s1, sizeof(s1), "ABCD");
	CPPUNIT_ASSERT_THROW(strcpy_s(s1+1, 2, s1), 
			     RuntimeConstraintViolation);
}

///////////////////////////////////////////////////////
/// Test: Strncpy_s
/// 
/// The strncpy_s function returns zero if there was no runtime-constraint violation.
/// Otherwise, a non-zero value is returned.
///
///////////////////////////////////////////////////////
void TestString :: test_strncpy_s_ShouldCopyCorrect (void)
{
	char s1[5];
	s2 = "1234";

	char src1[100] = "hello";
	char src2[7] = {'g', 'o', 'o', 'd', 'b', 'y', 'e'};
	char dst1[6], dst3[5];

	CPPUNIT_ASSERT_EQUAL(0, strncpy_s(s1, 5, s2, 1));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s1, "1"));

	CPPUNIT_ASSERT_EQUAL(0, strncpy_s(s1, 3, s2, 2));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s1, "12"));

	s2 = "12345";
	CPPUNIT_ASSERT_EQUAL(0, strncpy_s(s1, sizeof(s1), s2, sizeof(s1)-1));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s1, "1234"));

	CPPUNIT_ASSERT_EQUAL(0, strncpy_s(s1, sizeof(s1), "test", 0));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s1, ""));


	// EXAMPLE 1:
	// The strncpy_s function can be used to copy a string without the danger that the result
	// will not be null terminated or that characters will be written past the end of the destination array.

	CPPUNIT_ASSERT_EQUAL(0, strncpy_s(dst1, 6, src1, 100));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(dst1, "hello"));

	CPPUNIT_ASSERT_EQUAL(0, strncpy_s(dst3, 5, src2, 4));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(dst3, "good"));
}

///////////////////////////////////////////////////////
/// Test: Strncpy_s
///
///////////////////////////////////////////////////////
void TestString :: test_strncpy_s_ShouldThrowException (void)
{
	s2 = "1234";
	char s1[5];

	strncpy_s(s1, 5, s2, 1);

	// Neither s1 nor s2 shall be a null pointer
	CPPUNIT_ASSERT_THROW(strncpy_s(NULL, 5, s2, 5), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(strncpy_s(s1, 5, NULL, 5), RuntimeConstraintViolation);
	// s1max shall not equal zero
	CPPUNIT_ASSERT_THROW(strncpy_s(s1, 0, s2, 1), RuntimeConstraintViolation);
	// If n is not less than s1max, then s1max shall be greater than strnlen_s(s2, s1max)
	CPPUNIT_ASSERT_THROW(strncpy_s(s1, strnlen_s(s2, strlen(s2)), s2, 100), RuntimeConstraintViolation);

	CPPUNIT_ASSERT_THROW((strncpy_s(s1, 3, s2, 6)), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW((strncpy_s(s1, 3, s2, 3)), RuntimeConstraintViolation);

	// Copying shall not take place between objects that overlap
	CPPUNIT_ASSERT_THROW(strncpy_s(s1, sizeof(s1), s1, 2), RuntimeConstraintViolation);
	// ... then strcpy_s sets s1[0] to the null character.
	CPPUNIT_ASSERT_EQUAL(0, (int)s1[0]);

	// Copying shall not take place between objects that overlap
	strcpy_s(s1, sizeof(s1), "1234"); //prepare buffer
	CPPUNIT_ASSERT_THROW(strncpy_s(s1, sizeof(s1), s1+2, 2), RuntimeConstraintViolation);

	// This should work because the objects do not overlap.
	strcpy_s(s1, sizeof(s1), "1234"); //prepare buffer
	strncpy_s(s1+2, sizeof(s1)-2, s1, 2);
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s1, "1212"));

	// Copying shall not take place between objects that overlap
	strcpy_s(s1, sizeof(s1), "1234"); //prepare buffer
	CPPUNIT_ASSERT_THROW(strncpy_s(s1+2, sizeof(s1), s1, 3), RuntimeConstraintViolation);
	
	// Copying shall not take place between objects that overlap
	strcpy_s(s1, sizeof(s1), "1234"); //prepare buffer
	s1[2] = '\0';
	CPPUNIT_ASSERT_THROW(strncpy_s(s1+2, sizeof(s1)-2, s1, 3), RuntimeConstraintViolation);

	// Because of the \0-byte our source is only 2 bytes long
	strcpy_s(s1, sizeof(s1), "1234"); //prepare buffer
	s1[1] = '\0';
	strncpy_s(s1+2, sizeof(s1)-2, s1, 3);
	CPPUNIT_ASSERT_EQUAL(s1[0], '1'); //memcmp(s1, "1\01\0\0", 5));
	CPPUNIT_ASSERT_EQUAL(s1[1], '\0');			
	CPPUNIT_ASSERT_EQUAL(s1[2], '1');
	CPPUNIT_ASSERT_EQUAL(s1[3], '\0');

	// this one should work
	strncpy_s(s1+2, sizeof(s1)-2, s1, 1);



}

///////////////////////////////////////////////////////
/// Test: Strcat_s
///
/// The strcat_s function returns zero if there was no runtime-constraint violation.
/// Otherwise, a non-zero value is returned.
///
///////////////////////////////////////////////////////
void TestString :: test_strcat_s_ShouldAppendCorrect (void)
{
	s2 = "1234";
	char s1[5];

	CPPUNIT_ASSERT_EQUAL(0, strcpy_s(s1, sizeof(s1), "12"));
	CPPUNIT_ASSERT_EQUAL(0, strcat_s(s1, sizeof(s1), "3"));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s1, "123"));

	CPPUNIT_ASSERT_EQUAL(0, strcat_s(s1, sizeof(s1), "4"));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s1, "1234"));
}

///////////////////////////////////////////////////////
/// Test: Strcat_s
///
///////////////////////////////////////////////////////
void TestString :: test_strcat_s_ShouldThrowException (void)
{
	char s1[5];

	strcpy_s(s1, sizeof(s1), "1234");
	

	// Neither s1 nor s2 shall be a null pointer
	CPPUNIT_ASSERT_THROW(strcat_s(NULL, 1, "5"), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(strcat_s(s1, 1, NULL), RuntimeConstraintViolation);
	// s1max shall not equal zero
	CPPUNIT_ASSERT_THROW(strcat_s(s1, 0, "5"), RuntimeConstraintViolation);
	// Copying shall not take place between objects that overlap
	strcpy_s(s1, sizeof(s1), "1234");
	CPPUNIT_ASSERT_THROW(strcat_s(s1, sizeof(s1), s1), RuntimeConstraintViolation);

	strcpy_s(s1, sizeof(s1), "1234"); 
	CPPUNIT_ASSERT_THROW(strcat_s(s1, sizeof(s1), s1+2), RuntimeConstraintViolation);

	// should not work because we would read and write
	// the current null byte of s1
	strcpy_s(s1, sizeof(s1), "12");
	CPPUNIT_ASSERT_THROW(strcat_s(s1, sizeof(s1), s1), RuntimeConstraintViolation);

	strcpy_s(s1, sizeof(s1), "123");
	CPPUNIT_ASSERT_THROW(strcat_s(s1, sizeof(s1), s1), RuntimeConstraintViolation);

	// Let m denote the value s1max - strnlen_s(s1, s1max) upon entry to strcat_s.
	// m shall not equal zero.
	int m = 1 - strnlen_s(s1, 1);
	CPPUNIT_ASSERT_EQUAL(1, m);

	// m shall be greater than strnlen_s(s2, m).
	int n = strnlen_s(s2, m);
	CPPUNIT_ASSERT_EQUAL(1, n);
}

///////////////////////////////////////////////////////
/// Test: Strncat_s
///
/// The strncat_s function returns zero if there was no runtime-constraint violation.
/// Otherwise, a non-zero value is returned.
///
///////////////////////////////////////////////////////
void TestString :: test_strncat_s_ShouldAppendCorrect (void)
{
	char s1[100] = "good";
	char s22[6] = "hello";
	char s4[7] = "abc";
	char s5[1000] = "bye";

	// EXAMPLE 1:
	// The strncat_s function can be used to copy a string without the danger that the result
	// will not be null terminated or that characters will be written past the end of the destination array.	
	CPPUNIT_ASSERT_EQUAL(0, strncat_s(s1, 100, s5, 1000));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s1, "goodbye"));

	CPPUNIT_ASSERT_EQUAL(0, strncat_s(s22, 6, "", 1));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s22, "hello"));

	CPPUNIT_ASSERT_EQUAL(0, strncat_s(s4, 7, "defghijklmn", 3));
	CPPUNIT_ASSERT_EQUAL(0, strcmp(s4, "abcdef"));

	char src[4] = "cat";
	char dest[5] = "dog";
	strncat_s(dest, sizeof(dest), src, 1);
	CPPUNIT_ASSERT_EQUAL(string("dogc"), string(dest)); 
}

///////////////////////////////////////////////////////
/// Test: Strncat_s
///
///////////////////////////////////////////////////////
void TestString :: test_strncat_s_ShouldThrowException (void)
{
	char s1[5];

	strcpy_s(s1, sizeof(s1), "1234");
	

	// Neither s1 nor s2 shall be a null pointer
	CPPUNIT_ASSERT_THROW(strncat_s(NULL, 1, "5", 1), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(strncat_s(s1, 1, NULL, 1), RuntimeConstraintViolation);

	// s1max shall not equal zero
	CPPUNIT_ASSERT_THROW(strncat_s(s1, 0, "5", 1), RuntimeConstraintViolation);

	// Copying shall not take place between objects that overlap
	CPPUNIT_ASSERT_THROW(strncat_s(s1, sizeof(s1), s1, 1), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(strncat_s(s1, sizeof(s1), s1+2, 1), RuntimeConstraintViolation);
	strcpy_s(s1, sizeof(s1), "1234");
	CPPUNIT_ASSERT_THROW(strncat_s(s1+2, sizeof(s1)-2, s1, 1), RuntimeConstraintViolation);

	// Let m denote the value s1max - strnlen_s(s1, s1max) upon entry to strncat_s.
	// m shall not equal zero.
//				   s1[0] = 0;
//			int m = 1 - strnlen_s(s1, 1);
//			CPPUNIT_ASSERT_EQUAL(1, m);

// // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//			// m shall be greater than strnlen_s(s2, m).
//			int n = strnlen_s(s2, m);
//			CPPUNIT_ASSERT_EQUAL(1, n);
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

}


void TestString :: test_gets_s (void)
{
	char input[] = "Ich bin ein\n Testinput";
	char s[256];
	
	char tmpnam[255];
	strcpy_s(tmpnam, sizeof(tmpnam), P_tmpdir);
	strcat_s(tmpnam, sizeof(tmpnam),  "/XXXXXX");
	int tmpfileid = mkstemp(tmpnam);
	FILE * tmpfile = fdopen(tmpfileid, "w");
	fwrite(input, sizeof(char), strlen(input), tmpfile);
	fclose(tmpfile);
	freopen(tmpnam, "r", stdin);

	s[0] = 'T';
	CPPUNIT_ASSERT_THROW(gets_s(NULL,RSIZE_MAX-1), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(gets_s(s,RSIZE_MAX+1), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(gets_s(s,0), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_EQUAL('T' ,s[0]);

	freopen(tmpnam, "r", stdin);
	gets_s(s, 14);
	CPPUNIT_ASSERT_EQUAL(0,strncmp(s,"Ich bin ein",11));
	
	gets_s(s, 14);
	CPPUNIT_ASSERT_EQUAL(0,strncmp(s," Testinput",11));

	gets_s(s, 2);
	CPPUNIT_ASSERT_EQUAL(true,s[0] == '\0');
}

void TestString :: test_memcpy_s (void)
{
	char p1[25]; 
	char p2[] = "Ich bin ein Teststring";
	int s1max = 25;
	int n = 10;

	CPPUNIT_ASSERT_THROW(memcpy_s(NULL, s1max, p2, n), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(memcpy_s(p1, s1max, NULL, n), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(memcpy_s(p1, RSIZE_MAX+1, p2, n), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(memcpy_s(p1, s1max, p2, RSIZE_MAX+1), RuntimeConstraintViolation);
	for(int i = 0; i < s1max; i++)
		CPPUNIT_ASSERT_EQUAL(true, p1[i] == 0);
	CPPUNIT_ASSERT_THROW(memcpy_s(p2+2, sizeof(p2)-2, p2, n), RuntimeConstraintViolation);

	char p4[] = "Ich bin ein Teststring";
	memcpy_s(p1, s1max, p4, n);
	CPPUNIT_ASSERT_EQUAL(0,strncmp(p1,p4,9));
}

///XXX: this test only works in an english enviroment
void TestString :: test_strerror_s (void)
{
	char s[17];
	rsize_t maxsize = 17;
	errno_t errnum = EINVAL;
	char expected[] = "Invalid argument"; // 16 characters

	CPPUNIT_ASSERT_THROW(strerror_s(NULL, maxsize, errnum), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(strerror_s(s, RSIZE_MAX+1, errnum), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(strerror_s(s, 0, errnum), RuntimeConstraintViolation);

	
	strerror_s(s,maxsize,errnum);
	CPPUNIT_ASSERT_EQUAL(strcmp(s,expected),0);

	maxsize = 16;
	strerror_s(s, maxsize, errnum);
	CPPUNIT_ASSERT_EQUAL(strcmp(s,"Invalid argu..."),0);

	maxsize = 15;
	strerror_s(s,maxsize,errnum);
	CPPUNIT_ASSERT_EQUAL(strcmp(s, "Invalid arg..."),0);
	
	maxsize = 4;
	strerror_s(s,maxsize,errnum);
	CPPUNIT_ASSERT_EQUAL(strcmp(s, "..."),0);

	maxsize = 3;
	strerror_s(s,maxsize,errnum);
	CPPUNIT_ASSERT_EQUAL(strcmp(s, "In"),0);

	// for unknown errors GNU's strerror_r (which is used internally)
	// reacts differently
	maxsize = 17;
	strerror_s(s, sizeof(s), 41);
	CPPUNIT_ASSERT_EQUAL(strcmp(s, "Unknown error 41"),0);

	strerror_s(s, sizeof(s), 138);
	CPPUNIT_ASSERT_EQUAL(strcmp(s, "Unknown error..."),0);
}

void TestString :: test_strerrorlen_s (void)
{
	errno_t errnum = EINVAL;
	char expected[] = "Invalid argument";
	size_t explen = strlen(expected);

	CPPUNIT_ASSERT_EQUAL(strerrorlen_s(errnum), explen);
}

void TestString :: test_memmove_s (void)
{

	char s1[25];
	rsize_t s1max = 25;
	const char * s2 = "Ich bin ein Teststring";
	rsize_t n = strlen(s2);

	CPPUNIT_ASSERT_THROW(memmove_s(NULL, s1max, s2, n), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(memmove_s(s1, s1max, NULL, n), RuntimeConstraintViolation);
	for(rsize_t i = 0; i < s1max; i++)
		CPPUNIT_ASSERT_EQUAL(s1[i] == '\0',true);

	CPPUNIT_ASSERT_THROW(memmove_s(s1, RSIZE_MAX+1, s2, n), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(memmove_s(s1, s1max, s2, RSIZE_MAX+1), RuntimeConstraintViolation);
	for(rsize_t i = 0; i < s1max; i++)
		CPPUNIT_ASSERT_EQUAL(s1[i] == '\0',true);

	CPPUNIT_ASSERT_THROW(memmove_s(s1, s1max, s2, s1max+1), RuntimeConstraintViolation);
	for(rsize_t i = 0; i < s1max; i++)
		CPPUNIT_ASSERT_EQUAL(s1[i] == '\0',true);		

	{
		char s1[25];
		int ret = memmove_s(s1, sizeof(s1), s2, strlen(s2)+1);
		CPPUNIT_ASSERT_EQUAL(ret,0);
		CPPUNIT_ASSERT_EQUAL(0, strcmp(s1,s2));
	}
}

void TestString :: test_strtok_s (void)
{
	char s1[] = "I'm a teststring";
	rsize_t s1may = 16;
	rsize_t * s1max = &s1may;
	const char * s2 = "t";
	char ** ptr = (char **) NULL;

	CPPUNIT_ASSERT_THROW(strtok_s(NULL, s1max, s2, ptr), RuntimeConstraintViolation);
	rsize_t over = RSIZE_MAX+1;
	rsize_t * overp = &over;
	CPPUNIT_ASSERT_THROW(strtok_s(s1, overp, s2, ptr), RuntimeConstraintViolation);

	char str1[] = "?a???b,,,#c";
	char str2[] = "\t \t";
	char *t, *ptr1, *ptr2;
	rsize_t max1 = sizeof(str1);
	rsize_t max2 = sizeof(str2);
	
	t = strtok_s(str1, &max1, "?", &ptr1); // t points to the token "a"
	CPPUNIT_ASSERT_EQUAL(strcmp(t,"a"),0);
	t = strtok_s(NULL, &max1, ",", &ptr1); // t points to the token points to the token "??b"
	CPPUNIT_ASSERT_EQUAL(strcmp(t,"??b"),0);
	t = strtok_s(str2, &max2, " \t", &ptr2); // t is a null pointer
	CPPUNIT_ASSERT_EQUAL(t,(char*) NULL);
	t = strtok_s(NULL, &max1, "#,", &ptr1); // t points to the token "c"
	CPPUNIT_ASSERT_EQUAL(strcmp(t,"c"),0);
	t = strtok_s(NULL, &max1, "?", &ptr1); // t is a null pointer
	CPPUNIT_ASSERT_EQUAL(t,(char*) NULL);
	
}

void TestString :: test_fopen_s (void)
{
	FILE *streamptr;
	const char *filename = ".test";
	const char *mode = "uw";
	int ret = 0;

	CPPUNIT_ASSERT_THROW(fopen_s((FILE **) NULL, filename, mode), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(fopen_s(&streamptr, (char *) NULL, mode), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(fopen_s(&streamptr, filename, (char*) NULL), RuntimeConstraintViolation);

	ret = fopen_s(&streamptr, filename, mode);
	CPPUNIT_ASSERT_EQUAL(0, ret);
	fprintf(streamptr, "test123\n");
	fclose(streamptr);
	
	mode="w";
	ret = fopen_s(&streamptr, filename, mode);
	CPPUNIT_ASSERT_EQUAL(ret, 0);
	fclose(streamptr);
}

void TestString :: test_freopen_s (void)
{
	int ret = 0;

	FILE *streamptr = NULL;
	const char * restrict filename = ".test";
	const char * restrict mode = "uw";
	ret = fopen_s(&streamptr, filename, mode);	
	
	FILE * newstreamptr;
	FILE * stream = NULL;

	CPPUNIT_ASSERT_THROW(freopen_s((FILE **) NULL, filename, mode, stream), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(freopen_s(&newstreamptr, filename, (char *)NULL, stream), RuntimeConstraintViolation);
	CPPUNIT_ASSERT_THROW(freopen_s(&newstreamptr, filename, mode, (FILE *) NULL), RuntimeConstraintViolation);

	mode = "w";
	ret = freopen_s(&newstreamptr, NULL, mode, streamptr);
	CPPUNIT_ASSERT_EQUAL(ret,0);
}
